#pragma once


class NetworkCore
{
private:
	//비동기 소켓 입출력 관련
	LPFN_ACCEPTEX lpfnAcceptEx = nullptr;
	GUID guidAcceptEx = WSAID_ACCEPTEX;
private :
	IocpCoreSptr iocpCore;
	WsaReadySptr wsaReady;
private:
	void ErrorHandle(UInt32 _err);
	void DispatchEvent(class IocpEvent* _event, UInt32 _bytes);
public:
	bool Ready();
	bool ReadyToAccept(ListenerSptr _listener, UInt32 _acceptCnt);
public:
	HANDLE GetIocpHandle();
	void Dispatch(UInt32 _milliSec);
};
