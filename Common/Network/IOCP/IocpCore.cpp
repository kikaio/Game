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
    iocpHandle = CreateIocpHandle(64);
    if (iocpHandle == NULL) {
        DWORD err = GetLastError();
        //todo : logging and assert
        return false;
    }
    return true;
}

BOOL IocpCore::RegistToIocp(SessionSptr _session)
{
    _session->iocpAccept.session = _session;

    HANDLE newHandle = CreateIoCompletionPort(
        (HANDLE)_session->sock, iocpHandle
        , reinterpret_cast<ULONG_PTR>(&_session->iocpAccept), NULL
    );
    return newHandle != INVALID_HANDLE_VALUE;
}


