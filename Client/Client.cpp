#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	NetAddrSptr addr = MakeShared<NetAddr>();
	addr->SetAddr("127.0.0.1", 7777);
	WsaReady wsaReady;

	SOCKET sock = SocketUtil::CreateIocpTCP();
	if(connect(sock, addr->SockAddr(), sizeof(SOCKADDR)) == false) {
		printf("connect failed\n");
		return 0;
	}
	printf("connect successed\n");

	while(true) {
		this_thread::sleep_for(1s);
	}
	return 0;
}