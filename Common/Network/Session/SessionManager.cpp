#include "pch.h"
#include "Session.h"

void SessionManager::PushSession(SessionSptr _session)
{
	LOCK_GUARDDING(sessionsLock);
	sessions.push_back(_session);


	//if(sessions.find(sId) != sessions.end()) {
	//	//todo : session key duplication err logging
	//	printf("session key not exist. sid : %s\n", sId.c_str());
	//	CRASH("session key not exist");
	//	return ;
	//}
	//sessions.insert(make_pair(sId, _session));
}

SessionSptr SessionManager::GetSession(string _sid)
{
	LOCK_GUARDDING(sessionsLock);
	for(SessionSptr _session : sessions) {
		if(_session->GetSId().compare(_sid) == 0) {
			return _session;
		}
	}
	return nullptr;

	//if(sessions.find(_sid) == sessions.end()) {
	//	//todo : err logging
	//	return nullptr;
	//}

	//return sessions[_sid];
}

SessionSptr SessionManager::PopSession(string _sid)
{
	LOCK_GUARDDING(sessionsLock);
	auto finder = find_if(sessions.begin(), sessions.end(), [_sid](SessionSptr _session){
		return _sid.compare(_session->GetSId());
	});
	SessionSptr ret = nullptr;
	if(finder != sessions.end()) {
		ret = *finder;
		sessions.erase(finder);
	}
	return ret;

	//SessionSptr ret = nullptr;
	//auto finder = sessions.find(_sid);
	//if(finder == sessions.end()) {
	//	//todo : err logging
	//	return nullptr;
	//}

	//ret = sessions[_sid];
	//sessions.erase(finder);
	return ret;
}

string SessionManager::GenSessionId()
{
	auto curTimeStr = ClockUtil::GetNowStrWithMilli();
	string ret = to_string(regionNo) + '_' + to_string(serverNo) + '_' + curTimeStr;
	//todo : encrypt?
	return ret;
}
