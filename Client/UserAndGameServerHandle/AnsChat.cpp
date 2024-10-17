#include "pch.h"
#include "UserAndGameServerHandle.h"
namespace UserAndGameServerHandle {

	bool AnsChat(SessionSptr _session, UserAndGameServer::AnsChat& _packet) {
		UserAndGameServer::ChatInfo* chatInfo = _packet.mutable_chat_info();
		UserAndGameServer::UserProfile* userProfile = chatInfo->mutable_user_profile();
		printf("[%s] : %s\n", userProfile->nick_name().c_str(), chatInfo->msg());
		return true;
	}
}