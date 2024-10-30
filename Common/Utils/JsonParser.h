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
protected:
	rapidjson::Document ReadFromFile(std::string _path);
	bool WriteToFile(rapidjson::Document& _doc, std::string _path);
protected:
	bool GetInt32(rapidjson::Value& _doc, const char* _name, OUT int32_t& _val);
	bool GetInt32(rapidjson::Value& _doc, std::string _name, OUT int32_t& _val);
	bool GetStr(rapidjson::Value& _doc, const char* _name, OUT std::string& _val);
	bool GetStr(rapidjson::Value& _doc, std::string _name, OUT std::string& _val);
	bool GetValue(rapidjson::Value& _doc, const char* _name, OUT rapidjson::Value& _val);
	bool GetValue(rapidjson::Value& _doc, std::string _name, OUT rapidjson::Value& _val);
	
	bool GetBool(rapidjson::Value& _doc, const char* _name, OUT bool& _ret);
	bool GetBool(rapidjson::Value& _doc, const string& _name, OUT bool& _ret);

	bool GetFromArr(rapidjson::Value& _arr, int32_t _idx, OUT rapidjson::Value& _ele);
	bool ForEach(rapidjson::Value& _arr, function<void(rapidjson::Value&)> _func);

	bool GetArray(rapidjson::Value& _val, const char* _name, OUT rapidjson::Value& _arr);
	bool GetArray(rapidjson::Value& _val, const string& _name, OUT rapidjson::Value& _arr);

	bool SetString(rapidjson::Value& _doc, const char* _name, std::string& _val);
	bool SetInt32(rapidjson::Value& _doc, const char* _name, int32_t _val);
	bool SetInt64(rapidjson::Value& _doc, const char* _name, int64_t _val);

};