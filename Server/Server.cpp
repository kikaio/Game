#include "pch.h"
#include "ServerPch.h"
#include "Session.h"


void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpGameService(NetworkCoreSptr netCore);
int32_t DoServerLogic();
int32_t DoDatabaseTest();



int main()
{
    return DoDatabaseTest();
    //return DoServerLogic();
}

int32_t DoDatabaseTest()
{
    JsonReader js;
    js.ReadFile("./Configs/ServerConfig.json");
    rapidjson::Value _dbs(kArrayType);
    js.GetArray("db_configs", OUT _dbs);
    ASSERT_CRASH(_dbs.IsArray());
    for(auto iter = _dbs.Begin(); iter != _dbs.End(); iter++) {
        JsonReader _js;
        string name, host, user, pw, rwTypeStr;
        int32_t port, poolCnt;
        _js.CopyValue(*iter);
        _js.GetStr("name", OUT name);
        _js.GetStr("host", OUT host);
        _js.GetStr("user", OUT user);
        _js.GetStr("pw", OUT pw);
        _js.GetInt32("port", OUT port);
        _js.GetStr("rw_type", OUT rwTypeStr);
        _js.GetInt32("pool_cnt", OUT poolCnt);

        auto rwCastRet = magic_enum::enum_cast<RWType>(rwTypeStr.c_str());
        ASSERT_CRASH(rwCastRet.has_value());
        RWType rwType = rwCastRet.value();
        auto dbNameCastRet = magic_enum::enum_cast<DBNameType>(name.c_str());
        ASSERT_CRASH(dbNameCastRet.has_value());
        DBNameType dbNameType = dbNameCastRet.value();
        array<char, MAX_PATH> connStrArr = {0, };

        sprintf_s(connStrArr.data(), connStrArr.size(), "Driver={MySQL ODBC 9.1 ANSI Driver};Server=%s, %d Database=%s; Uid=%s; Pwd=%d"
            , host.c_str(), port, user.c_str(), pw.c_str()
        );
        string odbcName = "MysqlODBC";
        ASSERT_CRASH(DBConnectionPool::Get().Connect(1, odbcName, host, user, pw, (int32_t)dbNameType, (int32_t)rwType));
        continue;
    }

    auto sql = "DROP TABLE IF EXISTS [dbo].[Gold];  \
    CREATE TABLE [dbo].[Gold]                       \
    (                                               \
        [id] INT NOT NULL PRIMARY KEY IDENTITY,     \
        [gold] INT NOT NULL DEFAULT 0               \
    );                                              \
    ";DBConnection* conn = DBConnectionPool::Get().Pop();
    ASSERT_CRASH(conn->Execute(sql));

    for(int32_t idx = 0; idx < 3; idx++) {
        DBConnection* conn = DBConnectionPool::Get().Pop();
        conn->Unbind();

        int gold = 100;
        SQLLEN len = 0;

        conn->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(gold), &gold, &len);

        ASSERT_CRASH(conn->Execute("INSERT INTO [dbo].[Gold]([gold] VALUES (?))"));
        DBConnectionPool::Get().Push(conn);
    }


    {
        DBConnection* conn = DBConnectionPool::Get().Pop();
        conn->Unbind();

        int32_t targetGold = 100;
        SQLLEN len = 0;

        ASSERT_CRASH(conn->BindParam(1, SQL_C_LONG, SQL_INTEGER, sizeof(targetGold), &targetGold, &len));

        int32_t outId = 0;
        SQLLEN outIdLen = 0;
        int32_t outGold = 0;
        SQLLEN outGoldLen = 0;

        ASSERT_CRASH(conn->BindCol(1, SQL_C_LONG, sizeof(outId), &outId, &outIdLen));
        ASSERT_CRASH(conn->BindCol(2, SQL_C_LONG, sizeof(outGold), &outGold, &outGoldLen));

        ASSERT_CRASH(conn->Execute("SELECT id, gold FROM [dbo].[Gold] WHERE id = (?)"));
            
        while(conn->Fetch()) {
            printf("cur Id : %d, gold : %d\n", outId, outGold);
        }
        DBConnectionPool::Get().Push(conn);
    }

    return 0;
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

    this_thread::sleep_for(10s);

    ThreadManager::Get().JoinAll();
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

