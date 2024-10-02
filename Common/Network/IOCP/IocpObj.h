#pragma once
#include "IocpEvent.h"

class IocpObj : public enable_shared_from_this<IocpObj>
{
public:
	IocpObj();
	virtual ~IocpObj();
private:
	atomic<bool> isConnected = false;
	atomic<bool> isSending = false;
	NetAddrSptr netAddrSptr = nullptr;
	SOCKET sock = NULL;
	IocpCoreSptr iocpCore = nullptr;
public:
	vector<IocpAccept*> acceptEvents;
	IocpRecv iocpRecv;
	IocpConnect iocpConnect;
	IocpDisconnect iocpDisconnect;
	IocpSend iocpSend;
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
	void DoSend(BYTE* _buf, UInt32 _len);
	void DoRecv();
public:
	virtual void TryAccept();
	virtual void OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session);

	virtual void TryConnect();
	virtual void OnConnected();

	virtual void TryDisconnect();
	virtual void OnDisconnect();

	virtual void TrySend(BYTE* _orig, UInt32 _len);
	virtual void OnSended(UInt32 _bytes);

	virtual void TryRecv();
	virtual void OnRecved(UInt32 _bytes);
public:
	void SetIocpCore(IocpCoreSptr _iocpCore);
	void DispatchEvent(IocpEvent* _event, UInt32 _bytes);
};
