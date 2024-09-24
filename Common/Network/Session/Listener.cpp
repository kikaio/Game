#include "pch.h"
#include "Listener.h"

Listener::Listener(NetAddrSptr _ref)
	: netAddrSptr(_ref)
{
	sock = SocketUtil::CreateIocpTCP();
}

void Listener::DoAccept(IocpCoreSptr _iocpCore)
{
	SessionSptr reserveSession = MakeShared<Session>();
	if(SocketUtil::AcceptEx(shared_from_this(), reserveSession) == false) {
		UInt32 err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			// todo : ASSERT
		}
	}

	if(_iocpCore->RegistToIocp(reserveSession) == false) {
		TryAccept(_iocpCore);
		return ;
	}
}

void Listener::OnAccepted()
{
}

bool Listener::Bind()
{
	int ret = ::bind(sock, netAddrSptr->SockAddr(), sizeof(SOCKADDR));
	return ret == NO_ERROR;
}

bool Listener::Listen()
{
	SocketUtil::SetConditionalAccept(sock);
	SocketUtil::SetReuse(sock, true);
	SocketUtil::SetLinger(sock, 0, 0);
	int ret = ::listen(sock, backLog);
	return ret == NO_ERROR;
}
void Listener::TryAccept(IocpCoreSptr _iocpCore)
{
	DoAccept(_iocpCore);
}
