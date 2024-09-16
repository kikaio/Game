#include "pch.h"
#include "Thread.h"
#include <thread>


Thread::Thread(WorkFunc _work, UInt32 _seedNo, const char* _tName, const char* _desc)
{
	LThreadId = _seedNo;
	work = ([&_work, ref=shared_from_this()]() {
		ref->Init();
		_work();
		ref->Release();
	});
	threadDesc = _desc;

}

Thread::Thread(const Thread& other)
	: isStarted(other.isStarted), work(other.work), tName(other.tName), threadDesc(other.threadDesc)
{
}

Thread::Thread(Thread&& other)
{
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	threadDesc = std::move(other.threadDesc);

	other.isStarted = false;
	other.work = nullptr;
	other.tName = EMPTY_CONST_CHAR;
	other.threadDesc = EMPTY_CONST_CHAR;
}

Thread& Thread::operator=(Thread&& other) noexcept{
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	threadDesc = std::move(other.threadDesc);

	other.isStarted = false;
	other.work = nullptr;
	other.tName = EMPTY_CONST_CHAR;
	other.threadDesc = EMPTY_CONST_CHAR;
	return *this;
}

Thread& Thread::operator=(const Thread& other) noexcept {
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	threadDesc = std::move(other.threadDesc);
	return *this;
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
	printf("[tId:%d][%s]%s\n", LThreadId, tName.c_str(), _msg);
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

