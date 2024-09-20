#include "pch.h"
#include "SocketUtil.h"



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

