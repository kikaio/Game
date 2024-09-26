#include "pch.h"
#include "IocpEvent.h"

void IocpEvent::Init()
{
	this->hEvent = nullptr;
	this->Internal = 0;
	this->InternalHigh = 0;
	this->Offset = 0;
	this->OffsetHigh = 0;
	this->Pointer = nullptr;
}

void IocpAccept::AfterAccept()
{
	session = nullptr;
	owner = nullptr;
}
