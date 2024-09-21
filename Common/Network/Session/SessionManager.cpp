#include "pch.h"
#include "Session.h"

void SessionManager::Push(SessionSptr _session)
{
}

SessionSptr SessionManager::Get(string _sid)
{
	return SessionSptr();
}

SessionSptr SessionManager::Pop(string _sid)
{
	return SessionSptr();
}

string SessionManager::GenSessionId()
{
	auto timePoint = chrono::system_clock::now();
	
	return string();
}
