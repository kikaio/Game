#include "pch.h"
#include "DummySession.h"

bool DummySession::OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadLen)
{
	//packet 판별
	printf("payload's len : %d\n", payloadLen);
	return true;
}
