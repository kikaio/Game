#include "pch.h"
#include "IocpObj.h"

IocpObj::IocpObj()
{
	sock = SocketUtil::CreateIocpTCP();
	netAddrSptr = MakeShared<NetAddr>();
}

IocpObj::~IocpObj()
{
	for (IocpAccept* _ptr : acceptEvents) {
		xfree(_ptr);
	}
	SocketUtil::CloseSocket(sock);
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

void IocpObj::HandleError(int32_t _err)
{
	switch(_err){
	case WSAECONNABORTED:
	case WSAECONNRESET: { // 호스트가 연결이 끊김.
		TryDisconnect("server host disconnected..");
		break;
	}
	default:{
		printf("this error not handled. err : %d\n", _err);
		TryDisconnect("unexpected error\n");
		break;
	}
	}
}

void IocpObj::DoAccept(IocpAccept* _accepter)
{
	ASSERT_CRASH(netCore != nullptr);
	SessionSptr _clientSession = netCore->CreateSessionFactory();
	_clientSession->SetNetCore(netCore);
	_accepter->Init();
	_accepter->session = _clientSession;


	if (SocketUtil::AcceptEx(_accepter->owner, _accepter, _clientSession) == false) {
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			printf("soket util's acceptEx failed - %d\n", err);
			DoAccept(_accepter);
			return;
		}
	}
}

void IocpObj::DoConnect()
{
	if(isConnected.load()) {
		return ;
	}

	iocpConnect.Init();
	iocpConnect.owner = shared_from_this();
	if (SocketUtil::ConnectEx(sock, iocpCore->GetNetTarget()->SockAddr(), &iocpConnect) == false) {
		int32_t err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			iocpConnect.owner = nullptr;
			//todo : logging
			printf("connect Ex failed. check this..\n");
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
			//todo : logging
			iocpDisconnect.owner = nullptr;
			printf("disconnect Ex failed. err : %d\n", err);
			return ;
		}
	}
	return;
}

void IocpObj::DoSend()
{
	if (isConnected.load() == false) {
		return;
	}
	iocpSend.Init();
	iocpSend.owner = shared_from_this();
		
	vector<WSABUF> wsaBufs;
	{
		LOCK_GUARDDING(sendLock);
		int writeSize = 0;
		while (sendBuffers.empty() == false) {
			const SendBufferSptr sptr = sendBuffers.front();
			WSABUF wsaBuf = {};
			wsaBuf.buf = reinterpret_cast<char*>(sptr->Buffer());
			wsaBuf.len = sptr->WriteSize();
			wsaBufs.push_back(wsaBuf);

			writeSize += sptr->WriteSize();
			// todo : send 부하 조절용

			iocpSend.sendBuffers.push_back(sptr);
			sendBuffers.pop();
		}
	}

	if (SocketUtil::WSASend(sock, &iocpSend, wsaBufs) == false) {
		int err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			// todo : logging
			iocpSend.owner = nullptr;
			iocpSend.sendBuffers.clear();
			isSending.store(false);
			HandleError(err);
			return;
		}
	}
	return ;
}

void IocpObj::DoRecv()
{
	if (isConnected.load() == false) {
		return ;
	}
	iocpRecv.Init();
	iocpRecv.owner = shared_from_this();
	if(SocketUtil::WSARecv(sock, &iocpRecv) == false) {
		int err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			printf("SocketUtil::WSARecv failed. err : %d\n", err);
			HandleError(err);
			return;
		}
	}
}

void IocpObj::TryAccept()
{
	IocpAccept* accepter = xnew<IocpAccept>();
	acceptEvents.push_back(accepter);
	accepter->owner = shared_from_this();
	if (iocpCore->RegistToIocp(sock) == false) {
		int err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			printf("RegistListener failed. err : %d\n", err);
			DoAccept(accepter);
			return;
		}
	}
	DoAccept(accepter);
}

void IocpObj::OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session)
{
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
		if (err != WSA_IO_PENDING) {
			printf("Session Accepte Dispatch failed. err : %d\n", err);
			// todo : ASSERT
			DoAccept(_iocpAccept);
		}
		return;
	}
	AfterAccepted(_session);

	DoAccept(_iocpAccept);
	_session->OnConnected();
}

void IocpObj::TryConnect()
{
	printf("try connect called\n");
	DoConnect();
}

void IocpObj::OnConnected()
{
	if(isConnected.exchange(true) == true) {
		printf("duplicated connect????\n");
	}
	iocpConnect.owner = nullptr;

	TryRecv();
	AfterConnected();
}

void IocpObj::TryDisconnect(const char* _msg)
{
	// todo : logging
	if (isConnected.exchange(false) == false) {
		return;
	}
	printf("%s\n", _msg);
	DoDisconnect();
}

void IocpObj::OnDisconnect()
{
	iocpDisconnect.Init();
	iocpDisconnect.owner = nullptr;

	AfterDisconnected();
}

void IocpObj::TrySend(SendBufferSptr _sendBuffer)
{
	if (isConnected.load() == false) {
		return;
	}
	bool doSend = false;
	{
		LOCK_GUARDDING(sendLock);
		sendBuffers.push(_sendBuffer);
		if (isSending.exchange(true) == false) {
			doSend = true;
		}
	}
	if (doSend) {
		DoSend();
	}
}

void IocpObj::OnSended(UInt32 _bytes)
{
	iocpSend.owner = nullptr;
	iocpSend.sendBuffers.clear();
	if(_bytes == 0) {
		//todo : Discon
		TryDisconnect("on sended");
		return ;
	}
	
	{
		LOCK_GUARDDING(sendLock);
		if (sendBuffers.empty()) {
			isSending.store(false);
			AfterSended(_bytes);
		}
		else {
			DoSend();
		}
	}
	return ;
}

void IocpObj::TryRecv()
{
	if (isConnected.load() == false) {
		return;
	}
	DoRecv();
}

void IocpObj::OnRecved(UInt32 _bytes)
{
	iocpRecv.owner = nullptr;
	if(_bytes == 0) {
		TryDisconnect("on recved try disconnect");
		return ;
	}

	if (iocpRecv.recvBuffer.OnWrite(_bytes) == false) {
		TryDisconnect("recv buffer on write failed\n");
		return;
	}

	uint32_t dataSize = iocpRecv.recvBuffer.DataSize();
	int32_t processedBytes = AfterRecved(iocpRecv.recvBuffer.ReadPos(), dataSize);
	if (processedBytes < 0 || dataSize < processedBytes || (iocpRecv.recvBuffer.OnRead(processedBytes) == false)) {
		TryDisconnect("OnPaketRecved failed\n");
		return;
	}
	iocpRecv.recvBuffer.Clean();
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
		printf("On Accept!!\n");
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
		iocpDisconn->owner = nullptr;
		OnDisconnect();
		break;
	}
	default: {
		//todo : ASSERT
		CRASH("IocpObj DispatchEvent default case..?\n");
		return;
	}
	}
}
