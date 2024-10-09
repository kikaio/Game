#include "pch.h"
#include "DummySession.h"

bool DummySession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	if(ClientPacketHandler::HandlePayload(GetSession(), _payloadPtr, _payloadLen) == false) {
			return false;	
	}
	return true;
}
