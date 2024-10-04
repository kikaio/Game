#pragma once


class Lock
{
public:
	Lock(const char* _name);
private:
	Mutex lockObj;
	const string name ;
	LockId lockId = 0;
public:
	void DoLock();
	void DoUnlock();
	const string& GetName() const{
		return name;
	}
	void SetLockId(LockId _lockId) {
		lockId = _lockId;
		return ;
	}
	LockId LockId() const {
		return lockId;
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
