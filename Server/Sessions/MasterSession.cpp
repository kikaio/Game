#include "pch.h"
#include "MasterSession.h"



#define IMPL_MASTER_SESSION_SEND_PACKET(_msgType, _protocolName)											\
bool MasterSession::SendPacket(const MasterAndGameServer::##_msgType##_protocolName& _packet)				\
{																											\
	SendBufferSptr sendBuf = MasterPacketDiscriminator::MakePacket##_msgType##_protocolName(_packet);		\
	return TrySend(sendBuf);																				\
}																											\




MasterSession ::~MasterSession()
{
	printf("MasterSession  released\n");
}

bool MasterSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (MasterPacketDiscriminator::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		// todo : error logging
		return false;
	}
	return true;
}


IMPL_MASTER_SESSION_SEND_PACKET(Req, MasterServerConnect);