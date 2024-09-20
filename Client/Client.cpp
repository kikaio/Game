#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	WsaReady wsa;
	wsa.Ready();

	SOCKET clientSock = SocketUtil::CreateTCP();
	if (clientSock == INVALID_SOCKET) {
		PrintLn("socket Create failed");
		return 0;
	}

	NetAddr serverAddr;
	serverAddr.SetAddr("127.0.0.1", 7777);

	if (SOCKET_ERROR == connect(clientSock, serverAddr.SockAddr(), sizeof(SOCKADDR))) {
		PrintLn("connect failed");
		return 0;
	}

	string msg = "Stay awhile a listen";
	string msg2 = "Bye Bye Bye";
	bool change = true;
	array<BYTE, 256> buffer = { 0, };
	while (true) {
		int sended = 0;
		if (change) {
			sended = send(clientSock, reinterpret_cast<const char*>(msg.data()), (int)msg.size(), NULL);
		}
		else {
			sended = send(clientSock, reinterpret_cast<const char*>(msg2.data()), (int)msg2.size(), NULL);
		}
		printf("sended bytes : %d\n", sended);
		change = !change;
		int recved = recv(clientSock, reinterpret_cast<char*>(buffer.data()), 256, NULL);
		printf("recved bytes : %d\n", recved);
		PrintLn(reinterpret_cast<const char*>(buffer.data()));
		this_thread::sleep_for(1s);
	}

	return 0;
}