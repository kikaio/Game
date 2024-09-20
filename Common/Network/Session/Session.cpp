#include "pch.h"
#include "Session.h"

Session::Session()
{
	netAddrSptr = MakeShared<NetAddr>();
}

SOCKADDR* Session::SockAddr()
{
	return netAddrSptr->SockAddr();
}
