#include "pch.h"
#include "GameProfile.h"
#include "GameProfile.h"

bool GameProfile::InvalidNickNameCheck(string& _name)
{
    //todo : check logic 추가 필수 [지금은 단순히 4글자 ~ 12글자 허용]
    return true;
}

void GameProfile::Render()
{
    printf("=========[game profile : %lld]========\n", accountId);
    printf("greeting ment : %s\n", greetingMent.c_str());
    printf("main hero id : %d\n", mainHeroId);
    printf("main frame id : %d\n", mainFrameId);
    printf("==============================================\n");
}

int64_t GameProfile::AccountId() const
{
    return accountId;
}

void GameProfile::SetAccountId(int64_t _aid)
{
    accountId = _aid;
}

const string& GameProfile::GreetingMent() const
{
    return greetingMent;
}

const uint32_t& GameProfile::MainHeroId() const 
{
    return mainHeroId;
}

const uint32_t& GameProfile::MainFrameId() const
{
    return mainFrameId;
}
void GameProfile::InitGameProfile(ProfileRow _profileRow)
{
    accountId = _profileRow.aId;
    greetingMent = _profileRow.greetingMent;
    mainHeroId = _profileRow.mainHeroId;
    mainFrameId = _profileRow.mainFrameId;
}
