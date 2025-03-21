#include "pch.h"
#include "RedisConfig.h"

RedisConfig::RedisConfig(const RedisConfig& _other)
{
	redisName = _other.redisName;
	nameStr = _other.nameStr;
	hostStr = _other.hostStr;
	pw = _other.pw;
	port = _other.port;
	dbNo = _other.dbNo;
	poolCnt = _other.poolCnt;
}

void RedisConfig::Init(rapidjson::Value& _doc) {
	ASSERT_CRASH(_doc.HasMember("name"));
	ASSERT_CRASH(_doc.HasMember("host"));
	ASSERT_CRASH(_doc.HasMember("port"));
	ASSERT_CRASH(_doc.HasMember("db_no"));
	ASSERT_CRASH(_doc.HasMember("pool_cnt"));

	nameStr = _doc["name"].GetString();
	hostStr = _doc["host"].GetString();
	if(_doc.HasMember("pw")) {
		pw = _doc["pw"].GetString();
	}
	port = _doc["port"].GetInt();
	dbNo = _doc["db_no"].GetInt();
	poolCnt = _doc["pool_cnt"].GetInt();
	poolCnt = poolCnt < 1 ? 1: poolCnt;

	auto nameVal = magic_enum::enum_cast<RedisName>(nameStr.c_str());
	redisName = nameVal.value_or(RedisName::None);
	ASSERT_CRASH(redisName != RedisName::None);
}

void RedisConfig::Render() {
	printf("======reids config======\n");
	printf("name : %s\n", nameStr.c_str());
	printf("host : %s, port : %d \n", hostStr.c_str(), port);
	printf("dbNo : %d, poolCnt : %d\n", dbNo, poolCnt);
}
