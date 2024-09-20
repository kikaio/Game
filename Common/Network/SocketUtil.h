#pragma once

class SocketUtil 
{
public:
	static SOCKET CreateTCP();
	static SOCKET CreateIocpTCP();

	static SOCKET CreateUDP(); 

	static void SetReuse(SOCKET _sock, bool _flag); 

	static void SetLinger(SOCKET _sock, DWORD _onoff, DWORD _linger); 

	static void SetConditionalAccept(SOCKET _listener);

};