#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	string ip = "127.0.0.1";
	int port = 7777;
	int clientCnt = 1;

	NetworkCore netCore;
	if (netCore.Ready() == false) {
		//todo : ASSERT
		return 0;
	}
	printf("wsa standby.\n");
	
	if (netCore.ReadyToConnect() == false) {
		printf("ReadyToConnect failed\n");
		return 0;
	}
	
	vector<SessionSptr> sessions = netCore.StartConnect(ip, port, clientCnt);

	UInt32 waitMilliSec = INFINITE;
	while (true) {
		netCore.Dispatch(waitMilliSec);
	}

	return 0;
}