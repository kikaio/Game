#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

void DoIocpServer() {
    int accepterCnt = 1;
    int backlog = 100;
    int port = 7777;
    NetworkCore netCore;
    if (netCore.Ready() == false) {
        return ;
    }
    printf("wsa standby.\n");

    NetworkCore::CreateSessionFactory = [] {
        return MakeShared<UserSession>();
    };

    ListenerSptr listener = MakeShared<Listener>(port);
    netCore.ReadyToAccept(listener, backlog, accepterCnt);

    printf("accept ready\n");

    UInt32 waitMilliSec = INFINITE;
    while(true) {
        netCore.Dispatch(waitMilliSec);
    }
}

void DoSimpleServer() {
    WSAData wsaData = {};
    WSAStartup(MAKEWORD(2, 2), &wsaData);
    SOCKET sock = ::socket(AF_INET, SOCK_STREAM, 0);
    int port = 7777;
    NetAddr netAddr;
    netAddr.SetAddrAny(port);

    if (::bind(sock, netAddr.SockAddr(), sizeof(SOCKADDR)) == SOCKET_ERROR)
        return ;
    if (::listen(sock, 100) == SOCKET_ERROR)
        return ;

    printf("accept Start\n");
    SOCKADDR_IN clientAddr = {};
    int size = sizeof(SOCKADDR);
    SOCKET client = ::accept(sock, (SOCKADDR*)&clientAddr, &size);
    if (client != INVALID_SOCKET) {
        int a = 10;
    }
    printf("accept Fin\n");
    while (true) {
        this_thread::sleep_for(3s);
    }

    WSACleanup();
}

int main()
{
    //DoSimpleServer();
    DoIocpServer();

    return 0;
}
