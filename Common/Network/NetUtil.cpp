#include "pch.h"
#include "NetUtil.h"

bool NetUtil::HostNameToIp(const char* _host, OUT std::string& _ip)
{
	addrinfo addrHint = {0, };
	addrinfo* servinfo = nullptr;

	addrHint.ai_family = AF_INET;
	addrHint.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(_host, "http", &addrHint, &servinfo) != NO_ERROR) {
		return false;
	}

	char buf[80] = { 0, };
	for (auto _ptr = servinfo; _ptr != nullptr; _ptr = _ptr->ai_next) {
		sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(_ptr->ai_addr);
		inet_ntop(_ptr->ai_family, &(addr->sin_addr), buf, sizeof(buf));
		_ip = buf;
		break;
	}

	return true;
}

int32_t NetUtil::HostNameToIp(const char* _host)
{
	addrinfo addrHint = { 0, };
	addrinfo* servinfo = nullptr;
	uint16_t ret = 0;
	addrHint.ai_family = AF_INET;
	addrHint.ai_socktype = SOCK_STREAM;

	if (getaddrinfo(_host, "http", &addrHint, &servinfo) != NO_ERROR) {
		return ret;
	}

	char buf[80] = {0, };
	for(auto _ptr = servinfo; _ptr != nullptr; _ptr = _ptr->ai_next) {
		sockaddr_in* addr = reinterpret_cast<sockaddr_in*>(_ptr->ai_addr);
		inet_ntop(_ptr->ai_family, &(addr->sin_addr), buf, sizeof(buf));
		ret = ntohl((addr->sin_addr).s_addr);
		break;
	}

	return ret;
}

bool NetUtil::IsUsedAddr(sockaddr_in _addr, bool _b_tcp)
{
	bool ret = false;

	SOCKET socket = ::socket(AF_INET, _b_tcp ? SOCK_STREAM : SOCK_DGRAM, 0);
	if (socket == INVALID_SOCKET) {
		return false;
	}

	if (::bind(socket, reinterpret_cast<sockaddr*>(&_addr), sizeof(_addr)) == INVALID_SOCKET) {
		ret = true;
	}
	closesocket(socket);
	return ret;
}
