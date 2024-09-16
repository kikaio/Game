#include "pch.h"
#include "Thread.h"
#include <thread>


Thread::Thread(WorkFunc _work, UInt32 _seedNo, const char* _tName, const char* _desc)
 : seedNo(_seedNo)
{
	work = ([&_work, ref=shared_from_this()]() {
		ref->Init();
		_work();
		ref->Release();
	});
	threadDesc = _desc;

}

Thread::~Thread()
{
	if(isStarted) {
		worker.join();
	}
}

void Thread::Init()
{
	PrintfLog("thread was started.");
}

void Thread::Release()
{
	PrintfLog("thread was released.");
}

void Thread::PrintfLog(const char* _msg)
{
	printf("[tId:%d][%s][seedNo:%d]%s\n", worker.get_id(), tName, seedNo, _msg);
}

void Thread::Start()
{
	if(isStarted == false) {
		worker = thread(work);
		isStarted = true;
	}
}

void Thread::Join()
{
	if(isStarted == false) {
		PrintfLog("thread not started.");
		return ;
	}
	while(true){
		if(worker.joinable()) {
			worker.join();
			break;
		}
	}
}

