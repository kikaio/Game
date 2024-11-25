#include "pch.h"
#include "ServerSession.h"

ServerSession::~ServerSession()
{
	printf("Server Session released\n");
}

bool ServerSession::OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes)
{
	return true;
}
