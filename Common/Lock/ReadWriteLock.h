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
public:
	string GetName() {
		return name;
	}
	void ReadLock();
	void ReadUnlock();
	void WriteLock();
	void WriteUnlock();
};

