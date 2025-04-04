#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::NotiLeaveChatRoom(SessionSptr _session, UserAndChatServer::NotiLeaveChatRoom& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	
	return true;
}

