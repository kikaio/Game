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
	int64_t AccountId() const ;
	void SetAccountId(int64_t _aid);
	const string& GreetingMent() const;
	const uint32_t& MainHeroId() const;
	const uint32_t& MainFrameId() const;
public:
	void InitGameProfile(ProfileRow profileRow);
};


