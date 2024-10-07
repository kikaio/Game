#include "pch.h"
#include "NetworkCore.h"


NetworkCore::NetworkCore()
{	
	//기본 session 생성 
	CreateSessionFactory = []() {
		return MakeShared<Session>();
	};
}

bool NetworkCore::Ready()
{
	wsaReady = MakeShared<WsaReady>();
	if (wsaReady->Ready() == false) {
		int err = WSAGetLastError();
		printf("wsa ready failed, err : %d\n", err);
		CRASH("wsa ready failed\n");
		return false;
	}

	iocpCore = MakeShared<IocpCore>();
	// ready에서 handle 도 생성함.
	if (iocpCore->Ready() == false) {
		printf("iocp core ready failed\n");
		CRASH("iocp core ready failed\n");
		return false;
	}

	if (SocketUtil::SetExFunctions() == false) {
		printf("SetExFunctions failed\n");
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			ErrorHandle(err); 
			CRASH("SetExFunctions failed\n");
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
	_listener->SetSockOpts();
	_listener->SetIocpCore(iocpCore);
	_listener->SetNetCore(this); 

	if(_listener->Bind() == false) {
		UInt32 err = WSAGetLastError();
		if (err != WSA_IO_PENDING) {
			// todo  : ASSERT?
			printf("bind failed\n");
			CRASH("bind failed\n");
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
			printf("listen failed. err : %d\n", err);
			CRASH("listen failed.\n");
		}
		return false;
	}

	for (UInt32 idx = 0; idx < _acceptCnt; idx++) {
		_listener->TryAccept();
	}

	return true;
}


bool NetworkCore::ReadyToConnect()
{
	return true;
}

vector<SessionSptr> NetworkCore::StartConnect(string _ip, UInt32 _port, UInt32 _connCnt)
{
	iocpCore->GetNetTarget()->SetAddr(_ip, _port);

	vector<SessionSptr> sessions;
	for (UInt32 idx = 0; idx < _connCnt; idx++) {
		SessionSptr session = CreateSessionFactory();
		session->Net()->SetAddrAny(0);
		if(session->Bind() == false) {
			printf("this session bind failed.. err : %d\n", WSAGetLastError());
			continue;
		}
		session->SetSockOpts();
		session->SetIocpCore(iocpCore);
		session->SetNetCore(this);
		iocpCore->RegistToIocp(session->Sock());
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
		int32_t error = WSAGetLastError();
		switch (error) {
		case WAIT_TIMEOUT: {
			return;
		}
		default: {
			//이 경우 처리를 해줘야 server에서 usersession에 대한 disconnected를 탐지가능.
			IocpEvent* iocpEvent = reinterpret_cast<IocpEvent*>(overlappedPtr);
			DispatchEvent(iocpEvent, bytes);
			return;
		}
		}
		return;
	}
	else {
		IocpEvent* iocpEvent = reinterpret_cast<IocpEvent*>(overlappedPtr);
		DispatchEvent(iocpEvent, bytes);
	}
	return ;
}
