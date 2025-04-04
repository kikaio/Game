#include "pch.h"
#include "UserAndChatPacketHandle.h"

namespace UserAndChatPacketHandle {
	bool ReqEnterChatRoom(UserSessionSptr _session, const UserAndChatServer::ReqEnterChatRoom& _packet) {
		CS_DEBUG_LOG("ReqEnterChatChat called");
		
		return true;
	}
}
