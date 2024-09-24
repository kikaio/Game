#include "pch.h"
#include "NetworkCore.h"

bool NetworkCore::Ready()
{
	wsaReady = MakeShared<WsaReady>();
	if (wsaReady->Ready() == false) {
		printf("wsa ready failed");
		return false;
	}

	iocpCore = MakeShared<IocpCore>();
	// ready에서 handle 도 생성함.
	if (iocpCore->Ready() == false) {
		printf("iocp core ready failed\n");
		return false;
	}
	return true;
}

void NetworkCore::ErrorHandle(UInt32 _err)
{
	switch(_err) {
	default: {
		break;
	}
	}
}

void NetworkCore::DispatchEvent(IocpEvent* _event, UInt32 _bytes)
{
	switch (_event->Type()) {
	case IocpEvent::IOCP_EVENT::ACCEPT: {
		printf("On Accept!!");
		IocpAccept* iocpAccept = reinterpret_cast<IocpAccept*>(_event);
		SessionSptr session = iocpAccept->session;
		SocketUtil::UpdateAcceptToSock(listener-)
		iocpAccept->Init();
		iocpAccept->AfterAccept();
		//Recv 등록.
		//session->TryRecv();
		break;
	}
	case IocpEvent::IOCP_EVENT::CONNECT: {
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

bool NetworkCore::ReadyToAccept(ListenerSptr _listener, UInt32 _acceptCnt)
{
	iocpCore->RegistListener(_listener->Sock());

	//listener의 addr은 외부에서 우선 지정.
	if(_listener->Bind() == false) {
		// todo  : ASSERT?
		printf("bind failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return false;
	}

	if(_listener->Listen() == false) {
		// todo : ASSERT
		printf("listen failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return false;
	}

	DWORD dwBytes = 0;
	
	if (SocketUtil::SetAcceptableListener(_listener->Sock()) == false) {
		printf("Accepter setting failed\n");
		// todo : ASSERT, logging
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return false;
	}

	for(unsigned int idx = 0; idx < _acceptCnt; ++idx) {
		_listener->TryAccept(iocpCore);
	}

	return true;
}

HANDLE NetworkCore::GetIocpHandle()
{
	if(iocpCore == nullptr) {
		return nullptr;
	}
	return iocpCore->IocpHandle();
}

void NetworkCore::Dispatch(UInt32 _milliSec)
{
	DWORD bytes = 0;
	ULONG completionKey = 0;
	LPOVERLAPPED overlappedPtr = nullptr;

	BOOL ret = GetQueuedCompletionStatus(GetIocpHandle()
		, OUT &bytes, OUT reinterpret_cast<PULONG_PTR>(&completionKey) 
		, &overlappedPtr, _milliSec
	);
	if(ret == FALSE) {
		return;
	}

	IocpEvent* iocpEvent = reinterpret_cast<IocpEvent*>(overlappedPtr);
	if (iocpEvent == nullptr) {
		printf("event must be not null...\n");
		// todo : ASSERT
		return;
	}
	DispatchEvent(iocpEvent, bytes);
	return ;
}
