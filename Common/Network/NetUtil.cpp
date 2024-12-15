#include "pch.h"
#include "NetUtil.h"

bool NetUtil::HostNameToIp(const char* _host, OUT std::string& _ip)
{
	hostent* ent = nullptr;
	in_addr inAddr = {0, };
	long int* addr = nullptr;

	ent = gethostbyname(_host);
	if (ent == nullptr) {
		return false;
	}

	while (*(ent->h_addr_list) != nullptr) {
		addr = (long int*)*ent->h_addr_list;
		inAddr.s_addr = *addr;
		_ip = inet_ntoa(inAddr);
		break;
	}

	return true;
}

uint16_t NetUtil::HostNameToIp(const char* _host)
{
	hostent* ent = nullptr;
	in_addr inAddr = { 0, };
	long int* addr = nullptr;

	ent = gethostbyname(_host);
	if (ent == nullptr) {
		return false;
	}

	while (*(ent->h_addr_list) != nullptr) {
		addr = (long int*)*ent->h_addr_list;
		inAddr.s_addr = *addr;
		break;
	}
	return inAddr.s_addr;
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
