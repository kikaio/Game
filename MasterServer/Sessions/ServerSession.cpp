#include "pch.h"
#include "ServerSession.h"

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

//IMPL_USER_SESSION_SEND_PACKET(Ans, MasterServerConnect);