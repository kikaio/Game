#include "pch.h"
#include "GameServerSession.h"


bool GameServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	if(GameServerPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadLen) == false) {
			return false;	
	}
	return true;
}

bool GameServerSession::SendPacketReqChat(UserAndGameServer::ReqChat& _packet)
{
	SendBufferSptr sendBuff = GameServerPacketHandler::MakeSendBufferFromPacket(_packet);
	return TrySend(sendBuff);
}

bool GameServerSession::SendPacketReqLogin(UserAndGameServer::ReqLogin& _packet)
{
	SendBufferSptr sendBuff = GameServerPacketHandler::MakeSendBufferFromPacket(_packet);
	return TrySend(sendBuff);
}

void GameServerSession::SetDummyUser(DummyUserSptr _dum)
{
	dummyUserWptr = _dum;
}

DummyUserSptr GameServerSession::GetDummyUser()
{
	return dummyUserWptr.lock();
}

