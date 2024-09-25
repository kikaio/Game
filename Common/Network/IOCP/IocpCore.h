#pragma once

class IocpCore 
{
public:
	IocpCore();
	~IocpCore();
private:
	HANDLE iocpHandle= INVALID_HANDLE_VALUE;
private:
	void ErrorHandle(UInt32 _err);
	HANDLE CreateIocpHandle(DWORD _threadCnt);
public:
	bool Ready();
	BOOL RegistToIocp(SOCKET _sock, class IocpEvent* _event);
	BOOL RegistListener(SOCKET _sock, class IocpAccept* _accepter);
	HANDLE IocpHandle() {
		return iocpHandle;
	}
};