#include "pch.h"
#include "Lock.h"
#include "LockManager.h"



bool LockManager::CheckCycle()
{
	return false;
}

void LockManager::Push(Lock* _lock)
{
	LOCK_GUARDDING(mgrLock);
	if(CheckCycle() == false) {
		//todo : assert or logging
	}
	return ;
}

void LockManager::Pop(Lock* _lock)
{
	LOCK_GUARDDING(mgrLock);
	return ;
}
