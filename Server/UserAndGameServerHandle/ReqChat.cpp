#include "pch.h"
#include "UserAndGameServerHandle.h"


bool ReqChat(SessionSptr _session, UserAndGameServer::ReqChat& _packet) {
	
	auto curNetCore = _session->GetNetCore();
	if (curNetCore == nullptr) {
		return false;
	}

	UserAndGameServer::AnsChat ans;

	return true;
}
