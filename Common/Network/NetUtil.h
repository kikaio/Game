#pragma once

class NetUtil {
	static bool HostNameToIp(const char* _host, OUT std::string& _ip);
	static int32_t HostNameToIp(const char* _host);
	static bool IsUsedAddr(sockaddr_in _addr, bool _b_tcp);
};