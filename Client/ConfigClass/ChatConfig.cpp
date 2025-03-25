#include "pch.h"
#include "ChatConfig.h"

const string& ChatConfig::Host()
{
	return host;
}

int16_t ChatConfig::Port()
{
	return port;
}

int32_t ChatConfig::IocpThreadCnt()
{
	return iocpThreadCnt;
}
void ChatConfig::Init(const rapidjson::Value& _val) {
	ASSERT_CRASH(_val.HasMember("host"));
	ASSERT_CRASH(_val.HasMember("port"));
	ASSERT_CRASH(_val.HasMember("iocp_thread_cnt"));

	host = _val["host"].GetString();
	port = _val["port"].GetInt();
	iocpThreadCnt = _val["iocp_thread_cnt"].GetInt();
}
