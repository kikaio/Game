#include "pch.h"
#include "Lock.h"
#include "LockManager.h"



bool LockManager::CheckCycle(LockId _lockId)
{

	//const int32_t lockCount = nameToLockId.size();
	//discoveredOrder = vector<int32_t>(lockCount, -1);
	//discoveredCount = 0;
	//finished = vector<bool>(lockCount, false);

	discoveredCount = 0;
	finishedMap[_lockId] = false;
	discoveredOrderMap[_lockId] = -1;
	parentMap[_lockId] = -1;
	for (auto pair : finishedMap) {
		pair.second = false;
	}
	for (auto pair : discoveredOrderMap) {
		pair.second = -1;
	}
	for (auto pair : parentMap) {
		pair.second = -1;
	}
	
	for (auto lockId : LLockStack) {
		Dfs(lockId);
	}

	//특정 idx의 Lock의 부모(?) lockId
	//parent = vector<LockId>(lockCount, -1);
	 
	//for(int32_t idx = 0; idx < lockCount; ++idx) {
	//	Dfs(LLockStack[idx]);
	//}

	 //// 이 3개는 dfs 시 cycle을 확인하기 위한 용도이다.
	 //discoveredOrder.clear();
	 //finished.clear();
	 //parent.clear();

	return false;
}

void LockManager::Dfs(int32_t _curLockId)
{
	{
		if (discoveredOrderMap[_curLockId] != -1) {
			return;
		}
		discoveredOrderMap[_curLockId] = ++discoveredCount;

		auto finder = lockHistory.find(_curLockId);
		// 이 경우 해당 노드에서 뻗어나가는 간선이 없는 상태
		if (finder == lockHistory.end()) {
			return;
		}
		set<LockId>& lines = finder->second;
		for (LockId target : lines) {
			if (discoveredOrderMap[target] == -1) {
				parentMap[target] = _curLockId;
				Dfs(target);
				continue;
			}
			else {
				// 이 경우 target은 _curLockId의 후손이다. [순방향 간선]
				if (discoveredOrderMap[_curLockId] < discoveredOrderMap[target]) {
					continue;
				}
				else { 
					//순방향이 아니고 Dfs(target)가 아직 종료하지 않았다면
					if (finishedMap[target] == false) {
						//todo : ASSERT
						printf("%s => %s\n"
							, lockIdToName[_curLockId].c_str()
							, lockIdToName[target].c_str()
						);
						int32_t nowLockId = _curLockId;
						while (true) {
							printf("%s => %s\n"
								, lockIdToName[parentMap[nowLockId]].c_str()
								, lockIdToName[nowLockId].c_str()
							);
							nowLockId = parentMap[nowLockId];
							if (nowLockId == target) {
								break;
							}
						}
						CRASH("dead lock detected\n");
					}
				}
			}
		}
	}
	finishedMap[_curLockId] = true;





	//if(discoveredOrder[idx] != -1) {
	//	return ;
	//}

	//discoveredOrder[idx] = discoveredCount++;
	////idx번쨰로 push된 lock의 id에 대한 간선 정보.
	//auto finder = lockHistory.find(pushedLockIds[idx]);
	//if(finder == lockHistory.end()) {
	//	// 이 경우 해당 LockId 정점은 고립된 상태.
	//	return ;
	//}

	//set<LockId>& nextSet = finder->second;
	//for(LockId there : nextSet) {
	//	int32_t childIdx = lockIdToPushedIdx[there];
	//	//해당하는 ID의 Lock을 방문한 적이 없다면...
	//	if(discoveredOrder[childIdx] == -1) {
	//		parent[childIdx] = idx;
	//		Dfs(childIdx);
	//		continue;
	//	}
	//	else {
	//		// idx가 childIdx 가 먼저 발견되었다면, childIdx 는 idx의 후손이다. [순방향 간선]
	//		if(discoveredOrder[idx] < discoveredOrder[childIdx]) {
	//			continue;
	//		}
	//		else { //순방향이 아니고 Dfs(childIdx)가 아직 종료하지 않았다면, childIdx
	//			if (finished[childIdx] == false) {
	//				//todo : ASSERT
	//				printf("%s => %s\n"
	//					, lockIdToName[pushedLockIds[idx]].c_str()
	//					, lockIdToName[childIdx].c_str()
	//				);
	//				int32_t nowIdx = idx;
	//				while (true) {
	//					printf("%s => %s\n"
	//						, lockIdToName[pushedLockIds[parent[nowIdx]]].c_str()
	//						, lockIdToName[pushedLockIds[nowIdx]].c_str()
	//					);
	//					nowIdx = parent[nowIdx];
	//					if (nowIdx == childIdx) {
	//						break;
	//					}
	//				}
	//				CRASH("dead lock detected\n");
	//			}
	//		}
	//	}
	//}
	//finished[idx] = true;
}

void LockManager::Push(Lock* _lock)
{
	Push(_lock->LockId(), _lock->GetName());
	return ;
}

void LockManager::Push(LockId _lockId, string _lockName)
{
	lock_guard<mutex> lg(mgrLock);

	nameToLockId[_lockName] = _lockId;
	lockIdToName[_lockId] = _lockName;

	//해당 스레드가 잡고있는 lock 이 있었다면
	if (LLockStack.empty() == false) {
		//기존의 발견되지 않았던 lock이라면 데드락 여부 체크.
		LockId prevLockId = LLockStack.back();
		if (_lockId != prevLockId) {
			set<LockId>& history = lockHistory[prevLockId];
			if (history.find(_lockId) == history.end()) {
				history.insert(_lockId);
				CheckCycle(_lockId);
			}
		}
	}

	LLockStack.push_back(_lockId);

	return;
}

void LockManager::Pop(Lock* _lock)
{
	Pop(_lock->LockId());
}

void LockManager::Pop(LockId _lockId)
{
	lock_guard<mutex> lg(mgrLock);

	ASSERT_CRASH(LLockStack.empty() == false);
	ASSERT_CRASH(_lockId == LLockStack.back());

	LLockStack.pop_back();
	return;
}

LockId LockManager::GenLockId()
{
	lock_guard<mutex> lg(idGenLock);
	static LockId curLockId = 1;
	return curLockId++;
}
