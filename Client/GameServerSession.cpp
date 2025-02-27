#include "pch.h"
#include "GameServerSession.h"

bool GameServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	if(ClientPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadLen) == false) {
			return false;	
	}
	return true;
}

bool GameServerSession::SendPacketReqChat(UserAndGameServer::ReqChat& _packet)
{
	SendBufferSptr sendBuff = ClientPacketHandler::MakeSendBufferFromPacket(_packet);
	return TrySend(sendBuff);
}