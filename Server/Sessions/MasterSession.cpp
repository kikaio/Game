#include "pch.h"
#include "MasterSession.h"

MasterSession ::~MasterSession()
{
	printf("MasterSession  released\n");
}

bool MasterSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (MasterPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		// todo : error logging
		return false;
	}
	return true;
}


IMPL_MASTER_SESSION_SEND_PACKET(Req, MasterServerConnect);