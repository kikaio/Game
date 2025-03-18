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

int64_t DummyProfile::AccountId() const
{
	return accountId;
}

const string& DummyProfile::Nickname() const
{
	return nickname;
}

const string& DummyProfile::GreetingMent() const
{
	return greetingMent;
}

uint32_t DummyProfile::MainHeroId() const
{
	return mainHeroId;
}

uint32_t DummyProfile::MainFrameId() const
{
	return mainFrameId;
}

bool DummyProfile::SetAccountId(int64_t _accountId)
{
	accountId = _accountId;
	return true;
}

bool DummyProfile::SetNickname(const string& _name)
{
	nickname = _name;
	return true;
}

bool DummyProfile::SetGreetingMent(const string& _ment)
{
	greetingMent = _ment;
	return true;
}

bool DummyProfile::SetMainFrameId(uint32_t _id)
{
	mainFrameId = _id;
	return true;
}

bool DummyProfile::SetMainHeroId(uint32_t _id)
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

void DummyProfile::Render()
{
	DUM_DEBUG_LOG("[Profile]=====================");
	DUM_DEBUG_LOG("account id : {}", accountId);
	DUM_DEBUG_LOG("nickname : {}", nickname);
	DUM_DEBUG_LOG("greetingMent : {}", greetingMent);
	DUM_DEBUG_LOG("main hero id : {}", mainHeroId);
	DUM_DEBUG_LOG("main frame : {}", mainFrameId);
}
