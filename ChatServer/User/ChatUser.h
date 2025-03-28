#pragma once

class ChatUser {
private:
	UserSessionWptr userSession;
	ChatProfile profile;
public:
	int64_t GetProfileId();
	UserSessionSptr GetSession();
	void SetSession(UserSessionSptr _session);
};