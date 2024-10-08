#include "pch.h"
#include "DummySession.h"

bool DummySession::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadLen)
{
	//packet 판별
	printf("payload's len : %d\n", _payloadLen);
	string msg;
	BufReader br(_payloadPtr, _payloadLen);
	br.Read(msg);
	printf("msg : %s\n", msg.c_str());
	return true;
}
