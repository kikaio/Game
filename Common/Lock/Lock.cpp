#include "pch.h"
#include "Lock.h"
#include "LockManager.h"


#define DO_LOCK_TRACKING_LOG	false

Lock::Lock(const char* _name)
 : name(_name)
{
}

void Lock::DoLock()
{
	lockObj.lock();
}

void Lock::DoUnlock()
{
	lockObj.unlock();
}




LockGuard::LockGuard(Lock& _lock, const char* _fileName, const int _lineNo)
 : lock(_lock), fileName(_fileName), lineNo(_lineNo)
{
	lock.DoLock();
#ifdef _DEBUG
	LOCK_MGR().Push(&lock);
#endif
#if DO_LOCK_TRACKING_LOG
	
#endif
}

LockGuard::~LockGuard()
{
#ifdef _DEBUG
	LOCK_MGR().Pop(&lock);
#endif
	lock.DoUnlock();
#if DO_LOCK_TRACKING_LOG

#endif
}

