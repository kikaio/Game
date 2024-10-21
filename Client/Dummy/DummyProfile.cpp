#include "pch.h"
#include "DummyProfile.h"

bool DummyProfile::InvalidNicknameCheck(const string& _name)
{
	//todo : 비속어, 금지어 체크할 것.
	return true;
}

bool DummyProfile::InvalidGreetingMentCheck(const string& _ment)
{
	//todo : 비속어 이런거 체크 할것.
	return true;
}

AccountId_t DummyProfile::AccountId()
{
	return accountId;
}

const string& DummyProfile::Nickname()
{
	return nickname;
}

const string& DummyProfile::GreetingMent()
{
	return greetingMent;
}

uint32_t DummyProfile::MainHeroId()
{
	return mainHeroId;
}

uint32_t DummyProfile::MainFrameId()
{
	return mainFrameId;
}

bool DummyProfile::ChangeNickname(const string& _name)
{
	nickname = _name;
	return true;
}

bool DummyProfile::ChangeGreetingMent(const string& _ment)
{
	greetingMent = _ment;
	return true;
}

bool DummyProfile::ChangeMainFrameId(uint32_t _id)
{
	mainFrameId = _id;
	return true;
}

bool DummyProfile::ChangeMainHeroId(uint32_t _id)
{
	mainHeroId = _id;
	return true;
}

void DummyProfile::Clear()
{
	accountId = 0;
	nickname = "";
	greetingMent = "";
	mainFrameId = 0;
	mainHeroId = 0;
}
