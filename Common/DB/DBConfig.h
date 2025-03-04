#pragma once

class DBConfig
{
public:
	DBConfig();
	~DBConfig();
	DBConfig(const DBConfig& _other);
public:
	static string odbcName;
	string dbNameStr = "NONE";
	string hostStr = "NONE";
	string userStr = "NONE";
	string pwStr = "NONE";
	string rwTypeStr = "NONE";
	int32_t port = 0;
	int32_t poolCnt = 0;
	int32_t maxPoolCnt = 0;
	int32_t connTimeoutSec = 10;
	int32_t readTimeoutSec = 3;
	int32_t writeTimeoutSec = 3;
public:
	int32_t curPoolCnt = 0;

public:
	DBNameType dbNameType = DBNameType::NONE;
	RWType rwType = RWType::NONE;

public:
	void Init(rapidjson::Value& _doc);
	void Render();
};

