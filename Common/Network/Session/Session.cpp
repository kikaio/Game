#include "pch.h"
#include "Session.h"

Session::Session()
{
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);  //SocketUtil::CreateIocpTCP();
	netAddrSptr = MakeShared<NetAddr>();
}

Session::~Session()
{
	printf("session released");
}

SOCKADDR* Session::SockAddr()
{
	return netAddrSptr->SockAddr();
}

NetAddrSptr Session::Net()
{
	return netAddrSptr;
}

bool Session::Bind()
{
	return ::bind(sock, netAddrSptr->SockAddr(), sizeof(SOCKADDR)) != SOCKET_ERROR;
}

void Session::Dispatch(IocpEvent* _event, UInt32 _bytes)
{
	switch (_event->Type()) {
	case IocpEvent::IOCP_EVENT::CONNECT: {
		IocpConnect* iocpConnect = reinterpret_cast<IocpConnect*>(_event);
		iocpConnect->Init();
		iocpConnect->session = nullptr;
		OnConnected();
		break;
	}
	case IocpEvent::IOCP_EVENT::RECV: {
		break;
	}
	case IocpEvent::IOCP_EVENT::SEND: {
		break;
	}
	case IocpEvent::IOCP_EVENT::DISCONNECT: {
		break;
	}
	default: {
		//todo : ASSERT
		return;
	}
	}
}

void Session::TryConnect()
{
	printf("try connect colled\n");
	DoConnect();
}

void Session::DoConnect()
{
	iocpConnect.Init();
	iocpConnect.session = shared_from_this();
	if (SocketUtil::ConnectEx(sock, netAddrSptr->SockAddr(), &iocpConnect) == false) {
		if(WSAGetLastError() != WSA_IO_PENDING) {
			printf("connect Ex failed. try again..\n");
			DoConnect();
			return;
		}
	}
}

void Session::OnConnected()
{
	printf("Session : On Connected called\n");
}

