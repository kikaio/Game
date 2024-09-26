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
    int backlog = 100;
    int port = 7777;
    NetworkCore netCore;
    if (netCore.Ready() == false) {
        //todo : ASSERT
        return 0;
    }
    printf("wsa standby.\n");

    ListenerSptr listener = MakeShared<Listener>(port);
    netCore.ReadyToAccept(listener, backlog, acceptCnt);

    printf("accept ready\n");

    UInt32 waitMilliSec = INFINITE;
    while(true) {
        netCore.Dispatch(waitMilliSec);
    }
    return 0;
}
