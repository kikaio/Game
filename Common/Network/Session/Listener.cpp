#include "pch.h"
#include "Listener.h"
Listener::Listener(uint16_t _port)
	: IocpObj()
{
	Net()->SetAddrAny(_port);
}
