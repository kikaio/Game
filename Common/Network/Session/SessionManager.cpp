#include "pch.h"
#include "Session.h"

void SessionManager::Push(string _sId, SessionSptr _session)
{
	LOCK_GUARDDING(sessionsLock);
	if(sessions.find(_sId) != sessions.end()) {
		//todo : assert and session key duplication err logging
		return ;
	}
	sessions.insert(make_pair(_sId, _session));
}

SessionSptr SessionManager::Get(string _sid)
{
	LOCK_GUARDDING(sessionsLock);
	if(sessions.find(_sid) == sessions.end()) {
		//todo : err logging
		return nullptr;
	}

	return sessions[_sid];
}

SessionSptr SessionManager::Pop(string _sid)
{
	LOCK_GUARDDING(sessionsLock);
	SessionSptr ret = nullptr;
	auto finder = sessions.find(_sid);
	if(finder == sessions.end()) {
		//todo : err logging
		return nullptr;
	}

	ret = sessions[_sid];
	sessions.erase(finder);
	return ret;
}

string SessionManager::GenSessionId()
{
	auto curTimeStr = ClockUtil::GetNowStrWithMilli();
	string ret = to_string(regionNo) + '_' + to_string(serverNo) + '_' + curTimeStr;
	//todo : encrypt?
	return ret;
}
