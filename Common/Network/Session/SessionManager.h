﻿#pragma once

//iocp 용
class SessionManager
{
private:
	VAL_LOCK(sessionsLock);
//	map<string, SessionSptr> sessions;
	Vector<SessionSptr> sessions;
	UInt32 tag1 = 0;
	UInt32 tag2 = 0;
public:
	void SetTag(UInt32 _tag_1, UInt32 _tag_2);
public:
	void PushSession(SessionSptr _session);
	SessionSptr GetSession(string _sid);
	SessionSptr PopSession(string _sid); //sessions 에서 제거 후 반환.
	SessionSptr PopSession(SessionSptr _target);
	string GenSessionId();
public:
	void BroadCast(SendBufferSptr _sendBuffer);
};