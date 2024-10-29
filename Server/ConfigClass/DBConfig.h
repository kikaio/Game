#pragma once

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"


class DBConfig 
{
public:
	DBConfig();
	~DBConfig();
	DBConfig(const DBConfig& _other) = delete;
	DBConfig(DBConfig&& _other) = delete;
public:
	string dbName;
	string user;
	string pw;
	string rwType;
	int8_t poolCnt;
public:
	void Init(rapidjson::Document& _doc);
};
