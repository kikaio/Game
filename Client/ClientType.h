#pragma once


DECL_REF_USING(GameServerSession);
DECL_REF_USING(DumAct);
DECL_REF_USING(DummyUser);


struct LoginData {
	string deviceKey = "";
};

struct LoginResultData {
	bool isSuccess = false;
};