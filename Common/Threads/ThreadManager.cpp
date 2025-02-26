#include "pch.h"
#include "ThreadManager.h"
#include "Thread.h"


atomic<UInt32> ThreadManager::threadSeedNo = 1;

void ThreadManager::PushThread(WorkFunc _func, const char* _tName, const char* _desc)
{	
	auto threadSptr = MakeShared<Thread>(_func, threadSeedNo.fetch_add(1), _tName, _desc);

	threads.push_back(threadSptr);
	return ;
}

void ThreadManager::PushAndStart(WorkFunc _func, const char* _tName, const char* _desc)
{
	auto threadSptr = MakeShared<Thread>(_func, threadSeedNo.fetch_add(1), _tName, _desc);
	threadSptr->Start();

	threads.push_back(threadSptr);
}

void ThreadManager::StartAll()
{
	for(auto& t : threads) {
		t->Start();
	}
}

void ThreadManager::JoinAll()
{
	for(auto& t : threads) {
		t->Join();
	}
}

void ThreadManager::RenderThreadsInfo()
{
	for (auto& t : threads) {
		t->RenderInfo();
	}
}

void ThreadManager::DoGlobalQueueWork()
{
	while (true) {
		uint64_t now = ::GetTickCount64();
		if (now > LEndTickCount) {
			break;;
		}
		JobQueueSptr jobQueueSptr = GlobalQueue::Get().Pop();
		if (jobQueueSptr == nullptr) {
			break;
		}
		jobQueueSptr->Execute();
	}
}

void ThreadManager::DoDitributeJob()
{
	const uint64_t now = ::GetTickCount64();
	JobTimer::Get().Distribute(now);
}

