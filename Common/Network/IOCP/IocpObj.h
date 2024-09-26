#pragma once
#include "IocpEvent.h"

class IocpObj : public enable_shared_from_this<IocpObj>
{
public:
	IocpObj();
	~IocpObj();
private:
	bool isConnected = false;
	bool isDisconneccted = false;
	NetAddrSptr netAddrSptr = nullptr;
	SOCKET sock = NULL;
	IocpCoreSptr iocpCore = nullptr;
public:
	vector<IocpAccept*> acceptEvents;
	IocpRecv iocpRecv;
	IocpConnect iocpConnect;

public:
	void SetSockOpts();
	bool Bind();
	bool Listen(UInt32 _backlog);
	SOCKADDR* SockAddr();
	NetAddrSptr Net();
	SOCKET Sock();

private:
	void  DoAccept(IocpAccept* _accepter);
	virtual void DoConnect();

public:
	virtual void TryAccept(UInt32 _acceptCnt);
	virtual void OnAccepted(SessionSptr _session);

	virtual void TryConnect();
	virtual void OnConnected();

public:
	void SetIocpCore(IocpCoreSptr _iocpCore);
	void DispatchEvent(IocpEvent* _event, UInt32 _bytes);
};
