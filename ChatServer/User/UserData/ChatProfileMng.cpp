#include "pch.h"
#include "ChatProfile.h"
#include "ChatProfileMng.h"

ChatProfileSptr ChatProfileMng::GetProfile(int64_t _profileId)
{
	auto iter = profiles.find(_profileId);
	if(iter == profiles.end()) {
		return nullptr;
	}
	return iter->second;
}

ChatProfileSptr ChatProfileMng::CreateProfile(int64_t _id
	, const string& _nickName
	, int64_t _mainHeroId
	, int64_t _mainFrameId
)
{
	ChatProfileSptr profile = MakeShared<ChatProfile>();
	profile->SetProfileId(_id);
	profile->SetNickName(_nickName);
	profile->SetMainHeroId(_mainHeroId);
	profile->SetMainFrameId(_mainFrameId);

	profiles[_id] = profile;
	return profile;
}

void ChatProfileMng::Clear()
{
	profiles.clear();
}
