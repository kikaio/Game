#pragma once
#include "Singleton.h"
#include "Lock.h"

class LockManager : public Singleton<LockManager>
{
private:
	mutex mgrLock;
private:
	bool CheckCycle();
public:
	void Push(Lock* _lock);
	void Pop(Lock* _lock);
};