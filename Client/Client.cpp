#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}


void DoIocpClient() {

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

	function<void()> _func = []() {};

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
	NetAddrSptr net = MakeShared<NetAddr>();

	netCore->StartConnect(ip, port, clientCnt);

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore->Dispatch(waitMilliSec);
	}
}

void DoSendChat() {

	this_thread::sleep_for(5s);
	UserAndGameServer::ReqChat reqChat;
	while (true) {
		auto dummyUser = DummyUserManager::Get().PeekDummyUser(0);
		if (dummyUser != nullptr) {
			this_thread::sleep_for(5s);
			dummyUser->SendChatMsg("this is dummy chat");
		}
	}
	
}

int main()
{
	atomic<bool> clientDoRunning = true;

	ClientPacketHandler::Init();

	ThreadManager::Get().PushThread(
		DoIocpClient, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);

	ThreadManager::Get().PushThread(
		DoSendChat, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);


	ThreadManager::Get().StartAll();
	
	
	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();

	return 0;
}
