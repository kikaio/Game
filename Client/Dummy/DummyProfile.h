#pragma once

struct DummyProfile 
{
private:
	AccountId_t accountId = 0;
	string nickname = "";
	string greetingMent = "default greeting ment";
	uint32_t mainFrameId = 0;
	uint32_t mainHeroId = 0;
private:
	bool InvalidNicknameCheck(const string& _name);
	bool InvalidGreetingMentCheck(const string& _ment);
public:
	AccountId_t AccountId();
	const string& Nickname();
	const string& GreetingMent();
	uint32_t MainHeroId();
	uint32_t MainFrameId();
public:
	bool ChangeNickname(const string& _name);
	bool ChangeGreetingMent(const string& _ment);
	bool ChangeMainFrameId(uint32_t _id);
	bool ChangeMainHeroId(uint32_t _id);
public:
	void Clear();
};