#include "pch.h"
#include "Listener.h"

Listener::Listener(NetAddrSptr _ref)
	: netAddrSptr(_ref)
{
	sock = SocketUtil::CreateIocpTCP();
}

bool Listener::Bind()
{
	return ::bind(sock, netAddrSptr->SockAddr(), sizeof(SOCKADDR)) == NO_ERROR;
}

bool Listener::Listen()
{
	SocketUtil::SetConditionalAccept(sock);
	SocketUtil::SetReuse(sock, true);
	SocketUtil::SetLinger(sock, 0, 0);
	return ::listen(sock, backLog) == NO_ERROR;
}

SOCKET Listener::Accept(SOCKADDR* _addr)
{
	int size = sizeof(SOCKADDR);
	return ::accept(sock, _addr, &size);
}
