#pragma once

class IocpCore 
{
public:
	IocpCore();
	~IocpCore();
private:
	HANDLE iocpHandle= INVALID_HANDLE_VALUE;
	NetAddrSptr netTarget = nullptr;
private:
	void ErrorHandle(UInt32 _err);
	HANDLE CreateIocpHandle(DWORD _threadCnt);
public:
	bool Ready(DWORD _threadPoolCnt);
	BOOL RegistToIocp(SOCKET _sock);
	HANDLE IocpHandle() {
		return iocpHandle;
	}

	NetAddrSptr GetNetTarget() {
		return netTarget;
	}
};