#pragma once

class DummyUserManager: public Singleton<DummyUserManager>
{
private:
	int32_t dummyUserIdx = 0;
private:
	VAL_LOCK(dummyUserMapLock);
	map<int32_t, DummyUserSptr> dummyUserMap;
public:
	void PushDummyUser(DummyUserSptr _suer);
	DummyUserSptr PeekDummyUser(int32_t _dummyUserIdx);
	DummyUserSptr PopDummyUser(int32_t _dummyUserIdx);
};