#include "pch.h"
#include "SocketUtil.h"


LPFN_ACCEPTEX SocketUtil::lpfnAcceptEx = nullptr;
LPFN_CONNECTEX SocketUtil::lpfnConnectEx = nullptr;
LPFN_DISCONNECTEX SocketUtil::lpfnDisconnectEx = nullptr;

GUID SocketUtil::guidAcceptEx = WSAID_ACCEPTEX;
GUID SocketUtil::guidConnectEx = WSAID_CONNECTEX;
GUID SocketUtil::guidDisconnectEx = WSAID_DISCONNECTEX;

BOOL SocketUtil::SetExFunctions()
{
	if(SetAcceptFunc() == false) {
		printf("SetAcceptFunc failed\n");
		return false;
	}
	if (SetConnectFunc() == false) {
		printf("SetConnectFunc failed\n");
		return false;
	}
	if (SetDisconnectFunc() == false) {
		printf("SetDisconnectFunc failed\n");
		return false;
	}

	return true;
}

SOCKET SocketUtil::CreateTCP()
{
	return ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

SOCKET SocketUtil::CreateIocpTCP()
{
	return WSASocket(AF_INET, SOCK_STREAM, IPPROTO_TCP, nullptr, NULL, WSA_FLAG_OVERLAPPED);
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

	return ret != SOCKET_ERROR;
}

BOOL SocketUtil::UpdateConnectToSock(SOCKET _client)
{
	UInt32 ret = setsockopt(_client
		, SOL_SOCKET, SO_UPDATE_CONNECT_CONTEXT
		, nullptr, NULL
	);

	return ret != SOCKET_ERROR;
}

BOOL SocketUtil::CloseSocket(SOCKET _sock)
{
	return closesocket(_sock) == NO_ERROR;
}

BOOL SocketUtil::AcceptEx(IocpObjSptr _listener, IocpAccept* _accepter, SessionSptr _client)
{
	int addrSize = sizeof(*_client->SockAddr());
	DWORD dwBytes = 0;
//	_accepter->Init();
//	_accepter->session = _client;

	const UInt32 bufferLen = 1024;
	array<CHAR, bufferLen> tmpBuff = {};
	return lpfnAcceptEx(_listener->Sock(), _client->Sock()
		, tmpBuff.data(), 0
		, addrSize + 16, addrSize + 16
		, OUT &dwBytes, reinterpret_cast<LPOVERLAPPED>(_accepter)
	);
}

BOOL SocketUtil::ConnectEx(SOCKET _sock, const SOCKADDR* _addr, IocpConnect* _event)
{
	DWORD bytes = 0;
	const int bufSize = 1024;
	array<char, bufSize> tmpBuff = {0, };
	int ret = lpfnConnectEx(
		_sock, reinterpret_cast<const SOCKADDR*>(_addr)
		, sizeof(SOCKADDR)
		, nullptr, 0, nullptr, _event
	);
	return ret != SOCKET_ERROR;
}

BOOL SocketUtil::DisconnectEx(SOCKET _sock, IocpDisconnect* _event)
{
	return lpfnDisconnectEx(_sock, _event, TF_REUSE_SOCKET, NULL);
}

BOOL SocketUtil::SetAcceptFunc()
{
	SOCKET _sock = SocketUtil::CreateIocpTCP();
	return SetIocpWSAIoctl(_sock, lpfnAcceptEx, guidAcceptEx);
}

BOOL SocketUtil::SetConnectFunc()
{
	SOCKET _sock = SocketUtil::CreateIocpTCP();
	return SetIocpWSAIoctl(_sock, lpfnConnectEx, guidConnectEx);
}

BOOL SocketUtil::SetDisconnectFunc()
{
	SOCKET _sock = SocketUtil::CreateIocpTCP();
	return SetIocpWSAIoctl(_sock, lpfnDisconnectEx, guidDisconnectEx);
}

