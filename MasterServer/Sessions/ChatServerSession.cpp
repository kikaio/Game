#include "pch.h"
#include "ChatServerSession.h"


#define IMPLL_CHAT_SERVER_SESSION_SEND_PACKET(_msgType, _protocolType)									\
bool ChatServerSession::SendPacket(const MasterAndChatServer::##_msgType##_protocolType& _packet)		\
{																										\
	SendBufferSptr sendBuf = ChatServerDiscriminator::MakePacket##_msgType##_protocolType(_packet);		\
	return TrySend(sendBuf);																			\
}																										\




ChatServerSession::~ChatServerSession()
{
	printf("ChatServerSession released\n");
}

bool ChatServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (ChatServerDiscriminator::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}

IMPLL_CHAT_SERVER_SESSION_SEND_PACKET(Ans, ChatConnectMaster);
