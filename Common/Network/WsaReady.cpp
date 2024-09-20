#include "pch.h"
#include "WsaReady.h"

WsaReady::~WsaReady()
{
	WSACleanup();
}

bool WsaReady::Ready()
{
	WSAData data;
	return NO_ERROR == WSAStartup(MAKEWORD(2, 2), &data);
}
