#include "pch.h"

using namespace std;

atomic<bool> clientDoRunning = true;

void DoClientToGameServer(NetworkCoreSptr _netCore) {

	GameServerPacketHandler::Init();
	ASSERT_CRASH(_netCore->Ready());
	string ip = "127.0.0.1";
	int port = 7777;

	DUM_DEBUG_LOG("game wsa standby.");

	if (_netCore->ReadyToConnect(ip, port) == false) {
		DUM_DEBUG_LOG("ReadyToConnect failed.");
		return ;
	}

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		_netCore->Dispatch(waitMilliSec);
	}
}
void DoClientToChatServer(NetworkCoreSptr _netCore) {

	ChatServerDiscriminator::Init();
	ASSERT_CRASH(_netCore->Ready());
	string ip = "127.0.0.1";
	int port = 8888;

	DUM_DEBUG_LOG("chat wsa standby.");
	if (_netCore->ReadyToConnect(ip, port) == false) {
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
	while(clientDoRunning) {
		LEndTickCount = ::GetTickCount64() + workerTick;
		ThreadManager::Get().DoGlobalQueueWork();
		ThreadManager::Get().DoDitributeJob();
	}
}


int main()
{
	//logger 초기화
	LogHelper::Init("logs/dummyLog.log");

	NetworkCoreSptr gameServerNetCore = MakeShared<NetworkCore>();
	NetworkCoreSptr chatServerNetCore = MakeShared<NetworkCore>();
	//todo : chat server 용 net core 도 준비.
	int dummyUserCnt = 1;

	//dummy user 생성
	for (int i = 0; i < dummyUserCnt; ++i) {
		auto dummyUser = MakeShared<DummyUser>();
		dummyUser->gameServerNetCore = gameServerNetCore;
		dummyUser->chatServerNetCore = chatServerNetCore;
		DummyUserManager::Get().PushDummyUser(dummyUser);
	}


	//기본적인 Net 연결 관련 설정 준비 - game server
	ThreadManager::Get().PushAndStart(
		[gameServerNetCore](){ 
			DoClientToGameServer(gameServerNetCore); 
		}
		, "DoClientToGameServer", "iocp port dispatch while shutdown"
	);

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
