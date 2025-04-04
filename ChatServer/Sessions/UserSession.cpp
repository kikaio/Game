#include "pch.h"
#include "UserSession.h"

#define IMPL_USER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool UserSession::SendPacket(const UserAndChatServer::##_msgType##_protocolName& _packet)			\
{																									\
	SendBufferSptr sendBuf = UserPacketDiscriminator::MakePacket##_msgType##_protocolName(_packet);	\
	return TrySend(sendBuf);																		\
}				


ChatUserSptr UserSession::GetChatUser()
{
	return chatUser;
}

void UserSession::SetChatUser(ChatUserSptr _user)
{
	chatUser = _user;
}

bool UserSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (UserPacketDiscriminator::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}

IMPL_USER_SESSION_SEND_PACKET(Noti, Chat);
IMPL_USER_SESSION_SEND_PACKET(Ans, ChatConn);
IMPL_USER_SESSION_SEND_PACKET(Noti, EnterChatRoom);
IMPL_USER_SESSION_SEND_PACKET(Noti, LeaveChatRoom);
