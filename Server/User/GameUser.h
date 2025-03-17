#pragma once

class GameUser : public enable_shared_from_this<GameUser>
{
private:
	int64_t accountId;
private:
	GameProfile profile;
	Inventory inventory;
public :
	GameUser();
public:
	GameProfile& GetProfile();
	Inventory& GetInventory();
	void Render();
public:
	int64_t GetAccountId();
	void SetAccountId(int64_t _accountId);
};


