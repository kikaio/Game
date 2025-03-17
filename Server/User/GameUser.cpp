#include "pch.h"
#include "GameUser.h"


GameUser::GameUser() {

}

void GameUser::Render() {
	profile.Render();
	inventory.Render();
}
GameProfile& GameUser::GetProfile() {
	return profile;
}

Inventory& GameUser::GetInventory()
{
	return inventory;
}

int64_t GameUser::GetAccountId() {
	return accountId;
}


void GameUser::SetAccountId(int64_t _accountId) {
	accountId = _accountId;
	profile.SetAccountId(_accountId);
	return;
}

