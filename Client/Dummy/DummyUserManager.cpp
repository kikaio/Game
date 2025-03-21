#include "pch.h"
#include "DummyUserManager.h"
#include "DummyUser.h"

bool DummyUserManager::LoadScenarioFromFile()
{
	{
		//시작 시 connect 요청
		auto _dumActSptr = MakeShared<DumActGameServerConnect>(100);
		dumActs.push_back(_dumActSptr);
	}
	{
		//LoginData 설정
		auto _dumActSptr = MakeShared<DumActGameConn>(100);
		dumActs.push_back(_dumActSptr);
	}
	{
		//LoginData 설정
		auto _dumActSptr = MakeShared<DumActSetLoginData>("testDummy");
		dumActs.push_back(_dumActSptr);
	}
	{
		//LoginData 설정
		auto _dumActSptr = MakeShared<DumActLogin>(100);
		dumActs.push_back(_dumActSptr);
	}
	//{
	//	//connect 후 chat 전송
	//	auto _dumActSptr = MakeShared<DumActChat>(1, "first chat");
	//	dumActs.push_back(_dumActSptr);
	//}
	//{
	//	//connect 후 chat 전송
	//	auto _dumActSptr = MakeShared<DumActChat>(2, "second chat");
	//	dumActs.push_back(_dumActSptr);
	//}
	return true;
}

void DummyUserManager::PushDummyUser(DummyUserSptr _user)
{
	LOCK_GUARDDING(dummyUserMapLock);
	dummyUserMap[dummyUserIdx] = _user;
	string nickname = "dummy_"+ to_string(dummyUserIdx);
	_user->SetDummyUserIdx(dummyUserIdx);
	dummyUserIdx++;
}

DummyUserSptr DummyUserManager::PeekDummyUser(int32_t _dummyUserIdx)
{
	LOCK_GUARDDING(dummyUserMapLock);
	auto finder = dummyUserMap.find(_dummyUserIdx);
	if(finder == dummyUserMap.end()) {
		return nullptr;
	}
	else {
		return finder->second;
	}
}

DummyUserSptr DummyUserManager::PopDummyUser(int32_t _dummyUserIdx)
{
	LOCK_GUARDDING(dummyUserMapLock);
	auto finder = dummyUserMap.find(_dummyUserIdx);
	DummyUserSptr ret = nullptr;
	if(finder != dummyUserMap.end()) {
		ret = finder->second;
		dummyUserMap.erase(finder);
	}
	return ret;
}

bool DummyUserManager::ReadyTestScenario()
{
	//todo : 추후 json file에서 읽어오도록 할 것.
	if(LoadScenarioFromFile() == false) {
		return false;
	}

	//DummyUser들에게 각자 실행할 Acts에 대해서 설정.
	LOCK_GUARDDING(dummyUserMapLock);
	for(auto _pair : dummyUserMap) {
		_pair.second->SetTestScenario(dumActs, false);
	}

	return true;
}

void DummyUserManager::DoTestScenario()
{
	LOCK_GUARDDING(dummyUserMapLock);
	for (auto _pair : dummyUserMap) {
		_pair.second->DoDumAct();
	}
	return ;
}
