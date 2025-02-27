#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

atomic<bool> clientDoRunning = true;

void DoClientToGameServer(NetworkCoreSptr gameServerNetCore) {

	string ip = "127.0.0.1";
	int port = 7777;

	ASSERT_CRASH(gameServerNetCore->Ready());
	
	printf("wsa standby.\n");

	if (gameServerNetCore->ReadyToConnect(ip, port) == false) {
		printf("ReadyToConnect failed\n");
		return ;
	}

	this_thread::sleep_for(3s);
	//dummyUser 제어를 위해 Manager에서 관리한다.
	//gameServerNetCore->CreateSessionFactory = [] {
	//	auto dumSession = MakeShared<GameServerSession>();
	//	auto dummyUser = MakeShared<DummyUser>();
	//	dummyUser->SetGameServerSession(dumSession);
	//	DummyUserManager::Get().PushDummyUser(dummyUser);
	//	//session disconnect 후처리 연결 필수.
	//	dumSession->SetOnSessionDisconnectedFunc([dummyUser=dummyUser](){
	//		dummyUser->OnGameServerSessionDisconnected();
	//	});
	//	return dumSession;
	//};
	//
	//더미의 경우 act를 통해 connect 시도하는 것으로...
	//gameServerNetCore->StartConnect(0);

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

	ClientPacketHandler::Init();

	NetworkCoreSptr gameServerNetCore = MakeShared<NetworkCore>();
	//todo : chat server 용 net core 도 준비.
	int dummyUserCnt = 1;

	//dummy user 생성
	for (int i = 0; i < dummyUserCnt; ++i) {
		auto dummyUser = MakeShared<DummyUser>();
		DummyUserManager::Get().PushDummyUser(dummyUser);
	}


	//기본적인 Net 연결 관련 설정 준비 - game server
	ThreadManager::Get().PushThread(
		[gameServerNetCore](){ 
			DoClientToGameServer(gameServerNetCore); 
		}
		, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);

	//worker thread 및 job timer 준비
	int workerThreadCnt = 1;
	for(int idx = 0; idx < workerThreadCnt; idx++) {
		ThreadManager::Get().PushAndStart(
			DoWorkerThread, "Do Job with GlobalQueue", "execute every dummy's job in this threads"
		);
	}
	
	ThreadManager::Get().StartAll();

	//실제 dummy user의 작동
	DummyUserManager::Get().ReadyTestScenario();
	DummyUserManager::Get().DoTestScenario();
	
	// main thread 대기 및 종료 탐지.
	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();

	return 0;
}
