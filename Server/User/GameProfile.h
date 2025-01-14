#pragma once

struct GameProfile
{
private:
	AccountId_t accountId = 0;
	string nickname = "";
	string greetingMent = "";
	uint32_t mainHeroId = 0;
	uint32_t mainFrameId = 0;
private:
	bool InvalidNickNameCheck(string& _name);
public:
	void Render();
public:
	AccountId_t AccountId();
	const string& NickName();
	const string& GreetingMent();
	const uint32_t& MainHeroId();
	const uint32_t& MainFrameId();
public:
	bool ChangeNickname(string _newName);
	bool ChangeGreetingMent(string _newMent);
	bool ChangeMainHeroId(uint32_t _newId);
	bool ChangeMainFrameId(uint32_t _newId);
	void Overllaped(const GameProfile& _other);
};


