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
	
	while(true) {
		if (_dataSize< HEADER_BUF_SIZE) {
			break;
		}
		HEADER_BUF_TYPE_VAL* curHeader = reinterpret_cast<HEADER_BUF_TYPE_VAL*>(_buf + proceedBytes);
		int32_t payloadLen = *curHeader;
		//curHeader 는 실제 contents의 길이를 저장 중.
		if (_dataSize < HEADER_BUF_SIZE + payloadLen) {
			break;
		}
		BYTE* payloadPtr = reinterpret_cast<BYTE*>(++curHeader);
		//온전히 packet을 읽는 상태.
		ASSERT_CRASH(OnPacketRecved(payloadPtr, *curHeader));
	
		proceedBytes += HEADER_BUF_SIZE + payloadLen;
		_dataSize -= HEADER_BUF_SIZE + payloadLen;
	}
	return proceedBytes;
}

void Session::AfterAccepted(SessionSptr _session)
{
	//Accept 완료 된 session에 session id 지정.
	_session->sId = _session->netCore->GetSessionMgr().GenSessionId();
	_session->netCore->GetSessionMgr().PushSession(_session);
	return ;
}

void Session::AfterConnected()
{
	netCore->GetSessionMgr().PushSession(GetSession());
}

void Session::AfterDisconnected()
{
	netCore->GetSessionMgr().PopSession(GetSession());
}

bool Session::OnPacketRecved(BYTE* _payloadPtr, uint32_t payloadBytes)
{
	PAYLOAD_INFO protocolNo = *(reinterpret_cast<PAYLOAD_INFO*>(_payloadPtr));
	printf("protocol no : %d, payloadBytes = %d\n", protocolNo);
	return true;
}
