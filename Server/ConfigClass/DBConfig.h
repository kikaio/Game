#pragma once

class DBConfig
{
public:
	DBConfig();
	~DBConfig();
	DBConfig(const DBConfig& _other);
public:
	string dbNameStr = "NONE";
	string hostStr = "NONE";
	string userStr = "NONE";
	string pwStr = "NONE";
	string rwTypeStr = "NONE";
	int32_t poolCnt = 0;
public:
	void Init(rapidjson::Value& _doc);
	void Render();
};
