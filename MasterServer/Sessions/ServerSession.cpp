#include "pch.h"
#include "ServerSession.h"
#include "GamePacketHandler.h"
#include "MasterDefines.h"

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


IMPL_SERVER_SESSION_SEND_GAME_PACKET(Ans, MasterServerConnect);