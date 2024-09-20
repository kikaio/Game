#pragma once

class NetAddr 
{
public:
	NetAddr() = default;
private:
	string ip = "";
	UInt32 port = 0;
	SOCKADDR_IN sockAddr = { };
public:
	void SetAddr(string _ip, UInt32 _port);
	void SetAddrAny(UInt32 _port);
public:
	UInt32 Port() {
		return port;
	}
	string Ip() {
		return ip;
	}

	SOCKADDR* SockAddr() {
		return reinterpret_cast<SOCKADDR*>(&sockAddr);
	}

};