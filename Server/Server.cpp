﻿#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

#include <sw/redis++/redis++.h>

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}


void InitConfigs();
void DoIocpGameService(NetworkCoreSptr netCore);
void DoIocpMasterService(NetworkCoreSptr netCore);
int32_t DoServerLogic();

static GameConfig gameConf;
static MasterConfig masterConf;
static std::map<string, DBConfig> dbConfigs;
static std::map<string, RedisConfig> redisConfigs;

int main()
{
    timeval timeout;
    timeout.tv_sec = 10;
    timeout.tv_usec = 0;

    auto redis = sw::redis::Redis("tcp://127.0.0.1:6379");

    //config 정보 초기화
    InitConfigs();

    int32_t ret = DoServerLogic();
    ThreadManager::Get().JoinAll();
    printf("Server Main Thread Finished\n");
    return ret;
}

void InitConfigs() {

    JsonReader jr;
    jr.ReadFile("./configs/ServerConfig.json");

    rapidjson::Value masterValue(kObjectType);
    jr.GetObjectW("master", OUT masterValue);
    masterConf.Init(masterValue);

    rapidjson::Value gameValue(kObjectType);
    jr.GetObjectW("game", OUT gameValue);
    gameConf.ReadFromJson(gameValue);

    rapidjson::Value dbValue(kArrayType);
    jr.GetObjectW("db_configs", OUT dbValue);
    ASSERT_CRASH(dbValue.IsArray());

    for (auto iter = dbValue.Begin(); iter != dbValue.End(); iter++) {
        rapidjson::Value& dbConfigVal = *iter;
        DBConfig dbConf;
        dbConf.Init(dbConfigVal);
        dbConfigs.emplace(dbConf.dbNameStr, dbConf);
        ASSERT_CRASH(DBConnectionPool::Get().Connect(dbConf.poolCnt
            , DBConfig::odbcName, dbConf.hostStr
            , dbConf.userStr, dbConf.pwStr, dbConf.dbNameType, dbConf.rwType
        ));
    }

    rapidjson::Value redisValues(kArrayType);
    jr.GetObjectW("redis", redisValues);
    ASSERT_CRASH(redisValues.IsArray());
    for(auto _iter = redisValues.Begin(); _iter != redisValues.End(); _iter++) {
        rapidjson::Value& val = *_iter;
        RedisConfig redisConf ;
        redisConf.Init(val);
        redisConfigs.emplace(redisConf.nameStr, redisConf);
        //todo : redis db connect
        RedisConnPool::Get().Add(redisConf.redisName, redisConf.hostStr, redisConf.port);
    }
}

int32_t DoServerLogic() {
    
    ThreadManager::Get().PushAndStart([]() {
        NetworkCoreSptr gameServiceNetCore = MakeShared<NetworkCore>();
        DoIocpGameService(gameServiceNetCore);
    });


    ThreadManager::Get().PushAndStart([]() {
        NetworkCoreSptr masterCore = MakeShared<NetworkCore>();
        DoIocpMasterService(masterCore);
    });

    //스케줄 및 job 담당
    ThreadManager::Get().PushAndStart([]() {
        while (true) {
            ThreadManager::Get().DoGlobalQueueWork();
            ThreadManager::Get().DoDitributeJob();
        }
    });
    return 0;
}

void DoIocpGameService(NetworkCoreSptr netCore) {
    ServerPacketHandler::Init();
    ASSERT_CRASH(netCore->Ready());
    printf("wsa standby.\n");

    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;

    ListenerSptr listener = MakeShared<Listener>(port);
    netCore->ReadyToAccept(listener, backlog, accepterCnt);
    printf("accept ready\n");

    netCore->CreateSessionFactory = [] {
        //sid는 accept, connect 완료 시 자동 할당한다. => After 함수들 참고.
        auto user = MakeShared<UserSession>();
        //GameUser와의 연결은 GameService에서 특정 RPC를 통해 계정 로그인 후에 부여한다.
        return user;
    };

    UInt32 waitMilliSec = INFINITE;
    uint64_t workerTick = 10000;
    while (true) {
        LEndTickCount = ::GetTickCount64() + workerTick;
        netCore->Dispatch(waitMilliSec);
    }
}

void DoIocpMasterService(NetworkCoreSptr master) {

    //master server instance 기다려주는 시간
    this_thread::sleep_for(3s);

    MasterPacketHandler::Init();

    int32_t serverNo = 1;
    string serverName = "game_instance";
    ASSERT_CRASH(master->Ready());
    ASSERT_CRASH(master->ReadyToConnect());

    master->CreateSessionFactory = [serverNo, serverName](){
        MasterSessionSptr session = MakeShared<MasterSession>();
        session->SetOnSessionConnectedFunc([session, serverNo, serverName]() {
            //todo : send req connect packet
            MasterAndGameServer::ReqMasterServerConnect packet;
            packet.set_game_server_name(serverName.c_str());
            packet.set_game_server_no(serverNo);
            session->SendPacket(packet);
        });
        return session;
    };


    auto sessions = master->StartConnect(masterConf.hostStr, masterConf.port, 1);
    UInt32 waitMilliSec = INFINITE;
    uint64_t workerTick = 10000;
    while(true) {
        master->Dispatch(waitMilliSec);
    }
}