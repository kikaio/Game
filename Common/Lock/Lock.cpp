#include "pch.h"
#include "Lock.h"
#include "LockManager.h"


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
#if _DEBUG
	LOCK_MGR().Push(&lock);
#endif
#if DO_LOCK_TRACKING_LOG
	
#endif
	lock.DoLock();
}

LockGuard::~LockGuard()
{
	lock.DoUnlock();
#if _DEBUG
	LOCK_MGR().Pop(&lock);
#endif
#if DO_LOCK_TRACKING_LOG

#endif
}

