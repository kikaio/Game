#include "pch.h"
#include "NetworkCore.h"

void NetworkCore::Ready()
{
	wsaReady = MakeShared<WsaReady>();
	wsaReady->Ready();

	iocpCore = MakeShared<IocpCore>();
	// ready에서 handle 도 생성함.
	iocpCore->Ready();

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

void NetworkCore::ReadyToAccept(ListenerSptr _listener, UInt32 _acceptCnt)
{
	//listener의 addr은 외부에서 우선 지정.
	if(_listener->Bind() == false) {
		// todo  : ASSERT?
		printf("bind failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return ;
	}

	if(_listener->Listen() == false) {
		// todo : ASSERT
		printf("listen failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return ;
	}

	DWORD dwBytes = 0;
	
	if (SocketUtil::SetAcceptableListener(_listener->Sock()) == false) {
		printf("Accepter setting failed\n");
		// todo : ASSERT, logging
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return;
	}

	for(unsigned int idx = 0; idx < _acceptCnt; ++idx) {
		_listener->TryAccept(iocpCore);
	}
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
	if(ret == false) {
		UInt32 err = WSAGetLastError();
		if(err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
	}

	IocpEvent* iocpEvent = reinterpret_cast<IocpEvent*>(overlappedPtr);
	DispatchEvent(iocpEvent, bytes);
	return ;
}
