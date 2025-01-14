#pragma once

class RedisConfig
{
public:
	RedisConfig() {}
	RedisConfig(const RedisConfig& _other);
public:
	RedisName redisName = RedisName::None;
	string nameStr = "none";
	string hostStr = "NONE";
	int32_t port = 0;
	int32_t dbNo = 0;
	int32_t poolCnt = 1;
public:
	void Init(rapidjson::Value& _doc);
	void Render();
};
