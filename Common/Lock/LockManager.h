#pragma once
#include "Singleton.h"
#include "Lock.h"


class LockManager : public Singleton<LockManager>
{
private:
	mutex mgrLock;
	mutex idGenLock;
private:
	map<string, LockId> nameToLockId;
	map<LockId, string> lockIdToName;
	map<LockId, set<LockId>> lockHistory;
private:
	vector<int32_t> discoveredOrder;			//node가 발견된 순서를 기록하는 배열
	int32_t discoveredCount = 0;				//node가 발견된 순서
	vector<bool> finished;						//node가 발견되었는지 여부.
	vector<int32_t> parent;						//특정 node의 parent.
private:
	map<LockId, int32_t> discoveredOrderMap;	//node가 발견된 순서
	map<LockId, bool> finishedMap;				//node가 발견되었는지 여부.
	map<LockId, LockId> parentMap;				//특정 node의 parent.
private:
	bool CheckCycle(LockId _lockId);
private:
	void Dfs(int32_t idx);
public:
	void Push(Lock* _lock);
	void Push(LockId _lockId, string _lockName);
	void Pop(Lock* _lock);
	void Pop(LockId _lockId);
public:
	LockId GenLockId();
};