#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	this_thread::sleep_for(2s);

	NetAddrSptr addr = MakeShared<NetAddr>();
	addr->SetAddr("127.0.0.1", 7777);
	WsaReady wsaReady;
	wsaReady.Ready();

	SOCKET sock = SocketUtil::CreateIocpTCP();
	printf("try connect to server....\n");
	if(connect(sock, addr->SockAddr(), sizeof(SOCKADDR)) == SOCKET_ERROR) {
		int err = WSAGetLastError();
		printf("connect failed - err : %d\n", err);
		return 0;
	}
	printf("connect successed\n");

	while(true) {
		this_thread::sleep_for(1s);
	}
	return 0;
}