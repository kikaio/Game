#pragma once

//iocp 용
class Listener
{
public:
	Listener(NetAddrSptr _ref);
private:
	NetAddrSptr netAddrSptr = nullptr;
	SOCKET sock = NULL;
	Int32 backLog = 100;
public:
	bool Bind();
	bool Listen();
	SOCKET Accept(SOCKADDR* _addr);
	NetAddrSptr NetAddr() {
		return netAddrSptr;
	}
};