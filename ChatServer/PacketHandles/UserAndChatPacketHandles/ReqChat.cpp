#include "pch.h"
#include "UserAndChatPacketHandle.h"

namespace UserAndChatPacketHandle {
	bool ReqChat(UserSessionSptr _session, const UserAndChatServer::ReqChat& _packet) {
		CS_DEBUG_LOG("ReqChat called");
		auto chatUser = _session->GetChatUser();
		if(chatUser != nullptr) {
			//todo : 해당 유저의 room에 채팅 전달.
		}
		return true;
	}
}
