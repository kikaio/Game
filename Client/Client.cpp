#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

void DoSimpleClient() {
	WSAData wsaData = {};
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 1;

	SOCKADDR_IN addr = {};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	inet_pton(AF_INET, ip.c_str(), &addr.sin_addr);


	SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
	if (::connect(sock, (const SOCKADDR*)&addr, sizeof(SOCKADDR)) == SOCKET_ERROR) {
		int err = WSAGetLastError();

		return ;
	}

	printf("connect fin\n");

	while (true) {
		this_thread::sleep_for(3s);
	}
	WSACleanup();
}

atomic<bool> connected = false;
vector<SessionSptr> sessions;


void DoIocpClient() {

	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 5;

	NetworkCore netCore;
	if (netCore.Ready() == false) {
		//todo : ASSERT
		return ;
	}
	printf("wsa standby.\n");

	if (netCore.ReadyToConnect() == false) {
		printf("ReadyToConnect failed\n");
		return ;
	}

	this_thread::sleep_for(3s);
	NetworkCore::CreateSessionFactory = [] {
		return MakeShared<DummySession>();
	};
	NetAddrSptr net = MakeShared<NetAddr>();

	{
		sessions = netCore.StartConnect(ip, port, clientCnt);
		connected.store(true);
	}
	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore.Dispatch(waitMilliSec);
	}
}


char sendMsg[SMALL_BUF_SIZE] = "hello, I'm client. who are you?\n";
int main()
{
	atomic<bool> clientDoRunning = true;

	ThreadManager::Get().PushThread(
		DoIocpClient, "DoIocpDispatch", "iocp port dispatch while shutdown"
	);
	
	/*ThreadManager::Get().PushThread(
		[&clientDoRunning](){
			while(clientDoRunning.load()) {
				ThreadManager::Get().RenderThreadsInfo();
				this_thread::sleep_for(5s);
			}
		}, "RenderThreadInfo", "Render All thread's info to console"
	);*/


	ThreadManager::Get().StartAll();

	while(clientDoRunning.load()) {
		this_thread::sleep_for(10s);
	}

	ThreadManager::Get().JoinAll();

	return 0;
}