#pragma once

class SocketUtil 
{
public:
	static SOCKET CreateTCP() {
		return socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	}

	static SOCKET CreateUDP() {
		return socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	}

	static void SetReuse(SOCKET& _sock, bool _flag) {
		setsockopt(_sock, SOL_SOCKET, SO_REUSEADDR, reinterpret_cast<const char*>(&_flag), sizeof(_flag));
	}

	static void SetLinger(SOCKET& _sock, DWORD _onoff, DWORD _linger) {
		setsockopt(_sock, SO_LINGER, _onoff, reinterpret_cast<const char*>(&_linger), sizeof(_linger));
	}
};