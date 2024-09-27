#pragma once
#include "IocpEvent.h"

class IocpObj : public enable_shared_from_this<IocpObj>
{
public:
	IocpObj();
	virtual ~IocpObj();
private:
	atomic<bool> isConnected = false;
	NetAddrSptr netAddrSptr = nullptr;
	SOCKET sock = NULL;
	IocpCoreSptr iocpCore = nullptr;
public:
	vector<IocpAccept*> acceptEvents;
	IocpRecv iocpRecv;
	IocpConnect iocpConnect;
	IocpDisconnect iocpDisconnect;

public:
	void SetSockOpts();
	bool Bind();
	bool Listen(UInt32 _backlog);
	SOCKADDR* SockAddr();
	NetAddrSptr Net();
	
	SOCKET Sock();

private:
	void DoAccept(IocpAccept* _accepter);
	void DoConnect();
	void DoDisconnect();
public:
	virtual void TryAccept();
	virtual void OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session);

	virtual void TryConnect();
	virtual void OnConnected();

	virtual void TryDisconnect();
	virtual void OnDisconnect();
public:
	void SetIocpCore(IocpCoreSptr _iocpCore);
	void DispatchEvent(IocpEvent* _event, UInt32 _bytes);
};
