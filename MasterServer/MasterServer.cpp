#include "pch.h"

static MasterConfig masterConfig;

void Init();
void DoGameServerNetworking();
void DoChatServerNetworking();
int main()
{
	Init();

	ThreadManager::Get().PushAndStart(
		DoGameServerNetworking
		, "game server networking", "thread for game server networking"
	);
	ThreadManager::Get().PushAndStart(
		DoChatServerNetworking
		, "chat server networking", "thread for chat server networking"
	);
	
	uint64_t workerTick = 10000;
	ThreadManager::Get().PushAndStart([workerTick]() {
		while (true) {
			LEndTickCount = ::GetTickCount64() + workerTick;
			ThreadManager::Get().DoGlobalQueueWork();
			ThreadManager::Get().DoDitributeJob();
		}
	});

	ThreadManager::Get().JoinAll();
	ThreadManager::Get().Clear();

	return 0;
}

void Init() {
	printf("Master Server start\n");

	JsonReader jr;
	string configPath = "./Configs/ServerConfig.json";
	jr.ReadFile(configPath.c_str());
	rapidjson::Value masterConfigVal(kObjectType);
	ASSERT_CRASH(jr.GetObject("master_config", OUT masterConfigVal));

	masterConfig.ReadFromJson(masterConfigVal);
	masterConfig.Render();

	rapidjson::Value dbValue(kArrayType);
	jr.GetArray("db_configs", OUT dbValue);
	ASSERT_CRASH(dbValue.IsArray());

	for (auto iter = dbValue.Begin(); iter != dbValue.End(); iter++) {
		rapidjson::Value& _confVal = *iter;
		DBConfig conf;
		conf.Init(_confVal);
		ASSERT_CRASH(DBConnectionPool::Get().Connect(conf));
	}
	return ;
}

void DoChatServerNetworking() {

	ChatServerDiscriminator::Init();
	
	return ;
}

void DoGameServerNetworking() {

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

	while (true) {
		gameCoreSptr->Dispatch(INFINITE);
	}
	return ;
}