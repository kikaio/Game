#pragma once
#include "IocpEvent.h"


//iocp 용
class Session : public enable_shared_from_this<Session>
{
public:
	Session();
	virtual ~Session();
private:
	bool isConnected = false;
	NetAddrSptr netAddrSptr = nullptr;
public:
	SOCKET sock = NULL;
	IocpRecv iocpRecv;
	IocpConnect iocpConnect;
public:
	SOCKADDR* SockAddr();
	NetAddrSptr Net();
	bool Bind();
	void Dispatch(class IocpEvent* _event, UInt32 _bytes);
public:
//	virtual void TrySend() = 0;
//	virtual void TryRecv() = 0;
	virtual void TryConnect();
//	virtual void TryDisconnect() = 0;
//public:
//	virtual void DoSend();
//	virtual void DoRecv();
	virtual void DoConnect();
//	virtual void DoDisconnect();
//public:
//	virtual void OnAccepted();
//	virtual void OnSended();
//	virtual void OnRecved();
	virtual void OnConnected();
//	virtual void OnDisconnected();

};