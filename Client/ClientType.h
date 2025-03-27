#pragma once

struct LoginData {
	string sId = "";
	LOGIN_PLATFORM loginPlatform = LOGIN_PLATFORM::GUEST;
	string loginToken = "";
	string refreshToken = "";
};

struct LoginResultData {
	bool isSuccess = false;
	string loginToken = "";
public:
	void Render();
};


enum class CHAT_TYPE {
	NORMAL,
	GUILD,
	NOTICE
};