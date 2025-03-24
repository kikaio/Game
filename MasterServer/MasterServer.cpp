#include "pch.h"
#include "ServerSession.h"
#include "MasterConfig.h"
#include "DBWrapper.h"
#include "GamePacketHandler.h"


int main()
{
	printf("Master Server start\n");

	JsonReader jr;
	string configPath = "./Configs/ServerConfig.json";
	jr.ReadFile(configPath.c_str());
	rapidjson::Value masterConfigVal(kObjectType);
	ASSERT_CRASH(jr.GetObject("master_config", OUT masterConfigVal));

	MasterConfig masterConfig;
	masterConfig.ReadFromJson(masterConfigVal);
	masterConfig.Render();

	rapidjson::Value dbValue(kArrayType);
	jr.GetArray("db_configs", OUT dbValue);
	ASSERT_CRASH(dbValue.IsArray());

	for(auto iter = dbValue.Begin(); iter != dbValue.End(); iter++) {
		rapidjson::Value& _confVal = *iter;
		DBConfig conf;
		conf.Init(_confVal);
		ASSERT_CRASH(DBConnectionPool::Get().Connect(conf));
	}


	ThreadManager::Get().PushAndStart([]() {
		while (true) {
			ThreadManager::Get().DoGlobalQueueWork();
			ThreadManager::Get().DoDitributeJob();
		}
	});

	ThreadManager::Get().PushAndStart([&masterConfig](){
		GamePacketHandler::Init();
		NetworkCoreSptr gameCoreSptr = MakeShared<NetworkCore>();

		ASSERT_CRASH(gameCoreSptr->Ready());
		gameCoreSptr->CreateSessionFactory = []() {
			auto gameServer = MakeShared<ServerSession>();
			gameServer->SetOnSessionConnectedFunc([]() {
			});
			return gameServer;
			};

		ListenerSptr gameListener = MakeShared<Listener>(masterConfig.ListenPort());
		ASSERT_CRASH(gameCoreSptr->ReadyToAccept(gameListener
			, masterConfig.BackLog(), masterConfig.AcceptCnt())
		);
		printf("accept ready\n");

		printf("master and game wsa ready\n");

		uint32_t waitMilliSec = 100;
		uint64_t workerTick = 10000;
		while(true) {
			LEndTickCount = ::GetTickCount64() + workerTick;
			gameCoreSptr->Dispatch(waitMilliSec);
		}
	});
	
	ThreadManager::Get().JoinAll();
	ThreadManager::Get().Clear();

	return 0;
}
