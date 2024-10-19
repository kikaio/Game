#pragma once

struct GameProfile
{
public:
	uint64_t accountId = 0;
	string nickanme = "";
	string greetingMent = "";
	uint32_t mainHeroId = 0;
	uint32_t mainFrameId = 0;
private:
	bool InvalidNickNameCheck(string& _name);
public:
	void Render();
	bool ChangeNickname(string _newName);
	bool ChangeGreetingment(string _newMent);
	bool ChangeMainHeroId(uint32_t _newId);
	bool ChangeMainFrameId(uint32_t _newId);
};


