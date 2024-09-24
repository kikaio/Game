#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

int main()
{
    NetworkCore netCore;
    NetAddrSptr addr = MakeShared<NetAddr>();
    addr->SetAddrAny(7777);
    ListenerSptr listener = MakeShared<Listener>(addr);
    int acceptCnt = 10;
    netCore.Ready();
    netCore.ReadyToAccept(listener, acceptCnt);

    while(true) {
        this_thread::sleep_for(1s);
    }
    return 0;
}
