#include "pch.h"

using namespace std;

atomic<bool> clientDoRunning = true;

void DoClientToGameServer(NetworkCoreSptr gameServerNetCore) {

	string ip = "127.0.0.1";
	int port = 7777;

	ASSERT_CRASH(gameServerNetCore->Ready());
	
	DUM_DEBUG_LOG("wsa standby.");

	if (gameServerNetCore->ReadyToConnect(ip, port) == false) {
		DUM_DEBUG_LOG("ReadyToConnect failed.");
		return ;
	}

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		gameServerNetCore->Dispatch(waitMilliSec);
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

	GameServerPacketHandler::Init();
	
	//logger 초기화
	LogHelper::Init("logs/dummyLog.log");

	NetworkCoreSptr gameServerNetCore = MakeShared<NetworkCore>();
	//todo : chat server 용 net core 도 준비.
	int dummyUserCnt = 1;

	//dummy user 생성
	for (int i = 0; i < dummyUserCnt; ++i) {
		auto dummyUser = MakeShared<DummyUser>();
		dummyUser->gameServerNetCore = gameServerNetCore;
		DummyUserManager::Get().PushDummyUser(dummyUser);
	}


	//기본적인 Net 연결 관련 설정 준비 - game server
	ThreadManager::Get().PushAndStart(
		[gameServerNetCore](){ 
			DoClientToGameServer(gameServerNetCore); 
		}
		, "DoClientToGameServer", "iocp port dispatch while shutdown"
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
