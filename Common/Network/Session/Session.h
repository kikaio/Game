#pragma once

//iocp 용
class Session
{
public:
	Session();
private:
	NetAddrSptr netAddrSptr = nullptr;
public:
	SOCKET sock = NULL;
public:
	SOCKADDR* SockAddr();
};