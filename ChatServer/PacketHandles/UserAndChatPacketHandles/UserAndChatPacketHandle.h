#pragma once

#define DECL_USER_AND_CHAT_PACKET_HANDLE(_msgType, _protocolType)														\
bool _msgType##_protocolType(UserSessionSptr _session, const UserAndChatServer::##_msgType##_protocolType& _packet)		\


namespace UserAndChatPacketHandle {
	DECL_USER_AND_CHAT_PACKET_HANDLE(Req, Chat);
}