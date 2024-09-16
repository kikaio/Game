#include "pch.h"
#include "ReadWriteLock.h"

ReadWriteLock::ReadWriteLock(const char* _name)
	: name(_name)
{
}

void ReadWriteLock::ReadLock()
{
	UInt32 zeroMask = EMPTY_MASK;
	UInt32 curSpinCnt = 0;
	UInt32 curThreadId = 0;
	if((lockFlag.load() & WRITE_MASK >> 16) == curThreadId) {
		lockFlag.fetch_add(1);
		return ;
	}
	chrono::system_clock::time_point curTimePoint = chrono::system_clock::now();

	while ((lockFlag.load() & WRITE_MASK) > 0) {
		curSpinCnt++;
		if(curSpinCnt > SPIN_MAX_CNT) {
			curSpinCnt = 0;
			this_thread::yield();
			continue;
		}

		if (chrono::system_clock::now() - curTimePoint > chrono::seconds(ACQUIRE_TIME_OUT_SEC)) {
			//todo : err assert -> deadlock
			return;
		}
	}
}

void ReadWriteLock::ReadUnlock()
{
	if(lockFlag.load() == EMPTY_MASK) {
		//todo : err assert
	}

	lockFlag.fetch_sub(1);

	return ;
}

void ReadWriteLock::WriteLock()
{
	UInt32 curThreadId = 0;
	if((lockFlag.load() & WRITE_MASK) >> 16 == curThreadId) {
		curWriteCnt++;
		return ;
	}
	UInt32 expectVal = EMPTY_MASK;
	UInt32 desiredVal = curThreadId << 16;
	UInt32 curSpinCnt = 0;

	chrono::system_clock::time_point curTimePoint = chrono::system_clock::now();

	while(lockFlag.compare_exchange_strong(OUT expectVal, desiredVal) == false) {
		curSpinCnt++;
		if(curSpinCnt >= SPIN_MAX_CNT) {
			//todo logging
			curSpinCnt = 0;
			this_thread::yield();
			continue;
		}

		if(chrono::system_clock::now() - curTimePoint > chrono::seconds(ACQUIRE_TIME_OUT_SEC)) {
			//todo : err assert -> deadlock
			return;
		}
	}
	curWriteCnt++;
	return ;
}

void ReadWriteLock::WriteUnlock()
{
	if(curWriteCnt < 1) {
		//todo : err assert
		return ;
	}
	else if(curWriteCnt == 1){
		lockFlag.store(EMPTY_MASK);
		curWriteCnt--;
	}
	else {
		curWriteCnt--;
	}
	return ;
}
