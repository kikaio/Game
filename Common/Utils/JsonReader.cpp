#include "pch.h"
#include "JsonReader.h"

void JsonReader::ReadFile(string _path)
{
	doc = JsonParser::ReadFromFile(_path);
}

bool JsonReader::CopyDoc(const Document& _other)
{
	doc.CopyFrom(_other, doc.GetAllocator());
	return true;
}

bool JsonReader::CopyValue(const rapidjson::Value& _other) {
	doc.SetObject();
	doc.CopyFrom(_other, doc.GetAllocator());
	return false;
}

bool JsonReader::CopyObj(const char* _name, const rapidjson::Value& _val)
{
	if(_val.HasMember(_name) == false) {
		return false;
	}
	doc.CopyFrom(_val[_name], doc.GetAllocator());
	return true;
}

bool JsonReader::CopyObj(const string& _name, const rapidjson::Value& _val)
{
	return CopyObj(_name.c_str(), _val);
}

bool JsonReader::GetInt32(const char* _name, OUT int32_t& _ret)
{
	return JsonParser::GetInt32(doc, _name, _ret);
}

bool JsonReader::GetInt32(const string& _name, OUT int32_t& _ret)
{
	return GetInt32(_name.c_str(), _ret);
}

bool JsonReader::GetStr(const char* _name, OUT string& _ret)
{

	return JsonParser::GetStr(doc, _name, _ret);
}

bool JsonReader::GetStr(const string& _name, OUT string& _ret)
{
	return GetStr(_name.c_str(), _ret);
}

bool JsonReader::GetBool(const char* _name, OUT bool& _ret)
{
	return JsonParser::GetBool(doc, _name, _ret);
}

bool JsonReader::GetBool(const string& _name, OUT bool& _ret)
{
	return GetBool(_name.c_str(), _ret);
}

bool JsonReader::GetArray(const char* _name, OUT rapidjson::Value& _val) 
{
	return JsonParser::GetArray(doc, _name, _val);
}

bool JsonReader::GetArray(const string& _name, OUT rapidjson::Value& _val) 
{
	return GetArray(_name.c_str(), _val);
}