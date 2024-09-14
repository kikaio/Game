#pragma once

#define INVALID_LINE_NO		-1;


class Lock
{
public:
	Lock(const char* _name);
private:
	unique_lock<Mutex> uniqueLock;
	Mutex lockObj;
	const string name ;
public:
	void DoLock();
	void DoUnlock();
	const string& GetName() const{
		return name;
	}
};


class LockGuard
{
public:
	LockGuard(Lock& _lock, const char* _fileName, const int _lineNo);
	~LockGuard();
private:
	Lock& lock;
	const char* fileName;
	int lineNo = INVALID_LINE_NO;
	unique_lock<Mutex> uniqLock;
private:
};
