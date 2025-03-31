#include "pch.h"
#include "ChatProfile.h"

void ChatProfile::SetAccountId(int64_t _id)
{
    accountId = _id;
}

void ChatProfile::SetNickName(const string& _name)
{
    nickName = _name;
}

void ChatProfile::SetProfileHeroId(int64_t _id)
{
    profileHeroId = _id;
}

void ChatProfile::SetProfileFrameId(int64_t _id)
{
    profileFrameId = _id;
}

int64_t ChatProfile::GetAccountId() const
{
    return accountId;
}

const string& ChatProfile::GetNickName() const
{
    return nickName;
}

int64_t ChatProfile::GetProfileHeroId() const
{
    return profileHeroId;
}

int64_t ChatProfile::GetProfileFrameId() const
{
    return profileFrameId;
}

void ChatProfile::Render()
{
    DUM_DEBUG_LOG("[chat profile - accountId {}]======", accountId);
    DUM_DEBUG_LOG("nickname : {}, mainHeroId : {}, mainFrameId : {}"
        , nickName, profileHeroId, profileFrameId
    );
    DUM_DEBUG_LOG("===================");
}
