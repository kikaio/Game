#include "pch.h"
#include "GameUser.h"

GameUser::GameUser(UserSessionSptr _session)
 : session(_session)
{
}

UserSessionSptr GameUser::GetSession()
{
	return session;
}

GameProfile* GameUser::GetProfile()
{
	return &profile;
}

bool GameUser::ChangeNickname(string _name)
{
	return profile.ChangeNickname(_name);
}

bool GameUser::ChangeGreetingment(string _ment)
{
	return profile.ChangeGreetingMent(_ment);
}

void GameUser::OverlappedGameProfile(const GameProfile& _other)
{
	profile.Overllaped(_other);
}
