#include "pch.h"
#include "Thread.h"
#include <thread>


Thread::Thread(WorkFunc _work, UInt32 _seedNo, const char* _tName, const char* _desc)
 : tName(_tName), tDesc(_desc)
{
	LThreadId = _seedNo;
	work = ([this, _work=_work]() {
		this->Init();
		_work();
		this->Release();
	});
}

Thread::Thread(const Thread& other)
	: isStarted(other.isStarted), work(other.work), tName(other.tName), tDesc(other.tDesc)
{
}

Thread::Thread(Thread&& other)
{
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	tDesc = std::move(other.tDesc);

	other.isStarted = false;
	other.work = nullptr;
	other.tName = EMPTY_CONST_CHAR;
	other.tDesc = EMPTY_CONST_CHAR;
}

Thread& Thread::operator=(Thread&& other) noexcept{
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	tDesc = std::move(other.tDesc);

	other.isStarted = false;
	other.work = nullptr;
	other.tName = EMPTY_CONST_CHAR;
	other.tDesc = EMPTY_CONST_CHAR;
	return *this;
}

Thread& Thread::operator=(const Thread& other) noexcept {
	isStarted = other.isStarted;
	work = std::move(other.work);
	tName = std::move(other.tName);
	tDesc = std::move(other.tDesc);
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
			isStarted = false;
			break;
		}
	}
}

void Thread::RenderInfo()
{
	printf("tId : %d\n", LThreadId);
	printf("tName : %s\n", tName.c_str());
	printf("tDesc : %s\n", tDesc.c_str());
}
