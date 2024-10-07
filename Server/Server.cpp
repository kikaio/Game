#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpServer() {
    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;
    NetworkCore netCore;
    if (netCore.Ready() == false) {
        return ;
    }
    printf("wsa standby.\n");

    netCore.CreateSessionFactory = [] {
        //sid는 accept, connect 완료 시 자동 할당한다. => After 함수들 참고.
        auto user = MakeShared<UserSession>();
        return user;
    };

    ListenerSptr listener = MakeShared<Listener>(port);
    netCore.ReadyToAccept(listener, backlog, accepterCnt);

    printf("accept ready\n");

    UInt32 waitMilliSec = INFINITE;
    while(true) {
        netCore.Dispatch(waitMilliSec);
    }
}

int main()
{
    ThreadManager::Get().PushAndStart(DoIocpServer, "", "");
    this_thread::sleep_for(10s);

    
    ThreadManager::Get().JoinAll();
    return 0;
}
