#include "pch.h"
#include "MasterConfig.h"

const string& MasterConfig::Host()
{
	return host;
}

uint16_t MasterConfig::Port()
{
	return port;
}

int32_t MasterConfig::IocpThreadCnt()
{
	return iocpThreadCnt;
}
void MasterConfig::Init(const rapidjson::Value& _val) {
	ASSERT_CRASH(_val.HasMember("host"));
	ASSERT_CRASH(_val.HasMember("port"));
	ASSERT_CRASH(_val.HasMember("iocp_thread_cnt"));

	host = _val["host"].GetString();
	port = _val["port"].GetUint();
	iocpThreadCnt = _val["iocp_thread_cnt"].GetInt();
}

void MasterConfig::Render() {
	CLIENT_DEBUG_LOG("[master]======");
	CLIENT_DEBUG_LOG("host : {}:{}", host, port);
	CLIENT_DEBUG_LOG("iocp thread cnt : {}", iocpThreadCnt);
	return;
}

