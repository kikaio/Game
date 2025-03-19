#include "pch.h"
#include "GameServerSession.h"

#define IMPL_GAME_SERVER_SEND_FUNC(_protoType, _protoName) \
bool GameServerSession::SendPacket##_protoType##_protoName(UserAndGameServer::##_protoType##_protoName& _packet)		\
{																														\
	SendBufferSptr sendBuf = GameServerPacketHandler::MakeSendBufferFromPacket(_packet);								\
	return TrySend(sendBuf);																							\
}																														\


bool GameServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	if(GameServerPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadLen) == false) {
			return false;	
	}
	return true;
}


void GameServerSession::SetDummyUser(DummyUserSptr _dum)
{
	dummyUserWptr = _dum;
}

DummyUserSptr GameServerSession::GetDummyUser()
{
	return dummyUserWptr.lock();
}

IMPL_GAME_SERVER_SEND_FUNC(Req, Chat);
IMPL_GAME_SERVER_SEND_FUNC(Req, Login);
IMPL_GAME_SERVER_SEND_FUNC(Req, GameConn);

//bool GameServerSession::SendPacketReqChat(UserAndGameServer::ReqChat& _packet)
//{
//	SendBufferSptr sendBuff = GameServerPacketHandler::MakeSendBufferFromPacket(_packet);
//	return TrySend(sendBuff);
//}
//
//bool GameServerSession::SendPacketReqLogin(UserAndGameServer::ReqLogin& _packet)
//{
//	SendBufferSptr sendBuff = GameServerPacketHandler::MakeSendBufferFromPacket(_packet);
//	return TrySend(sendBuff);
//}
