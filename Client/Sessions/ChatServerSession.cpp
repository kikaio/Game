#include "pch.h"
#include "ChatServerSession.h"

#define IMPL_CHAT_SERVER_SEND_FUNC(_protoType, _protoName) \
bool ChatServerSession::SendPacket##_protoType##_protoName(UserAndChatServer::##_protoType##_protoName& _packet)		\
{																														\
	SendBufferSptr sendBuf = ChatServerDiscriminator::MakeSendBufferFromPacket(_packet);								\
	return TrySend(sendBuf);																							\
}																														\


bool ChatServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	if(ChatServerDiscriminator::HandlePayload(GetSession(), _payloadPtr, _payloadLen) == false) {
			return false;	
	}
	return true;
}


void ChatServerSession::SetDummyUser(DummyUserSptr _dum)
{
	dummyUserWptr = _dum;
}

DummyUserSptr ChatServerSession::GetDummyUser()
{
	return dummyUserWptr.lock();
}

IMPL_CHAT_SERVER_SEND_FUNC(Req, ChatConn);
