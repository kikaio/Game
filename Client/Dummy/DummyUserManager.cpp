#include "pch.h"
#include "DummyUserManager.h"
#include "DummyUser.h"

void DummyUserManager::PushDummyUser(DummyUserSptr _user)
{
	LOCK_GUARDDING(dummyUserMapLock);
	dummyUserMap[dummyUserIdx] = _user;
	string nickname = "dummy_"+ to_string(dummyUserIdx);
	_user->SetNickname(nickname);
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
	//DumAct 항목 추가.
	auto _dumActSptr = MakeShared<DumActGameServerConnect>();
	dumActs.push_back(_dumActSptr);

	//DummyUser들에게 각자 실행할 Acts에 대해서 설정.
	LOCK_GUARDDING(dummyUserMapLock);
	for(auto _pair : dummyUserMap) {
		_pair.second->SetTestScenario(dumActs);
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
