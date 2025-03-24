#include "pch.h"
#include "MasterServerSession.h"

#define IMPL_MASTER_SERVER_SESSION_SEND_PACKET(_msgType, _protocolName)										\
bool MasterServerSession::SendPacket(const MasterAndChatServer::##_msgType##_protocolName& _packet)			\
{																											\
	SendBufferSptr sendBuf = MasterPacketDiscriminator::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																				\
}																											\


MasterServerSession::~MasterServerSession() {
	printf("MasterServerSession released\n");
}

bool MasterServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes) {

	if (MasterPacketDiscriminator::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}

IMPL_MASTER_SERVER_SESSION_SEND_PACKET(Req, ChatConnectMaster);
