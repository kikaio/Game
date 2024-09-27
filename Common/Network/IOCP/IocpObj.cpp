#include "pch.h"
#include "IocpObj.h"

IocpObj::IocpObj()
{
	sock = SocketUtil::CreateIocpTCP();
	netAddrSptr = MakeShared<NetAddr>();
}

IocpObj::~IocpObj()
{
	
	if (isConnected.load()) {
		closesocket(sock);
	}
	for (IocpAccept* _ptr : acceptEvents) {
		xfree(_ptr);
	}
}

void IocpObj::SetSockOpts()
{
	SocketUtil::SetReuse(sock, true);
	SocketUtil::SetLinger(sock, 0, 0);
}

bool IocpObj::Bind()
{
	int ret = ::bind(sock, netAddrSptr->SockAddr(), sizeof(SOCKADDR));
	return ret != SOCKET_ERROR;
}
bool IocpObj::Listen(UInt32 _backlog)
{
	SocketUtil::SetConditionalAccept(sock);
	int ret = ::listen(sock, _backlog);
	return ret != SOCKET_ERROR;
}

SOCKADDR* IocpObj::SockAddr()
{
	if (netAddrSptr == nullptr) {
		return nullptr;
	}
	return netAddrSptr->SockAddr();
}

NetAddrSptr IocpObj::Net()
{
	return netAddrSptr;
}

SOCKET IocpObj::Sock()
{
	return sock;
}

void IocpObj::DoAccept(IocpAccept* _accepter)
{
	SessionSptr _clientSession = NetworkCore::CreateSessionFactory();
	_accepter->Init();
	_accepter->session = _clientSession;

	if (SocketUtil::AcceptEx(_accepter->owner, _accepter, _clientSession) == false) {
		UInt32 err = WSAGetLastError();
		if (err != ERROR_IO_PENDING) {
			printf("soket util's acceptEx failed - %d\n", err);
			// todo : ASSERT
			DoAccept(_accepter);
			return;
		}
	}
}

void IocpObj::DoConnect()
{
	iocpConnect.Init();
	iocpConnect.owner = shared_from_this();
	if (SocketUtil::ConnectEx(sock, iocpCore->GetNetTarget()->SockAddr(), &iocpConnect) == false) {
		if (WSAGetLastError() != WSA_IO_PENDING) {
			printf("connect Ex failed. try again..\n");
			DoConnect();
			return;
		}
	}
}

void IocpObj::TryAccept()
{
	printf("Try Accept called\n");
	IocpAccept* accepter = xnew<IocpAccept>();
	acceptEvents.push_back(accepter);
	accepter->owner = shared_from_this();
	if (iocpCore->RegistToIocp(sock) == false) {
		int err = WSAGetLastError();
		printf("RegistListener failed. err : %d\n", err);
		return;
	}
	DoAccept(accepter);
}

void IocpObj::OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session)
{
	printf("accepted!\n");
	if (SocketUtil::UpdateAcceptToSock(_session->sock, sock) == false) {
		DoAccept(_iocpAccept);
		return;
	}
	_session->iocpRecv.owner = _session;
	_session->SetIocpCore(iocpCore);
	if (iocpCore->RegistToIocp(_session->sock) == false) {
		printf("Session Accepte Dispatch failed.\n");
		// todo : ASSERT
		return;
	}
	//Recv 등록.
	//session->TryRecv();

	DoAccept(_iocpAccept);
}

void IocpObj::TryConnect()
{
	printf("try connect called\n");
	DoConnect();
}

void IocpObj::OnConnected()
{
	isConnected.store(true);
	printf("Session : On Connected called\n");
}

void IocpObj::SetIocpCore(IocpCoreSptr _iocpCore)
{
	iocpCore = _iocpCore;
}

void IocpObj::DispatchEvent(IocpEvent* _event, UInt32 _bytes)
{
	switch (_event->Type()) {
	case IocpEvent::IOCP_EVENT::ACCEPT: {
		printf("On Accept!!");
		IocpAccept* iocpAccept = reinterpret_cast<IocpAccept*>(_event);
		SessionSptr session = iocpAccept->session;
		iocpAccept->Init();
		iocpAccept->AfterAccept();
		OnAccepted(iocpAccept, session);
		break;
	}
	case IocpEvent::IOCP_EVENT::CONNECT: {
		printf("On Connected\n");
		IocpConnect* iocpConnect = reinterpret_cast<IocpConnect*>(_event);
		iocpConnect->Init();
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
		printf("IocpObj DispatchEvent default case..?\n");
		return;
	}
	}
}
