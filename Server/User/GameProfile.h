#pragma once

struct GameProfile
{
private:
	int64_t accountId = 0;
	string greetingMent = "";
	uint32_t mainHeroId = 0;
	uint32_t mainFrameId = 0;
private:
	bool InvalidNickNameCheck(string& _name);
public:
	void Render();
public:
	int64_t AccountId();
	const string& GreetingMent();
	const uint32_t& MainHeroId();
	const uint32_t& MainFrameId();
public:
	void SetAccountId(int64_t _accountId);
	bool ChangeGreetingMent(string _newMent);
	bool ChangeMainHeroId(uint32_t _newId);
	bool ChangeMainFrameId(uint32_t _newId);
};


