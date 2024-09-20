#pragma once

class IocpCore 
{
public:
	IocpCore();
	~IocpCore();
private:
	HANDLE iocpHandle= nullptr;
public:
	bool Ready();
	bool RegistSocket(SOCKET _sock);
};