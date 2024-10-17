#include "pch.h"
#include "UserSession.h"

UserSession::~UserSession()
{
	printf("UserSession released\n");
}

bool UserSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	ServerPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadBytes);
	return true;
}


IMPL_USER_SESSION_SEND_PACKET(Ans, Chat);