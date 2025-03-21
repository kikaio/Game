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

int main()
{
    //config 정보 초기화
    InitConfigs();
    int32_t ret = DoServerLogic();
    ThreadManager::Get().JoinAll();
    GS_DEBUG_LOG("Server Main Thread Finished");

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
    jr.GetArray("db_configs", OUT dbValue);
    ASSERT_CRASH(dbValue.IsArray());

    for (auto iter = dbValue.Begin(); iter != dbValue.End(); iter++) {
        rapidjson::Value& dbConfigVal = *iter;
        DBConfig dbConf;
        dbConf.Init(dbConfigVal);
        ASSERT_CRASH(DBConnectionPool::Get().Connect(dbConf));
    }

    rapidjson::Value redisValues(kArrayType);
    jr.GetArray("redis", OUT redisValues);
    ASSERT_CRASH(redisValues.IsArray());
    for(auto _iter = redisValues.Begin(); _iter != redisValues.End(); _iter++) {
        rapidjson::Value& val = *_iter;
        RedisConfig redisConf ;
        redisConf.Init(val);
        //todo : redis db connect
        RedisConnPool::Get().Add(redisConf);
    }

    string logFilePath = "logs/GameServer.log";
    LogHelper::Init(logFilePath);
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
        uint64_t workerTick = 100;
        while (true) {
            LEndTickCount = ::GetTickCount64() + workerTick;
            ThreadManager::Get().DoGlobalQueueWork();
            ThreadManager::Get().DoDitributeJob();
        }
    });
    return 0;
}

void DoIocpGameService(NetworkCoreSptr netCore) {
    ServerPacketHandler::Init();
    UInt32 tag1 = 1;
    UInt32 tag2 = 2;

    netCore->SetTag(tag1, tag2);
    ASSERT_CRASH(netCore->Ready());
    GS_DEBUG_LOG("wsa standby.");

    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;

    ListenerSptr listener = MakeShared<Listener>(port);

    netCore->CreateSessionFactory = [] {
        //sid는 accept, connect 완료 시 자동 할당한다. => After 함수들 참고.
        UserSessionSptr user = MakeShared<UserSession>();
        //GameUser와의 연결은 GameService에서 특정 RPC를 통해 계정 로그인 후에 부여한다.
        user->SetOnSessionConnectedFunc([user]() {
            //session 을 redis에 저장.   
            shared_ptr<RedisConn> _conn = RedisConnPool::Get().GetSessionConn();
            GS_DEBUG_LOG("session[{}] connected!", user->GetSId());
            _conn->set(user->GetSId().c_str(), "session_id");

            }
        );
        return static_pointer_cast<Session>(user);
    };


    netCore->ReadyToAccept(listener, backlog, accepterCnt);
    GS_DEBUG_LOG("accept ready");

    UInt32 waitMilliSec = INFINITE;
    uint64_t workerTick = 10000;
    while (true) {
        netCore->Dispatch(waitMilliSec);
    }
}

void DoIocpMasterService(NetworkCoreSptr master) {

    //master server instance 기다려주는 시간
    this_thread::sleep_for(3s);

    MasterPacketHandler::Init();

    int32_t serverNo = 1;
    string serverName = "game_instance";
    ASSERT_CRASH(master->Ready(1));
    ASSERT_CRASH(master->ReadyToConnect(masterConf.hostStr, masterConf.port));

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

    auto sessions = master->StartConnect(1);
    UInt32 waitMilliSec = INFINITE;
    while(true) {
        master->Dispatch(waitMilliSec);
    }
}