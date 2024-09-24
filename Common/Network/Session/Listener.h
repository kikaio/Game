#pragma once

//iocp 용
class Listener : public enable_shared_from_this<Listener>
{
public:
	Listener(NetAddrSptr _ref);
private:
	NetAddrSptr netAddrSptr = nullptr;
	SOCKET sock = NULL;
	Int32 backLog = 100;
private:
	void DoAccept(IocpCoreSptr _iocpCore);
protected:
	virtual void OnAccepted(); // 상속 후 재정의 
public:
	bool Bind();
	bool Listen();
	
	NetAddrSptr NetAddr() {
		return netAddrSptr;
	}
	SOCKET Sock() {
		return sock;
	}
public:
	void TryAccept(IocpCoreSptr _iocpCore);
};