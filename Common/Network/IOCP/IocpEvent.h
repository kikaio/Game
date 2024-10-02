#pragma once

class IocpEvent : public OVERLAPPED
{
public:
	enum class IOCP_EVENT : UInt8 {
		NONE
		, ACCEPT
		, CONNECT
		, RECV
		, SEND
		, DISCONNECT
	};
public:
	IocpEvent(IOCP_EVENT _type) : type(_type) {
	}
private:
	IOCP_EVENT type = IOCP_EVENT::NONE;
public :
	IocpObjSptr owner = nullptr;
public:
	IOCP_EVENT Type() {
		return type;
	}
	void Init();

};

class IocpAccept : public IocpEvent 
{
public:
	IocpAccept() : IocpEvent(IOCP_EVENT::ACCEPT){};
public:
	SessionSptr session = nullptr;
public: 
	void AfterAccept();
};

class IocpConnect : public IocpEvent
{
public:
	IocpConnect() : IocpEvent(IOCP_EVENT::CONNECT) {};
};

class IocpRecv : public IocpEvent
{
public:
	IocpRecv() : IocpEvent(IOCP_EVENT::RECV) {};
public:
	PacketBuffer packetBuffer;
};

class IocpSend : public IocpEvent
{
public:
	IocpSend() : IocpEvent(IOCP_EVENT::SEND) {};
public:
	vector<WSABUF> wsaBufs;
};

class IocpDisconnect : public IocpEvent
{
public:
	IocpDisconnect() : IocpEvent(IOCP_EVENT::DISCONNECT) {};
};
