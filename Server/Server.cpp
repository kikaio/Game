#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpServer(NetworkCoreSptr netCore) {
//    UInt32 waitMilliSec = INFINITE;
    UInt32 waitMilliSec = 10;
    uint64_t workerTick = 10000;
    while(true) {
        LEndTickCount = ::GetTickCount64() + workerTick;
        netCore->Dispatch(waitMilliSec);
        ThreadManager::Get().DoGlobalQueueWork();
        ThreadManager::Get().DoDitributeJob();
    }
}

int main()
{
    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;
    ServerPacketHandler::Init();
    NetworkCoreSptr netCore = MakeShared<NetworkCore>();
    if (netCore->Ready() == false) {
        return 0;
    }
    printf("wsa standby.\n");

    netCore->CreateSessionFactory = [] {
        //sid는 accept, connect 완료 시 자동 할당한다. => After 함수들 참고.
        auto user = MakeShared<UserSession>();
        return user;
        };

    ListenerSptr listener = MakeShared<Listener>(port);
    netCore->ReadyToAccept(listener, backlog, accepterCnt);

    printf("accept ready\n");
    NetworkCoreSptr netCoreSptr = netCore->GetCoreSptr();
    ThreadManager::Get().PushAndStart([&netCoreSptr]() {
        DoIocpServer(netCoreSptr);
    });
    
    this_thread::sleep_for(10s);

    ThreadManager::Get().JoinAll();
    return 0;
}
