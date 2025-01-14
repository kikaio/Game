#pragma once

#include "GameProfile.h"

class GameUser : public enable_shared_from_this<GameUser>
{
public:
	GameUser(UserSessionSptr _session);
private:
	UserSessionSptr session;
	GameProfile profile;
public:
	UserSessionSptr GetSession();
public:
	GameProfile* GetProfile();
public:
	bool ChangeNickname(string _name);
	bool ChangeGreetingment(string _ment);
	void OverlappedGameProfile(const GameProfile& _other);
public:
	GameUserSptr GetGameUser() {
		return shared_from_this();
	}
};


