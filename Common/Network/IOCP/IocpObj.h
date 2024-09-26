#pragma once
class IocpAccept;
class IocpEvent;

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
	vector<IocpAccept*> acceptEvents;
public:
	void SetSockOpts();
	bool Bind();
	bool Listen(UInt32 _backlog);
	NetAddrSptr NetAddr() {
		return netAddrSptr;
	}
	SOCKET Sock() {
		return sock;
	}
private:
	void  DoAccept(IocpAccept* _accepter);
public:
	virtual void TryAccept(UInt32 _acceptCnt);
	virtual void OnAccepted(SessionSptr _session);
public:
	void DispatchEvent(IocpEvent* _event, UInt32 _bytes);
};
