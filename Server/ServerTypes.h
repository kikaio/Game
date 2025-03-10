#pragma once


DECL_REF_USING(UserSession);
DECL_REF_USING(MasterSession);
DECL_REF_USING(GameUser);

#define MAKE_PACKET_ERROR(_no, _detail) PacketError { ENUM_TO_INT(_no), ENUM_TO_INT(_detail) }

struct PacketError {
	int32_t err_no = 0;
	int32_t err_detail = 0;
	string err_desc = "";
};

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

struct ChatData {
	CHAT_TYPE chatType = CHAT_TYPE::NORMAL;
	ChatProfile chatProfile;
	string msg = "";
};


struct LoginData {
public:
	string sId = ""; // guest 인 경우 device key 가 온다.
	LOGIN_PLATFORM loginPlatform = LOGIN_PLATFORM::GUEST;
};

struct LoginResultData {
	bool isSuccess = false;
};
