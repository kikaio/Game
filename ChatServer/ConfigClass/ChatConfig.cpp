#include "pch.h"
#include "ChatConfig.h"

void ChatConfig::Init(rapidjson::Value& _val) {
	ASSERT_CRASH(_val.HasMember("listen_port"));
	ASSERT_CRASH(_val.HasMember("accept_cnt"));
	ASSERT_CRASH(_val.HasMember("back_log"));
	listenPort = _val["listen_port"].GetInt();
	acceptCnt = _val["accept_cnt"].GetInt();
	backLog = _val["back_log"].GetInt();
}

void ChatConfig::Render() {
	CS_DEBUG_LOG("[Chat Server]=======");
	CS_DEBUG_LOG("listenPort : {}, acceptCnt : {}, backLog : {}", listenPort, acceptCnt, backLog);
}