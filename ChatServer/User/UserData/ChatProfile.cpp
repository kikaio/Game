#include "pch.h"
#include "ChatProfile.h"


void ChatProfile::SetProfileId(int64_t _id) {
	profileId = _id;
}

int64_t ChatProfile::GetProfileId() const {
	return profileId;
}


void ChatProfile::SetNickName(const string& _name) {
	nickName = _name;
}

const string& ChatProfile::GetNickName() const {
	return nickName;
}

void ChatProfile::SetMainHeroId(int64_t _id) {
	profileMainHeroId = _id;
}

int64_t ChatProfile::GetMainHeroId() const {
	return profileMainHeroId;
}

void ChatProfile::SetMainFrameId(int64_t _id) {
	profileMainFrameId = _id;
}

int64_t ChatProfile::GetMainFrameId() const {
	return profileMainFrameId;
}