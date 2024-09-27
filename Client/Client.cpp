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

void DoIocpClient() {

	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 100;

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

	NetAddrSptr net = MakeShared<NetAddr>();
	vector<SessionSptr> sessions = netCore.StartConnect(ip, port, clientCnt);

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore.Dispatch(waitMilliSec);
	}
}

int main()
{

	//DoSimpleClient();
	DoIocpClient();

	
	return 0;
}