#include "pch.h"
#include "IocpCore.h"

IocpCore::IocpCore()
{
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

bool IocpCore::Ready()
{
    iocpHandle = CreateIocpHandle(0);
    if (iocpHandle == NULL) {
        DWORD err = GetLastError();
        //todo : logging and assert
        printf("iocp handle create failed. err - %d\n", err);
        return false;
    }
    return true;
}

BOOL IocpCore::RegistToIocp(SOCKET _sock, class IocpEvent* _event)
{
    _event->Init();
    HANDLE newHandle = CreateIoCompletionPort(
        (HANDLE)_sock, iocpHandle
        , NULL, NULL
    );
    return newHandle != INVALID_HANDLE_VALUE;
}

BOOL IocpCore::RegistListener(SOCKET _sock, class IocpAccept* _accepter)
{
    HANDLE newHandle = CreateIoCompletionPort(
        (HANDLE)_sock, iocpHandle
        , reinterpret_cast<ULONG_PTR>(_accepter), NULL
    );
    return newHandle != INVALID_HANDLE_VALUE;
}


