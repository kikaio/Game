#include "pch.h"
#include "ServerPch.h"
#include "Session.h"


void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpGameService(NetworkCoreSptr netCore) {
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

void DoDatabaseConn() {
    DBManager::Get().Test();
}

int main()
{
    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;
    ServerPacketHandler::Init();
    NetworkCoreSptr gameServiceNetCore = MakeShared<NetworkCore>();
    if (gameServiceNetCore->Ready() == false) {
        return 0;
    }
    printf("wsa standby.\n");

    gameServiceNetCore->CreateSessionFactory = [] {
        //sid는 accept, connect 완료 시 자동 할당한다. => After 함수들 참고.
        auto user = MakeShared<UserSession>();
        //GameUser와의 연결은 GameService에서 특정 RPC를 통해 계정 로그인 후에 부여한다.
        return user;
        };

    ListenerSptr listener = MakeShared<Listener>(port);
    gameServiceNetCore->ReadyToAccept(listener, backlog, accepterCnt);

    printf("accept ready\n");
    ThreadManager::Get().PushAndStart([&gameServiceNetCore]() {
        DoIocpGameService(gameServiceNetCore);
    });
    
    this_thread::sleep_for(10s);

    ThreadManager::Get().JoinAll();
    return 0;
}
