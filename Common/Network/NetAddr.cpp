#include "pch.h"
#include "NetAddr.h"

NetAddr::NetAddr()
{
}


void NetAddr::SetAddr(string _ip, UInt32 _port)
{
	ip = _ip;
	port = _port;

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &sockAddr.sin_addr.s_addr);
}

void NetAddr::SetAddrAny(UInt32 _port)
{
	ip = "0.0.0.0";
	port = _port;

	sockAddr.sin_family = AF_INET;
	sockAddr.sin_port = htons(port);
	sockAddr.sin_addr.s_addr = INADDR_ANY;
}
