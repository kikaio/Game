#pragma once

class DummyUserManager: public Singleton<DummyUserManager>
{
private:
	int32_t dummyUserIdx = 0;
private:
	vector<DumActSptr> dumActs;
private:
	VAL_LOCK(dummyUserMapLock);
	map<int32_t, DummyUserSptr> dummyUserMap;
private:
	bool LoadScenarioFromFile();
public:
	void PushDummyUser(DummyUserSptr _suer);
	DummyUserSptr PeekDummyUser(int32_t _dummyUserIdx);
	DummyUserSptr PopDummyUser(int32_t _dummyUserIdx);

public :
	bool ReadyTestScenario();
	void DoTestScenario();
};