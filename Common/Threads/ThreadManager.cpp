#include "pch.h"
#include "ThreadManager.h"
#include "Thread.h"


atomic<UInt32> ThreadManager::threadSeedNo = 1;

void ThreadManager::PushThread(WorkFunc _func, const char* _tName, const char* _desc)
{	
	threads.push_back(MakeShared<Thread>(Thread(_func, threadSeedNo.fetch_add(1), _tName, _desc)));
	return ;
}

void ThreadManager::PushAndStart(WorkFunc _func, const char* _tName, const char* _desc)
{
	LOCK_GUARDDING(threadsLock);
	auto threadSptr = MakeShared<Thread>(Thread(_func, threadSeedNo.fetch_add(1), _tName, _desc));
	threads.push_back(threadSptr);
	threadSptr->Start();
}

void ThreadManager::StartAll()
{
	LOCK_GUARDDING(threadsLock);
	for(auto& t : threads) {
		t->Start();
	}
}

void ThreadManager::JoinAll()
{
	LOCK_GUARDDING(threadsLock);
	for(auto& t : threads) {
		t->Join();
	}
}

