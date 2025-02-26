#pragma once


DECL_REF_USING(UserSession);
DECL_REF_USING(MasterSession);
DECL_REF_USING(GameUser);

struct LoginData {
public:
	string deviceKey = "";
};

struct LoginResultData {
	bool isSuccess = false;
};

struct UserProfile {
	string nickName = "";
};
