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

	NetworkCoreSptr masterServiceNetCore = MakeShared<NetworkCore>();
	ASSERT_CRASH(masterServiceNetCore->Ready());
	printf("master corenet read.\n");
	masterServiceNetCore->CreateSessionFactory = []() {
		auto session= MakeShared<ServerSession>();
		return session;
	};

	GamePacketHandler::Init();
	NetworkCoreSptr gameCoreSptr = MakeShared<NetworkCore>();
	ASSERT_CRASH(gameCoreSptr->Ready());
	printf("master and game wsa ready");
	gameCoreSptr->CreateSessionFactory= [](){
		auto gameServer = MakeShared<ServerSession>();
		return gameServer;
	};
	printf("accept ready");
	ThreadManager::Get().PushAndStart([&masterConfig, &gameCoreSptr](){
		uint32_t waitMilliSec = 100;
		uint64_t workerTick = 10000;
		while(true) {
			LEndTickCount = ::GetTickCount64() + workerTick;
			gameCoreSptr->Dispatch(waitMilliSec);
			ThreadManager::Get().DoGlobalQueueWork();
			ThreadManager::Get().DoDitributeJob();
		}
	});

	return 0;
}
