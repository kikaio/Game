#pragma once

//iocp 용
class SessionManager
{
private:
	VAL_LOCK(sessionsLock);
//	map<string, SessionSptr> sessions;
	Vector<SessionSptr> sessions;
	UInt32 regionNo = 0;
	UInt32 serverNo = 0;
public:
	void PushSession(SessionSptr _session);
	SessionSptr GetSession(string _sid);
	SessionSptr PopSession(string _sid); //sessions 에서 제거 후 반환.
	string GenSessionId();
};