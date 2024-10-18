#pragma once

class ReadWriteLock
{
	enum : UInt32{
		WRITE_MASK = 0xFFFF'0000
		, READ_MASK = 0x0000'FFFF
		, EMPTY_MASK = 0x0000'0000
		, SPIN_MAX_CNT = 50000
		, ACQUIRE_TIME_OUT_SEC = 10
	};
public:
	ReadWriteLock(const char* _name = EMPTY_CONST_CHAR);
private:
	atomic<UInt32> lockFlag = 0;
	string name;
	UInt16 curWriteCnt = 0;
	LockId lockId = 0;
public:
	string LockName() {
		return name;
	}
	LockId LockId() {
		return lockId;
	}
	void ReadLock();
	void ReadUnlock();
	void WriteLock();
	void WriteUnlock();
};

class ReadLockGuard
{
public:
	ReadLockGuard(ReadWriteLock& _lock, const char* _fileName, const int _lineNo);
	~ReadLockGuard();
private:
	ReadWriteLock& lock;
	const char* fileName;
	int lineNo = INVALID_LINE_NO;
};

class WriteLockGuard
{
public:
	WriteLockGuard(ReadWriteLock& _lock, const char* _fileName, const int _lineNo);
	~WriteLockGuard();
private:
	ReadWriteLock& lock;
	const char* fileName;
	int lineNo = INVALID_LINE_NO;
};