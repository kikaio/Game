#include "pch.h"
#include "MasterConfig.h"

const string& MasterConfig::Host()
{
	return host;
}

int16_t MasterConfig::Port()
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
	port = _val["port"].GetInt();
	iocpThreadCnt = _val["iocp_thread_cnt"].GetInt();
}
