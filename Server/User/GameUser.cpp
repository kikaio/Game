#include "pch.h"
#include "GameUser.h"


GameUser::GameUser() {

}

void GameUser::Render() {
	profile.Render();
}
GameProfile& GameUser::GetProfile() {
	return profile;
}

int64_t GameUser::GetAccountId() {
	return accountId;
}


void GameUser::SetAccountId(int64_t _accountId) {
	accountId = _accountId;
	profile.SetAccountId(_accountId);
	return;
}

