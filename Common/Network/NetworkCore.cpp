#include "pch.h"
#include "NetworkCore.h"

bool NetworkCore::Ready()
{
	wsaReady = MakeShared<WsaReady>();
	if (wsaReady->Ready() == false) {
		int err = WSAGetLastError();
		printf("wsa ready failed\n");
		return false;
	}

	iocpCore = MakeShared<IocpCore>();
	// ready에서 handle 도 생성함.
	if (iocpCore->Ready() == false) {
		printf("iocp core ready failed\n");
		return false;
	}

	if (SocketUtil::SetExFunctions() == false) {
		printf("SetExFunctions failed\n");
		// todo : ASSERT, logging
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
			return false;
		}
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
	IocpObjSptr obj = _event->owner;
	obj->DispatchEvent(_event, _bytes);
}

bool NetworkCore::ReadyToAccept(ListenerSptr _listener, UInt32 _backlog, UInt32 _acceptCnt)
{

	//listener의 addr은 외부에서 우선 지정.
	_listener->SetSockOpts();
	_listener->SetIocpCore(iocpCore);

	if(_listener->Bind() == false) {
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			// todo  : ASSERT?
			printf("bind failed\n");
			ErrorHandle(err);
		}
		return false;
	}

	if(_listener->Listen(_backlog) == false) {
		// todo : ASSERT
		printf("listen failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err);
		}
		return false;
	}

	_listener->TryAccept(_acceptCnt);

	return true;
}


bool NetworkCore::ReadyToConnect()
{
	return true;
}

vector<SessionSptr> NetworkCore::StartConnect(string _ip, UInt32 _port, UInt32 _connCnt)
{
	vector<SessionSptr> sessions;
	for (UInt32 idx = 0; idx < _connCnt; idx++) {
		SessionSptr session = MakeShared<Session>();
		session->Net()->SetAddr(_ip, _port);
		if(session->Bind() == false) {
			printf("this session bind failed..");
			continue;
		}
		iocpCore->RegistToIocp(session->Sock(), &session->iocpConnect);
		sessions.push_back(session);
	}

	for (auto& _session : sessions) {
		_session->TryConnect();
	}

	return sessions;
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
	ULONG_PTR completionKey = 0;
	LPOVERLAPPED overlappedPtr = nullptr;

	BOOL ret = GetQueuedCompletionStatus(GetIocpHandle()
		, OUT &bytes, OUT &completionKey
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
