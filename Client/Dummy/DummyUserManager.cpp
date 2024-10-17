#include "pch.h"
#include "DummyUserManager.h"

void DummyUserManager::PushDummyUser(DummyUserSptr _user)
{
	LOCK_GUARDDING(dummyUserMapLock);
	dummyUserMap[dummyUserIdx] = _user;
	string nickname = "dummy_"+ to_string(dummyUserIdx);
	dummyUserIdx++;
	_user->SetNickname(nickname);
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
