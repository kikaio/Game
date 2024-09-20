#include "pch.h"
#include "ServerPch.h"


void PrintLn(const char* _msg)
{
    printf("%s\n", _msg);
}

int main()
{
    WsaReady wsa;
    wsa.Ready();
    NetAddr addr;
    addr.SetAddrAny(7777);
    SOCKET listener = SocketUtil::CreateTCP();
    SocketUtil::SetReuse(listener, true);
    if (NO_ERROR != ::bind(listener, addr.SockAddr(), sizeof(SOCKADDR))) {
        PrintLn("bind failed");
        return 0;
    }

    if (NO_ERROR != ::listen(listener, 5)) {
        PrintLn("listen failed");
        return 0;
    }
    NetAddr clientAddr;
    int size = sizeof(SOCKADDR);
    
    SOCKET clientSock = ::accept(listener, clientAddr.SockAddr(), &size);
    if (clientSock == INVALID_SOCKET) {
        int32_t err = WSAGetLastError();
        printf("accept failed - %d\n", err);
        return 0;
    }

    array<BYTE, 256> buffer = {0,};
    while (true) {
        // todo : recv
        int recved = ::recv(clientSock, reinterpret_cast<char*>(buffer.data()), 256, NULL);
        PrintLn(reinterpret_cast<const char*>(buffer.data()));
        printf("recved bytes : %d\n", recved);
        // todo : send echo
        
        int sended = ::send(clientSock, reinterpret_cast<const char*>(buffer.data()), recved, NULL);
        printf("send echo : %s\n", buffer.data());
    }

    return 0;
}
