#include "pch.h"
#include "Session.h"

Session::Session()
{
	netAddrSptr = MakeShared<NetAddr>();
}

Session::~Session()
{
	printf("session released");
}

SOCKADDR* Session::SockAddr()
{
	return netAddrSptr->SockAddr();
}

void Session::Dispatch(IocpEvent* _event, UInt32 _bytes)
{
	
}

