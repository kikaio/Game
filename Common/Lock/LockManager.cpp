#include "pch.h"
#include "Lock.h"
#include "LockManager.h"



bool LockManager::CheckCycle()
{
	return false;
}

void LockManager::Push(Lock* _lock)
{
	lock_guard<mutex> lg(mgrLock);
	if(CheckCycle() == false) {
		//todo : assert or logging
	}
	return ;
}

void LockManager::Pop(Lock* _lock)
{
	lock_guard<mutex> lg(mgrLock);
	return ;
}
