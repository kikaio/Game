#pragma once

class Thread : public enable_shared_from_this<Thread>
{
public:
	Thread() = delete;
	Thread(const Thread& other) = delete;
	Thread(Thread&& other) = delete;
	
	Thread(WorkFunc _work, UInt32 _seedNo
		, const char* _tName = EMPTY_CONST_CHAR
		, const char* _desc = EMPTY_CONST_CHAR
	);

	~Thread();
private:
	bool isStarted = false;
	WorkFunc work;
	thread worker;
	string tName;
	string threadDesc;
	UInt32 seedNo = 0; 
private:
	void Init();
	void Release();
	void PrintfLog(const char*);
public:
	void Start();
	void Join();
};