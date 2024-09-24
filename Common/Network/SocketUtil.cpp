#include "pch.h"
#include "SocketUtil.h"


LPFN_ACCEPTEX SocketUtil::lpfnAcceptEx = nullptr;
LPFN_CONNECTEX SocketUtil::lpfnConnectEx = nullptr;
LPFN_DISCONNECTEX SocketUtil::lpfnDisconnectEx = nullptr;

GUID SocketUtil::guidAcceptEx = WSAID_ACCEPTEX;
GUID SocketUtil::guidConnectEx = WSAID_CONNECTEX;
GUID SocketUtil::guidDisconnectEx = WSAID_DISCONNECTEX;

SOCKET SocketUtil::CreateTCP()
{
	return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

SOCKET SocketUtil::CreateIocpTCP()
{
	return WSASocket(AF_INET, SOCK_STREAM, IPPROTO_IP, nullptr, NULL, WSA_FLAG_OVERLAPPED);
}

SOCKET SocketUtil::CreateUDP()
{
	return ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
}

void SocketUtil::SetReuse(SOCKET _sock, bool _flag)
{
	::setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&_flag), sizeof(_flag));
}

void SocketUtil::SetLinger(SOCKET _sock, DWORD _onoff, DWORD _linger)
{
	::setsockopt(_sock, SO_LINGER, _onoff, reinterpret_cast<const char*>(&_linger), sizeof(_linger));
}

void SocketUtil::SetConditionalAccept(SOCKET _listener)
{
	//AcceptEx를 호출하기 전에 listen이 호출되는 것을 방지한다.[?]
	bool flag = true;
	::setsockopt(_listener, SOL_SOCKET, SO_CONDITIONAL_ACCEPT, (char*)&flag, sizeof(flag));
}

BOOL SocketUtil::UpdateAcceptToSock(SOCKET _accepted, SOCKET _listener)
{
	UInt32 ret = setsockopt(_accepted
		, SOL_SOCKET, SO_UPDATE_ACCEPT_CONTEXT
		, (char*)&_listener, sizeof(_listener)
	);

	return ret == NO_ERROR;
}

BOOL SocketUtil::AcceptEx(ListenerSptr _listener, SessionSptr _client)
{
	int addrSize = sizeof(*_client->SockAddr());
	DWORD dwBytes = 0;

	_client->iocpAccept.session = _client;

	const UInt32 bufferLen = 256;
	array<CHAR, bufferLen> tmpBuff = {};
	return lpfnAcceptEx(_listener->Sock(), _client->sock
		, tmpBuff.data(), NULL, addrSize + 16, addrSize + 16
		, &dwBytes, reinterpret_cast<LPOVERLAPPED>(&_client->iocpAccept)
	);
}

BOOL SocketUtil::SetAcceptableListener(SOCKET _sock)
{
	DWORD dwBytes = 0;
	int ret = WSAIoctl(_sock, SIO_GET_EXTENSION_FUNCTION_POINTER
		, &guidAcceptEx, sizeof(guidAcceptEx)
		, &lpfnAcceptEx, sizeof(lpfnAcceptEx)
		, &dwBytes, nullptr, nullptr
	);

	return ret == NO_ERROR;
}

