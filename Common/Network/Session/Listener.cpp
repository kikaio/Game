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
			printf("soket util's acceptEx failed - %d\n", err);
			// todo : ASSERT
			DoAccept(_iocpCore);
			return;
		}
	}

	if(_iocpCore->RegistToIocp(reserveSession) == false) {
		printf("client socket regist to Iocp is failed.\n");
		DoAccept(_iocpCore);
		return ;
	}
	
	if (SocketUtil::UpdateAcceptToSock(reserveSession->sock, sock) == false) {
		//todo : ASSERT
		printf("UpdateAcceptToSock failed\n");
		return;
	}
}

void Listener::OnAccepted()
{
}

bool Listener::Bind()
{
	SocketUtil::SetReuse(sock, true);
	SocketUtil::SetLinger(sock, 0, 0);
	int ret = ::bind(sock, netAddrSptr->SockAddr(), sizeof(SOCKADDR));
	return ret != SOCKET_ERROR;
}

bool Listener::Listen()
{
	SocketUtil::SetConditionalAccept(sock);
	int ret = ::listen(sock, backLog);
	return ret != SOCKET_ERROR;
}
void Listener::TryAccept(IocpCoreSptr _iocpCore)
{
	DoAccept(_iocpCore);
}
