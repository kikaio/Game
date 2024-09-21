#include "pch.h"
#include "ServerPch.h"
#include "Session.h"

void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

int main()
{
    WsaReady wsa;
    wsa.Ready();

    Listener listener(MakeShared<NetAddr>());
    listener.NetAddr()->SetAddrAny(7777);
    if (listener.Bind()) {
        PrintLn("bind failed");
        return 0;
    }

    if (listener.Listen()) {
        PrintLn("listen failed");
        return 0;
    }

    NetAddr clientAddr;
    int size = sizeof(SOCKADDR);
    {
        SessionSptr client = MakeShared<Session>();
        client->sock = listener.Accept(client->SockAddr());
        if (client->sock == INVALID_SOCKET) {
            int32_t err = WSAGetLastError();
            printf("accept failed - %d\n", err);
            return 0;
        }
    }

    return 0;
}
