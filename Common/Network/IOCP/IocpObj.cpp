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
	printf("IocpObj released!\n");
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
		if (err != WSA_IO_PENDING) {
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

void IocpObj::DoDisconnect()
{
	iocpDisconnect.Init();
	iocpDisconnect.owner = shared_from_this();
	if (SocketUtil::DisconnectEx(sock, &iocpDisconnect) == false) {
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			printf("disconnect Ex failed. err : %d\n", err);
			DoDisconnect();
			return ;
		}
	}
}

void IocpObj::DoSend(BYTE* _buf, UInt32 _len)
{
	iocpSend.Init();
	iocpSend.owner = shared_from_this();
	iocpSend.buf = _buf;
	iocpSend.remainCnt = _len;
	if(SocketUtil::WSASend(sock, &iocpSend) == false) {
		int err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			DoSend(_buf, _len);
			return;
		}
	}
	return ;
}

void IocpObj::DoRecv()
{
	iocpRecv.Init();
	iocpRecv.owner = shared_from_this();
	if(SocketUtil::WSARecv(sock, &iocpRecv) == false) {
		int err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			printf("SocketUtil::WSARecv failed. err : %d\n", err);
			DoRecv();
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
		if(err != WSA_IO_PENDING) {
			DoAccept(accepter);
			printf("RegistListener failed. err : %d\n", err);
			return;
		}
	}
	DoAccept(accepter);
}

void IocpObj::OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session)
{
	printf("accepted!\n");
	_iocpAccept->Init();
	_iocpAccept->AfterAccept();


	if (SocketUtil::UpdateAcceptToSock(_session->sock, sock) == false) {
		DoAccept(_iocpAccept);
		return;
	}
	_session->iocpRecv.owner = _session;
	_session->SetIocpCore(iocpCore);
	if (iocpCore->RegistToIocp(_session->sock) == false) {
		int err = GetLastError();
		printf("Session Accepte Dispatch failed. err : %d\n", err);
		// todo : ASSERT
		DoAccept(_iocpAccept);
		return;
	}
	
	DoAccept(_iocpAccept);
	_session->TryRecv();
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

void IocpObj::TryDisconnect()
{
	DoDisconnect();
}

void IocpObj::OnDisconnect()
{
	iocpDisconnect.owner = nullptr;
	if (isConnected.load() == false) {
		return;
	}
	iocpDisconnect.Init();
	iocpDisconnect.owner = nullptr;
	isConnected.store(false);
	SocketUtil::CloseSocket(sock);
}

void IocpObj::TrySend(BYTE* _orig, UInt32 _len)
{
	printf("Try send called\n");
	DoSend(_orig, _len);
}

void IocpObj::OnSended(UInt32 _bytes)
{
	printf("OnSended called. bytes : %d\n", _bytes);
	iocpSend.owner = nullptr;
	printf("OnSended Called\n");
	if(_bytes == 0) {
		//todo : Discon
		TryDisconnect();
		return ;
	}

	int remainLen = iocpSend.remainCnt - _bytes;
	if(remainLen == 0) { 
		printf("send Complete\n");
		return;
	}
	else if (remainLen > 0) {
		TrySend(iocpSend.buf+_bytes, remainLen);
		return;
	}
	else {
		//todo ASSERT
		return ;
	}
	return ;
}

void IocpObj::TryRecv()
{
	printf("Try Recv Called\n");
	DoRecv();
}

void IocpObj::OnRecved(UInt32 _bytes)
{
	printf("OnRecved called. bytes : %d\n", _bytes);
	iocpRecv.owner = nullptr;
	if(_bytes == 0) {
		TryDisconnect();
		return ;
	}
	DoRecv();
}

void IocpObj::SetIocpCore(IocpCoreSptr _iocpCore)
{
	iocpCore = _iocpCore;
}

char testMsg[SMALL_BUF_SIZE] = "Wellcome to the Game!!\0";

void IocpObj::DispatchEvent(IocpEvent* _event, UInt32 _bytes)
{
	switch (_event->Type()) {
	case IocpEvent::IOCP_EVENT::ACCEPT: {
		printf("On Accept!!");
		IocpAccept* iocpAccept = reinterpret_cast<IocpAccept*>(_event);
		SessionSptr session = iocpAccept->session;
		OnAccepted(iocpAccept, session);
		break;
	}
	case IocpEvent::IOCP_EVENT::CONNECT: {
		printf("On Connected\n");
		IocpConnect* iocpConnect = reinterpret_cast<IocpConnect*>(_event);
		OnConnected();
		break;
	}
	case IocpEvent::IOCP_EVENT::RECV: {
		OnRecved(_bytes);
		break;
	}
	case IocpEvent::IOCP_EVENT::SEND: {
		OnSended(_bytes);
		break;
	}
	case IocpEvent::IOCP_EVENT::DISCONNECT: {
		IocpDisconnect* iocpDisconn = reinterpret_cast<IocpDisconnect*>(_event);
		OnDisconnect();
		break;
	}
	default: {
		//todo : ASSERT
		printf("IocpObj DispatchEvent default case..?\n");
		return;
	}
	}
}
