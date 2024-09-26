#include "pch.h"
#include "Listener.h"
Listener::Listener(UInt32 _port)
	: IocpObj()
{
	Net()->SetAddrAny(_port);
}
