#pragma once


DECL_REF_USING(DummyUser);
DECL_REF_USING(DummySession);


struct LoginData {
	string deviceKey = "";
};

struct LoginResultData {
	bool isSuccess = false;
};