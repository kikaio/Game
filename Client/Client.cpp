#include "pch.h"

using namespace std;

atomic<bool> clientDoRunning = true;

static ClientConfig clientConfig;
static ChatConfig chatConfig;
static GameConfig gameConfig;
static MasterConfig masterConfig;

void Init();
void DoClientToGameServer(NetworkCoreSptr _netCore);
void DoClientToChatServer(NetworkCoreSptr _netCore);
void DoWorkerThread();

int main()
{
	Init();

	NetworkCoreSptr gameServerNetCore = MakeShared<NetworkCore>();
	NetworkCoreSptr chatServerNetCore = MakeShared<NetworkCore>();
	//todo : chat server 용 net core 도 준비.
	int32_t dummyUserCnt = clientConfig.DummyCnt();

	//dummy user 생성
	for (int i = 0; i < dummyUserCnt; ++i) {
		auto dummyUser = MakeShared<DummyUser>();
		dummyUser->gameServerNetCore = gameServerNetCore;
		dummyUser->chatServerNetCore = chatServerNetCore;
		dummyUser->SetChatServerInfo(chatConfig.Host(), chatConfig.Port());
		DummyUserManager::Get().PushDummyUser(dummyUser);
	}


	//기본적인 Net 연결 관련 설정 준비 - game server
	/*ThreadManager::Get().PushAndStart(
		[gameServerNetCore](){ 
			DoClientToGameServer(gameServerNetCore); 
		}
		, "DoClientToGameServer", "iocp port dispatch while shutdown"
	);*/

	ThreadManager::Get().PushAndStart(
		[chatServerNetCore]() {
			DoClientToChatServer(chatServerNetCore);
		}
		, "DoClientToChatServer", "iocp port dispatch while shutdown"
	);


	//worker thread 및 job timer 준비
	int workerThreadCnt = 1;
	for(int idx = 0; idx < workerThreadCnt; idx++) {
		ThreadManager::Get().PushAndStart(
			DoWorkerThread, "Do Job with GlobalQueue", "execute every dummy's job in this threads"
		);
	}

	//실제 dummy user의 작동
	this_thread::sleep_for(1s);
	DummyUserManager::Get().ReadyTestScenario();
	DummyUserManager::Get().DoTestScenario();
	
	// main thread 대기 및 종료 탐지.
	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();
	ThreadManager::Get().Clear();

	return 0;
}

void Init() {
	
	//logger 초기화
	LogHelper::Init("logs");

	JsonReader jr;
	jr.ReadFile("./Configs/ClientConfig.json");
	rapidjson::Value clientVal(kObjectType);
	jr.GetObject("client", OUT clientVal);
	clientConfig.Init(clientVal);
	clientConfig.Render();

	rapidjson::Value chatVal(kObjectType);
	jr.GetObject("chat", OUT chatVal);
	chatConfig.Init(chatVal);
	chatConfig.Render();

	rapidjson::Value gameVal(kObjectType);
	jr.GetObject("game", OUT gameVal);
	gameConfig.Init(gameVal);
	gameConfig.Render();

	rapidjson::Value masterVal(kObjectType);
	jr.GetObject("master", OUT masterVal);
	masterConfig.Init(masterVal);
	masterConfig.Render();

	return ;
}


void DoClientToGameServer(NetworkCoreSptr _netCore) {

	GameServerDiscriminator::Init();
	ASSERT_CRASH(_netCore->Ready(gameConfig.IocpThreadCnt()));
	gameConfig.Host();

	DUM_DEBUG_LOG("game wsa standby.");

	if (_netCore->ReadyToConnect(gameConfig.Host(), gameConfig.Port()) == false) {
		DUM_DEBUG_LOG("ReadyToConnect failed.");
		return;
	}

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		_netCore->Dispatch(waitMilliSec);
	}
}
void DoClientToChatServer(NetworkCoreSptr _netCore) {

	ChatServerDiscriminator::Init();
	ASSERT_CRASH(_netCore->Ready(chatConfig.IocpThreadCnt()));

	DUM_DEBUG_LOG("chat wsa standby. host : {}:{}", chatConfig.Host(), chatConfig.Port());
	if (_netCore->ReadyToConnect(chatConfig.Host(), chatConfig.Port()) == false) {
		DUM_DEBUG_LOG("ReadyToConnect failed.");
		return;
	}

	int32_t waitMilliSec = INFINITE;
	while (true) {
		_netCore->Dispatch(waitMilliSec);
	}
}

void DoWorkerThread() {

	uint64_t workerTick = 100;
	while (clientDoRunning) {
		LEndTickCount = ::GetTickCount64() + workerTick;
		ThreadManager::Get().DoGlobalQueueWork();
		ThreadManager::Get().DoDitributeJob();
	}
}
