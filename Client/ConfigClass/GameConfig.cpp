#include "pch.h"
#include "GameConfig.h"

const string& GameConfig::Host()
{
	return host;
}

uint16_t GameConfig::Port()
{
	return port;
}

int32_t GameConfig::IocpThreadCnt()
{
	return iocpThreadCnt;
}
void GameConfig::Init(const rapidjson::Value& _val) {
	ASSERT_CRASH(_val.HasMember("host"));
	ASSERT_CRASH(_val.HasMember("port"));
	ASSERT_CRASH(_val.HasMember("iocp_thread_cnt"));

	host = _val["host"].GetString();
	port = _val["port"].GetUint();
	iocpThreadCnt = _val["iocp_thread_cnt"].GetInt();
}

void GameConfig::Render() {
	CLIENT_DEBUG_LOG("[game]======");
	CLIENT_DEBUG_LOG("host : {}:{}", host, port);
	CLIENT_DEBUG_LOG("iocp thread cnt : {}", iocpThreadCnt);
	return ;
}

