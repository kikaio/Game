#include "pch.h"
#include "GameConfig.h"

const uint16_t GameConfig::ListenPort() { return listenPort; }
const int32_t GameConfig::AcceptCnt() { return acceptCnt; }
const int32_t GameConfig::BackLog() { return backLog; }
const string& GameConfig::Name() { return name; }
const int32_t GameConfig::No() { return no; }


bool GameConfig::ReadFromJson(const rapidjson::Value& _val) {

	//for(auto _iter = _val.MemberBegin(); _iter != _val.MemberEnd(); _iter++) {
	//	printf("name : %s, val : %d\n", _iter->name.GetString(), _iter->value.GetInt());
	//}

	ASSERT_CRASH(_val.HasMember("no"));
	ASSERT_CRASH(_val.HasMember("name"));
	ASSERT_CRASH(_val.HasMember("listen_port"));
	ASSERT_CRASH(_val.HasMember("accept_cnt"));
	ASSERT_CRASH(_val.HasMember("back_log"));
	no = _val["no"].GetInt();
	name = _val["name"].GetString();
	listenPort = _val["listen_port"].GetUint();
	acceptCnt = _val["accept_cnt"].GetInt();
	backLog = _val["back_log"].GetInt();

	return true;
}



void GameConfig::Render() {
	GS_DEBUG_LOG("[game server config]==========");
	GS_DEBUG_LOG("no : {}", no);
	GS_DEBUG_LOG("name : {}", name.c_str());
	GS_DEBUG_LOG("listen port : {}", listenPort);
	GS_DEBUG_LOG("acceptCnt : {}", acceptCnt);
	GS_DEBUG_LOG("backLog : {}", backLog);
}