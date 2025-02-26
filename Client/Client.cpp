#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

atomic<bool> clientDoRunning = true;

void DoClientToGameServer() {

	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 1;

	NetworkCoreSptr netCore = MakeShared<NetworkCore>();
	
	ASSERT_CRASH(netCore->Ready());
	
	printf("wsa standby.\n");

	if (netCore->ReadyToConnect() == false) {
		printf("ReadyToConnect failed\n");
		return ;
	}

	this_thread::sleep_for(3s);
	//dummyUser 제어를 위해 Manager에서 관리한다.
	netCore->CreateSessionFactory = [] {
		auto dumSession = MakeShared<DummySession>();
		auto dummyUser = MakeShared<DummyUser>();
		dummyUser->SetDummySession(dumSession);
		DummyUserManager::Get().PushDummyUser(dummyUser);
		//session disconnect 후처리 연결 필수.
		dumSession->SetOnSessionDisconnectedFunc([dummyUser=dummyUser](){
			dummyUser->OnSessionDisconnected();
		});
		return dumSession;
	};
	
	netCore->StartConnect(ip, port, clientCnt);

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore->Dispatch(waitMilliSec);
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

	ThreadManager::Get().PushThread(
		DoClientToGameServer, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);

	int workerThreadCnt = 1;
	for(int idx = 0; idx < workerThreadCnt; idx++) {
		ThreadManager::Get().PushAndStart(
			DoWorkerThread, "Do Job with GlobalQueue", "execute every dummy's job in this threads"
		);
	}
	
	ThreadManager::Get().StartAll();
	
	
	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();

	return 0;
}
