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

int64_t GameProfile::AccountId()
{
    return accountId;
}

const string& GameProfile::GreetingMent()
{
    return greetingMent;
}

const uint32_t& GameProfile::MainHeroId()
{
    return mainHeroId;
}

const uint32_t& GameProfile::MainFrameId()
{
    return mainFrameId;
}
void GameProfile::SetAccountId(int64_t _accountId) {
    accountId = _accountId;
}

bool GameProfile::ChangeGreetingMent(string _newMent)
{
    greetingMent = _newMent;
    return true;
}

bool GameProfile::ChangeMainHeroId(uint32_t _newId)
{
    //todo : plan data check.
    mainHeroId = _newId;
    return true;
}

bool GameProfile::ChangeMainFrameId(uint32_t _newId)
{
    //todo : plan data check
    mainFrameId = _newId;
    return true;
}
