#pragma once

class SocketUtil 
{
private:
	static GUID guidAcceptEx;
	static GUID guidConnectEx;
	static GUID guidDisconnectEx;
public:
	static LPFN_ACCEPTEX lpfnAcceptEx;
	static BOOL SetAcceptableListener(SOCKET _sock);

	static LPFN_CONNECTEX lpfnConnectEx;

	static LPFN_DISCONNECTEX lpfnDisconnectEx;

public:
	static SOCKET CreateTCP();
	static SOCKET CreateIocpTCP();

	static SOCKET CreateUDP(); 

	static void SetReuse(SOCKET _sock, bool _flag); 

	static void SetLinger(SOCKET _sock, DWORD _onoff, DWORD _linger); 

	static void SetConditionalAccept(SOCKET _listener);

	static BOOL UpdateAcceptToSock(SOCKET _client, SOCKET _listener);

	static BOOL AcceptEx(ListenerSptr _listener, SessionSptr _client);

};