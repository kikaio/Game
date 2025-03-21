#include "pch.h"
#include "Session.h"

Session::Session()
	: IocpObj()
{
}

Session::~Session()
{
}

int32_t Session::AfterRecved(BYTE* _buf, UInt32 _dataSize)
{
	uint32_t proceedBytes = 0;
	auto headerSize = sizeof(PacketHeader);
	while(true) {

		if (_dataSize< headerSize) {
			break;
		}
		PacketHeader* curHeader = reinterpret_cast<PacketHeader*>(_buf + proceedBytes);
		uint32_t payloadLen = *curHeader;
		//curHeader 는 실제 contents의 길이를 저장 중.
		if (_dataSize < headerSize + payloadLen) {
			break;
		}
		BYTE* payloadPtr = reinterpret_cast<BYTE*>(++curHeader);
		//온전히 packet을 읽는 상태.
		ASSERT_CRASH(OnPacketRecved(payloadPtr, payloadLen));
	
		proceedBytes += (headerSize + payloadLen);
		_dataSize -= (headerSize + payloadLen);
	}
	return proceedBytes;
}

void Session::AfterConnected()
{
	netCore->GetSessionMgr().PushSession(GetSession());
	onSessionConenctedFunc();
}

void Session::AfterDisconnected()
{
	netCore->GetSessionMgr().PopSession(GetSession());
	onSessionDisconenctedFunc();
}

bool Session::OnPacketRecved(BYTE* _payloadPtr, uint32_t _payloadBytes)
{
	printf("payloadBytes = %d\n", _payloadBytes);
	return true;
}

void Session::SetOnSessionDisconnectedFunc(OnSessionDisconnectedFunc _func)
{
	onSessionDisconenctedFunc = _func;
}

void Session::SetOnSessionConnectedFunc(OnSessionConnectedFunc _func)
{
	onSessionConenctedFunc = _func;
}
