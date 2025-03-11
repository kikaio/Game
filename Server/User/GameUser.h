#pragma once

#include "GameProfile.h"

class GameUser : public enable_shared_from_this<GameUser>
{
private:
	int64_t accountId;
private:
	GameProfile profile;
public :
	GameUser();
public:
	GameProfile& GetProfile();
	void Render();
public:
	int64_t GetAccountId();
	void SetAccountId(int64_t _accountId);
};


