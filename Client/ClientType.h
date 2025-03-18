#pragma once


struct UserProfile {
	int32_t profileId = 0;
	int32_t accountLv = 0;
	string nickName = "";
	string greetingMent = "";
	int32_t profileHeroId = 0;
	int32_t profileFrameId = 0;
	int32_t mainHeroId = 0;
};

struct ChatProfile {
	int32_t profileId = 0;
	string nickName = "";
	int32_t profileHeroId = 0;
	int32_t profileFrameId = 0;
	int32_t mainHeroId = 0;
};

struct LoginData {
	string sId = "";
	LOGIN_PLATFORM loginPlatform = LOGIN_PLATFORM::GUEST;
	string loginToken = "";
};

struct LoginResultData {
	bool isSuccess = false;
};

struct ChatData {
	CHAT_TYPE chatType = CHAT_TYPE::NORMAL;
	ChatProfile chatProfile;
	string msg = "";
};

