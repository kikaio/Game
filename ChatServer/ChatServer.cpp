// ChatServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"


static MasterConfig masterConfig;
static ChatConfig chatConfig;

void StartMasterThread();
void StartChatThread();

void InitConfig();

int main()
{
	InitConfig();

	ThreadManager::Get().PushThread(StartMasterThread
		, "for master server"
		, "thread about with master server"
	);

	ThreadManager::Get().PushThread(StartChatThread
		, "for chat server role"
		, "thread about with chat server"
	);

	ThreadManager::Get().StartAll();

	ThreadManager::Get().JoinAll();
	ThreadManager::Get().Clear();

	CS_DEBUG_LOG("chat server fin");
	return 0;
}
void InitConfig() {
	JsonReader jr;
	string configFilePath = "./configs/ServerConfig.json";
	jr.ReadFile(configFilePath.c_str());

	rapidjson::Value masterValue(rapidjson::kObjectType);
	jr.GetObjectW("master", masterValue);
	masterConfig.Init(masterValue);
		
	rapidjson::Value chatValue(rapidjson::kObjectType);
	jr.GetObjectW("chat", chatValue);
	chatConfig.Init(chatValue);


	rapidjson::Value mongoDBValue(rapidjson::kObjectType);
	jr.GetObjectW("mongo_db", mongoDBValue);

	rapidjson::Value redisDBValues(rapidjson::kArrayType);
	jr.GetObjectW("redis", redisDBValues);
	for(auto _iter = redisDBValues.Begin(); _iter != redisDBValues.End(); _iter++) {
		const auto& _val = *_iter;
		//todo : init for redis
	}

	const string logFolderPath = "logs";
	LogHelper::Init(logFolderPath, "debug");
}

void StartMasterThread() {
	NetworkCoreSptr masterNet = MakeShared<NetworkCore>();
	this_thread::sleep_for(3s);
	const string& host = masterConfig.GetHost();
	int16_t port = masterConfig.GetPort();
	int32_t serverNo = 1;
	string serverName = "chat_instance";
	MasterPacketDiscriminator::Init();
	ASSERT_CRASH(masterNet->Ready(1));
	ASSERT_CRASH(masterNet->ReadyToConnect(host, port));

	masterNet->CreateSessionFactory = [serverNo, serverName](){
		MasterServerSessionSptr _session = MakeShared<MasterServerSession>();
		return _session;
	};

	return ;
}

void StartChatThread() {
	NetworkCoreSptr chatNet = MakeShared<NetworkCore>();
	return ;
}