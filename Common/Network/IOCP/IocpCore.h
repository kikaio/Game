#pragma once

class IocpCore 
{
public:
	IocpCore();
	~IocpCore();
private:
	HANDLE iocpHandle= nullptr;
private:
	void ErrorHandle(UInt32 _err);
	HANDLE CreateIocpHandle(DWORD _threadCnt);
public:
	bool Ready();
	BOOL RegistToIocp(SessionSptr _sessionId);
	HANDLE IocpHandle() {
		return iocpHandle;
	}
};