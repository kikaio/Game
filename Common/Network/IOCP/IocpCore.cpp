#include "pch.h"
#include "IocpCore.h"

IocpCore::IocpCore()
{
}

IocpCore::~IocpCore()
{
}

bool IocpCore::Ready()
{
    iocpHandle = CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, NULL, NULL);
    if (iocpHandle == INVALID_HANDLE_VALUE) {
        //todo : logging and assert
        return false;
    }
    return true;
}

bool IocpCore::RegistSocket(SOCKET _sock)
{
    return false;
}

