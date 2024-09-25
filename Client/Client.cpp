#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	this_thread::sleep_for(2s);
	string ip = "127.0.0.1";
	UInt32 port = 7777;

	NetworkCore netCore;

	if (netCore.Ready() == false) {
		printf("net core ready failed\n");
		return 0;
	}
	
	if (netCore.ReadyToConnect() == false) {
		printf("ReadyToConnect failed\n");
		return 0;
	}

	printf("net core ready complete\n");
	int connCnt = 1;
	vector<SessionSptr> sessions = netCore.StartConnect(ip, port, connCnt);
	printf("net core ready regist complete\n");


	while(true) {
		this_thread::sleep_for(1s);
		printf("do something\n");
	}
	return 0;
}