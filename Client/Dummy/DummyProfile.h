#pragma once

struct DummyProfile
{
private:
	int64_t accountId = 0;
	string nickname = "";
	string greetingMent = "default greeting ment";
	uint32_t mainFrameId = 0;
	uint32_t mainHeroId = 0;
private:
	bool InvalidNicknameCheck(const string& _name);
	bool InvalidGreetingMentCheck(const string& _ment);
public:
	int64_t AccountId() const;
	const string& Nickname() const;
	const string& GreetingMent() const;
	uint32_t MainHeroId() const;
	uint32_t MainFrameId() const;
public:
	bool SetAccountId(int64_t _accountId);
	bool SetNickname(const string& _name);
	bool SetGreetingMent(const string& _ment);
	bool SetMainFrameId(uint32_t _id);
	bool SetMainHeroId(uint32_t _id);
public:
	void Clear();
};