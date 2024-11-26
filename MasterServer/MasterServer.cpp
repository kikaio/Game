#include "pch.h"
#include "ServerSession.h"
#include "MasterConfig.h"
#include "DBWrapper.h"
#include "GamePacketHandler.h"


int main()
{
	ASSERT_CRASH(DBWrapper::ReadDBConfigFile());

	printf("Master Server start\n");

	JsonReader jr;
	string configPath = "./Configs/ServerConfig.json";
	jr.ReadFile(configPath.c_str());
	rapidjson::Value masterConfigVal(kObjectType);
	ASSERT_CRASH(jr.GetObject("master_config", OUT masterConfigVal));

	MasterConfig masterConfig;
	masterConfig.ReadFromJson(masterConfigVal);
	masterConfig.Render();


	ThreadManager::Get().PushAndStart([&masterConfig](){
		GamePacketHandler::Init();
		NetworkCoreSptr gameCoreSptr = MakeShared<NetworkCore>();

		ASSERT_CRASH(gameCoreSptr->Ready());
		gameCoreSptr->CreateSessionFactory = []() {
			auto gameServer = MakeShared<ServerSession>();
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
			ThreadManager::Get().DoGlobalQueueWork();
			ThreadManager::Get().DoDitributeJob();
		}
	});
	
	ThreadManager::Get().JoinAll();

	return 0;
}
