#pragma once

#include <fstream>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"


class JsonParser
{
public:
	JsonParser();
	~JsonParser();
public:
	rapidjson::Document ReadFromFile(string _path);
	bool WriteToFile(rapidjson::Document& _doc, string _path);
public:
	int32_t GetInt32(rapidjson::Document& _doc, const char* _name);
	int32_t GetInt32(rapidjson::Document& _doc, string _name);
	string GetStr(rapidjson::Document& _doc, const char* _name);
	string GetStr(rapidjson::Document& _doc, string _name);

	bool SetString(rapidjson::Document& _doc, const char* _name, string _val);
	bool SetInt32(rapidjson::Document& _doc, const char* _name, int32_t _val);
	bool SetInt64(rapidjson::Document& _doc, const char* _name, int64_t _val);

};