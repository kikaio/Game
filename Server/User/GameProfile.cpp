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
}

bool GameProfile::ChangeNickname(string _newName)
{
    return false;
}

bool GameProfile::ChangeGreetingment(string _newMent)
{
    return false;
}

bool GameProfile::ChangeMainHeroId(uint32_t _newId)
{
    return false;
}

bool GameProfile::ChangeMainFrameId(uint32_t _newId)
{
    return false;
}
