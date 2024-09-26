#include "pch.h"
#include "Listener.h"
Listener::Listener(UInt32 _port)
	: IocpObj()
{
	NetAddr()->SetAddrAny(_port);
}
