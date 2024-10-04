#include "pch.h"
#include "Lock.h"
#include "LockManager.h"



bool LockManager::CheckCycle()
{
	//todo : check lock allocate cycle exist -> deadlock detected
	const int32_t lockCount = nameToLockId.size();
	discoveredOrder = vector<int32_t>(lockCount, -1);
	discoveredCount = 0;
	finished = vector<bool>(lockCount, false);
	//특정 idx의 Lock의 부모(?) lockId
	parent = vector<LockId>(lockCount, -1);
	 
	 for(int32_t idx = 0; lockCount; ++idx) {
		//lock
		Dfs(idx);
	 }

	 // 이 3개는 dfs 시 cycle을 확인하기 위한 용도이다.
	 discoveredOrder.clear();
	 finished.clear();
	 parent.clear();

	return false;
}

void LockManager::Dfs(int32_t idx)
{
	if(discoveredOrder[idx] != -1) {
		return ;
	}

	discoveredOrder[idx] = discoveredCount++;
	//idx번쨰로 push된 lock의 id에 대한 간선 정보.
	auto finder = lockHistory.find(pushedLockIds[idx]);
	if(finder == lockHistory.end()) {
		// 이 경우 해당 LockId 정점은 고립된 상태.
		return ;
	}

	set<LockId>& nextSet = finder->second;
	for(LockId there : nextSet) {
		int32_t childIdx = lockIdToPushedIdx[there];
		//해당하는 ID의 Lock을 방문한 적이 없다면...
		if(discoveredOrder[childIdx] == -1) {
			parent[childIdx] = idx;
			Dfs(childIdx);
			continue;
		}
		else {
			// idx가 childIdx 가 먼저 발견되었다면, childIdx 는 idx의 후손이다. [순방향 간선]
			if(discoveredOrder[idx] < discoveredOrder[childIdx]) {
				continue;
			}
			else { //순방향이 아니고 Dfs(childIdx)가 아직 종료하지 않았다면, childIdx
				
			}
		}
	}
}

void LockManager::Push(Lock* _lock)
{
	lock_guard<mutex> lg(mgrLock);

	string lockName = _lock->GetName();
	LockId lockId = _lock->LockId();

	nameToLockId[lockName] = lockId ;
	lockIdToName[lockId] = lockName;

	//해당 스레드가 잡고있는 lock 이 있었다면
	if(LLockStack.empty() == false) {
		//기존의 발견되지 않았던 lock이라면 데드락 여부 체크.
		LockId prevLockId = LLockStack.top();
		if(lockId != prevLockId) {
			set<LockId>& history = lockHistory[prevLockId];
			if(history.find(lockId) == history.end()) {
				history.insert(lockId);
				CheckCycle();
			}
		}
	}
	lockIdToPushedIdx.insert(make_pair(pushedLockIds.size(), lockId));
	pushedLockIds.push_back(lockId);
	LLockStack.push(lockId);

	return ;
}

void LockManager::Pop(Lock* _lock)
{
	lock_guard<mutex> lg(mgrLock);
	if(LLockStack.empty()) {
		//todo : ASSERT
		printf("Lock Multiple Unlocked!\n");
		return ;
	}

	if(_lock->LockId() != LLockStack.top()) {
		//todo : ASSERT
		printf("Lock Unlock invalid.\n");
		return ;
	}
	
	pushedLockIds.pop_back();
	LLockStack.pop();
	return ;
}

LockId LockManager::GenLockId()
{
	lock_guard<mutex> lg(idGenLock);
	static LockId curLockId = 1;
	return curLockId++;
}
