#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

int main()
{
    int acceptCnt = 1;
    NetworkCore netCore;
    if (netCore.Ready() == false) {
        //todo : ASSERT
        return 0;
    }
    printf("wsa standby.\n");

    NetAddrSptr addr = MakeShared<NetAddr>();
    addr->SetAddrAny(7777);
    ListenerSptr listener = MakeShared<Listener>(addr);
    netCore.ReadyToAccept(listener, acceptCnt);

    printf("accept ready\n");

    UInt32 waitMilliSec = 100;
    while(true) {
        netCore.Dispatch(INFINITE);
    }
    return 0;
}
