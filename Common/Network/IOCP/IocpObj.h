#pragma once
#include "IocpEvent.h"

class NetworkCore;

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
	atomic<bool> isDead = false;
public:
	vector<IocpAccept*> acceptEvents;
	IocpRecv iocpRecv;
	IocpConnect iocpConnect;
	IocpDisconnect iocpDisconnect;
	IocpSend iocpSend;

	VAL_LOCK(sendLock);
	queue<SendBufferSptr> sendBuffers;
protected:
	NetworkCoreSptr netCore = nullptr;
public:
	void SetSockOpts();
	bool Bind();
	bool Listen(UInt32 _backlog);
	SOCKADDR* SockAddr();
	NetAddrSptr Net();
	
	SOCKET Sock();
	
	bool IsConnected() {
		return isConnected.load();
	}
public:
	void SetNetCore(NetworkCoreSptr _core) {
		netCore = _core;
		return ;
	}
	NetworkCoreSptr GetNetCore() {
		return netCore;
	}
private:
	void HandleError(int32_t _err);
private:
	void DoAccept(IocpAccept* _accepter);
	void DoConnect();
	void DoDisconnect();
	void DoSend();
	void DoRecv();
public:
	virtual void TryAccept();
	virtual void OnAccepted(IocpAccept* _iocpAccept, SessionSptr _session);

	virtual void TryConnect();
	virtual void OnConnected();

	virtual void TryDisconnect(const char* _msg);
	virtual void OnDisconnect();

	virtual bool TrySend(SendBufferSptr _sendBuffer);
	virtual void OnSended(UInt32 _bytes);

	virtual void TryRecv();
	virtual void OnRecved(UInt32 _bytes);
protected:
	virtual void AfterAccepted(SessionSptr _session) {
		return ;
	}
	virtual int32_t AfterRecved(BYTE* _buf, UInt32 _dataSize) {
		return 0;
	}
	virtual void AfterSended(UInt32 _bytes) {
		printf("send bytes : %d\n", _bytes);
	}

	virtual void AfterConnected() {
		return;
	}
	virtual void AfterDisconnected() {
	}
public:
	void SetIocpCore(IocpCoreSptr _iocpCore);
	void DispatchEvent(IocpEvent* _event, UInt32 _bytes);
};
