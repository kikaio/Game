#include "pch.h"
#include "IocpCore.h"

IocpCore::IocpCore()
{
    netTarget = MakeShared<NetAddr>();
}

IocpCore::~IocpCore()
{
}

void IocpCore::ErrorHandle(UInt32 _err)
{
    switch(_err) {
        // todo : case 별로 logging 혹은 assert
    default: {
        break;
    }
    }
}

HANDLE IocpCore::CreateIocpHandle(DWORD _threadCnt)
{
    return CreateIoCompletionPort(INVALID_HANDLE_VALUE, nullptr, NULL, _threadCnt);
}

bool IocpCore::Ready(DWORD _threadCnt)
{
    iocpHandle = CreateIocpHandle(_threadCnt);
    if (iocpHandle == NULL) {
        DWORD err = GetLastError();
        //todo : logging
        printf("iocp handle create failed. err - %d\n", err);
        CRASH("write unlock multiple\n");
        return false;
    }
    return true;
}

BOOL IocpCore::RegistToIocp(SOCKET _sock)
{
    HANDLE newHandle = CreateIoCompletionPort(
        (HANDLE)_sock, iocpHandle
        , NULL, NULL
    );
    return newHandle != INVALID_HANDLE_VALUE;
}
