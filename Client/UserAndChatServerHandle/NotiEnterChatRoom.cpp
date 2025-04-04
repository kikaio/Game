#include "pch.h"
#include "UserAndChatServerHandle.h"

bool UserAndChatServerHandle::NotiEnterChatRoom(SessionSptr _session, UserAndChatServer::NotiEnterChatRoom& _packet) {
	GET_CHAT_SERVER_SESSION_AND_DUM;
	
	return true;
}

