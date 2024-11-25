#include "pch.h"
#include "ServerPch.h"
#include "Session.h"


void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpGameService(NetworkCoreSptr netCore);
void DoIocpMasterService(NetworkCoreSptr netCore);
int32_t DoServerLogic();
int32_t DoDatabaseTest();



int main()
{
    //int32_t ret = DoDatabaseTest();
    int32_t ret = DoServerLogic();
    ThreadManager::Get().JoinAll();
    printf("Server Main Thread Finished\n");
    return ret;
}

int32_t DoDatabaseTest()
{
    ASSERT_CRASH(DBWrapper::TryConnectToDatabases());
    return DBWrapper::DoDatabaseTest();
}

int32_t DoServerLogic() {
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

    MasterPacketHandler::Init();
    NetworkCoreSptr masterCore = MakeShared<NetworkCore>();
    if (masterCore->ReadyToConnect()) {
        return 0;
    }
    ThreadManager::Get().PushAndStart([&masterCore]() {
        this_thread::sleep_for(3s);
        DoIocpMasterService(masterCore);
    });
}

void DoIocpGameService(NetworkCoreSptr netCore) {
    //    UInt32 waitMilliSec = INFINITE;
    UInt32 waitMilliSec = 10;
    uint64_t workerTick = 10000;
    while (true) {
        LEndTickCount = ::GetTickCount64() + workerTick;
        netCore->Dispatch(waitMilliSec);
        ThreadManager::Get().DoGlobalQueueWork();
        ThreadManager::Get().DoDitributeJob();
    }
}

void DoIocpMasterService(NetworkCoreSptr master) {
    UInt32 waitMilliSec = 10;
    uint64_t workerTick = 10000;

    string ip = "127.0.0.1";
    int16_t port = 33301;
    auto sessions = master->StartConnect(ip, port, 1);

    for (auto _session : sessions) {
        //todo : send connect req
        MasterAndGameServer::ReqMasterServerConnect _packet;
        _packet.set_game_server_name("gameServer");
        _packet.set_game_server_no(1);
        auto _sendBuff = MasterPacketHandler::MakePacketReqMasterServerConnect(_packet);
        if (_session->TrySend(_sendBuff) == false) {
            //todo : error logging
            printf("session send failed");
            continue;
        }
    }

    int32_t keepAliveSec = 10;
    chrono::duration keepaliveMilliSec = chrono::seconds::duration(keepAliveSec);
    while (true) {
        this_thread::sleep_for(keepaliveMilliSec);
        printf("todo send keep alive...\n");
        //for (auto _session : sessions) {
        //    // todo : send noti for keep alive
        //}
    }

}