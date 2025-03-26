#include "pch.h"
#include "ChatConfig.h"


uint16_t ChatConfig::ListenPort() {
	return listenPort;
}

int32_t ChatConfig::AcceptCnt() {
	return acceptCnt;
}

int32_t ChatConfig::BackLog() {
	return backLog;
}

const string& ChatConfig::Name() {
	return name;
}

int32_t ChatConfig::No() {
	return no;
}

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
	CS_DEBUG_LOG("name : {}, no : {}", name, no);
	CS_DEBUG_LOG("listenPort : {}, acceptCnt : {}, backLog : {}", listenPort, acceptCnt, backLog);
}