#include "pch.h"
#include "UserSession.h"

UserSession::~UserSession()
{
	printf("UserSession released\n");
}

bool UserSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	if (ServerPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadBytes) == false) {
		//todo : error logging
		return false;
	}
	return true;
}


IMPL_USER_SESSION_SEND_PACKET(Ans, Chat);