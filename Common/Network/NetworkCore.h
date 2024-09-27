#pragma once

using SessionCreateFunc = std::function<SessionSptr()>;

class NetworkCore
{
private :
	IocpCoreSptr iocpCore = nullptr;
	WsaReadySptr wsaReady = nullptr;
public:
	static SessionCreateFunc  CreateSessionFactory;

private:
	void ErrorHandle(UInt32 _err);
	void DispatchEvent(class IocpEvent* _event, UInt32 _bytes);

public:
	bool Ready();
	bool ReadyToAccept(ListenerSptr _listener, UInt32 _backlog, UInt32 _acceptCnt);
	bool ReadyToConnect();
	vector<SessionSptr> StartConnect(string _ip, UInt32 _port, UInt32 _connCnt);
public:
	HANDLE GetIocpHandle();
	void Dispatch(UInt32 _milliSec);
};
