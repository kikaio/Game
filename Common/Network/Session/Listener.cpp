#include "pch.h"
#include "Listener.h"

Listener::Listener(NetAddrSptr _ref)
	: netAddrSptr(_ref)
{
	sock = SocketUtil::CreateIocpTCP();
}

void Listener::DoAccept(IocpCoreSptr _iocpCore, IocpAccept* _accepter)
{
	SessionSptr reserveSession = MakeShared<Session>();

	if(SocketUtil::AcceptEx(shared_from_this(), _accepter, reserveSession) == false) {
		UInt32 err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			printf("soket util's acceptEx failed - %d\n", err);
			// todo : ASSERT
			DoAccept(_iocpCore, _accepter);
			return;
		}
	}
}

void Listener::OnAccepted(SessionSptr _session)
{
	printf("accepted!\n");
	SocketUtil::UpdateAcceptToSock(_session->sock, sock);
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
	IocpAccept* accepter = xnew<IocpAccept>();
	accepter->listener = shared_from_this();
	acceptEvents.push_back(accepter);
	accepter->Init();
	_iocpCore->RegistListener(sock, accepter);
	DoAccept(_iocpCore, accepter);
}
