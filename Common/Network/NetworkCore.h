#pragma once
#include "SessionManager.h"

using SessionCreateFunc = std::function<SessionSptr()>;

class NetworkCore : public enable_shared_from_this<NetworkCore>
{
public:
	NetworkCore();
private :
	//현재 NetCore에 관련된 Session들만 관리하는 SessionMgr.
	SessionManager sessionMgr;
	IocpCoreSptr iocpCore = nullptr;
	WsaReadySptr wsaReady = nullptr;
public:
	SessionCreateFunc  CreateSessionFactory;

private:
	void ErrorHandle(UInt32 _err);
	void DispatchEvent(class IocpEvent* _event, UInt32 _bytes);

public:
	bool Ready(DWORD _iocpThreadPoolCnt = 0);
	bool ReadyToAccept(ListenerSptr _listener, UInt32 _backlog, UInt32 _acceptCnt);
	bool ReadyToConnect(string _ip, UInt32 _port);
	vector<SessionSptr> StartConnect(UInt32 _connCnt);
public:
	HANDLE GetIocpHandle();
	void Dispatch(UInt32 _milliSec);
	SessionManager& GetSessionMgr() {
		return sessionMgr;
	}

	void BroadCast(SendBufferSptr _sendBuffer);
	NetworkCoreSptr GetCoreSptr() {
		return shared_from_this();
	}
	IocpCoreSptr GetIocpCore() {
		return iocpCore;
	}
};
