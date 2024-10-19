#pragma once

class GameUser
{
public:
	GameUser(UserSessionSptr _session);
private:
	UserSessionSptr session;
public:
	UserSessionSptr GetSession();
};


