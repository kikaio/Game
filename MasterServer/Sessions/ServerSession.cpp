#include "pch.h"
#include "ServerSession.h"

#define IMPL_SERVER_SESSION_SEND_GAME_PACKET(_msgType, _protocolName)								\
bool ServerSession::SendPacket(const MasterAndGameServer::##_msgType##_protocolName& _packet)		\
{																									\
	SendBufferSptr sendBuf = GamePacketHandler::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																		\
}																									\





ServerSession::~ServerSession()
{
	printf("Server Session released\n");
}

bool ServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (GamePacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}


bool ServerSession::SendPacket(const MasterAndGameServer::AnsMasterServerConnect& _packet) {
	SendBufferSptr sendBuf = GamePacketHandler::MakePacketAnsMasterServerConnect(_packet); return TrySend(sendBuf);
};