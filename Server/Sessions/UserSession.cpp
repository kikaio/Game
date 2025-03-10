#include "pch.h"
#include "UserSession.h"

#define IMPL_USER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool UserSession::SendPacket(const UserAndGameServer::##_msgType##_protocolName& _packet)			\
{																									\
	SendBufferSptr sendBuf = ServerPacketHandler::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																		\
}																									\



UserSession::~UserSession()
{
	printf("UserSession released\n");
}

bool UserSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (ServerPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}

bool UserSession::SendError(const UserAndGameServer::NotiErrInfo& _err)
{
	SendBufferSptr sendBuf = ServerPacketHandler::MakePacketNotiErrInfo(_err);
	return TrySend(sendBuf);
}

bool UserSession::SendError(const PacketError& _err) {
	UserAndGameServer::NotiErrInfo _noti;
	ProtoConverter::ToPacket(_err, _noti);
	return SendError(_noti);
}


IMPL_USER_SESSION_SEND_PACKET(Noti, ErrInfo);
IMPL_USER_SESSION_SEND_PACKET(Ans, Chat);
IMPL_USER_SESSION_SEND_PACKET(Ans, Login);
