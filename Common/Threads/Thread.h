#pragma once

class Thread // : public enable_shared_from_this<Thread>
{
public:
	Thread() = default;
	Thread(WorkFunc _work, UInt32 _seedNo
		, const char* _tName = EMPTY_CONST_CHAR
		, const char* _desc = EMPTY_CONST_CHAR
	);

	Thread(const Thread& other);
	Thread(Thread&& other);
	Thread& operator= (Thread&& other) noexcept;
	Thread& operator= (const Thread& other) noexcept;

	~Thread();
private:
	bool isStarted = false;
	WorkFunc work;
	thread worker;
	string tName;
	string tDesc;
private:
	void Init();
	void Release();
	void PrintfLog(const char*);
public:
	void Start();
	void Join();
public:
	void RenderInfo();
};