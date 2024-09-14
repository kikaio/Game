#pragma once

#define LOCK_MGR()			LockMananger::Get()

class LockMananger : public Singleton<LockMananger>
{
private:
	Lock lock;
private:
	bool CheckCycle();
public:
	void Push(Lock* _lock);
	void Pop(Lock* _lock);
};