#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

void DoIocpClient() {

	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 1;

	NetworkCore netCore;
	
	ASSERT_CRASH(netCore.Ready());
	
	printf("wsa standby.\n");

	if (netCore.ReadyToConnect() == false) {
		printf("ReadyToConnect failed\n");
		return ;
	}

	this_thread::sleep_for(3s);
	netCore.CreateSessionFactory = [] {
		auto dumSession = MakeShared<DummySession>();
		return dumSession;
	};
	NetAddrSptr net = MakeShared<NetAddr>();

	netCore.StartConnect(ip, port, clientCnt);

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore.Dispatch(waitMilliSec);
	}
}


int main()
{
	atomic<bool> clientDoRunning = true;

	ThreadManager::Get().PushThread(
		DoIocpClient, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);
	

	ThreadManager::Get().StartAll();
	
	
	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();

	return 0;
}
