#pragma once

//iocp 용
class SessionManager : public Singleton<SessionManager>
{
private:
	VAL_LOCK(sessionsLock);
	map<string, SessionSptr> sessions;
	UInt32 regionNo = 0;
	UInt32 serverNo = 0;
public:
	void Push(string _sId, SessionSptr _session);
	SessionSptr Get(string _sid);
	SessionSptr Pop(string _sid); //sessions 에서 제거 후 반환.
	string GenSessionId();
};