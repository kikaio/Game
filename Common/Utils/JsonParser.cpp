#include "pch.h"
#include "JsonParser.h"

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

rapidjson::Document JsonParser::ReadFromFile(string _path)
{
	rapidjson::Document doc;
	FILE* fp = fopen(_path.c_str(), "rb");
	if(fp == nullptr) {
		//todo : error logging
		return doc;
	}

	array<char, 65536> readBuf;
	rapidjson::FileReadStream fs(fp, readBuf.data(), readBuf.size());
	doc.ParseStream(fs);
	return doc;
}

bool JsonParser::WriteToFile(rapidjson::Document& _doc, string _path)
{
	rapidjson::StringBuffer sb;
	rapidjson::Writer<rapidjson::StringBuffer> writer(sb);
	_doc.Accept(writer);

	std::ofstream outFile(_path);
	if(outFile.is_open()) {
		outFile << sb.GetString();
		outFile.close();
	}
	return false;
}

int32_t JsonParser::GetInt32(rapidjson::Document& _doc, const char* _name)
{
	if(_doc.HasMember(_name)) {
		return _doc[_name].GetInt();
	}
	return 0;
}

int32_t JsonParser::GetInt32(rapidjson::Document& _doc, string _name)
{
	return GetInt32(_doc, _name.c_str());
}

string JsonParser::GetStr(rapidjson::Document& _doc, const char* _name)
{
	if(_doc.HasMember(_name)) {
		return _doc[_name].GetString();
	}
	return string();
}

string JsonParser::GetStr(rapidjson::Document& _doc, string _name)
{
	return GetStr(_doc, _name.c_str());
}

bool JsonParser::SetString(rapidjson::Document& _doc, const char* _name, string _val)
{
	if(_doc.HasMember(_name)) {
		_doc[_name].SetString(_val.c_str(), _val.size());
	}
	else {
		rapidjson::Value _str(rapidjson::kStringType);
		_str.SetString(_val.c_str(), _val.size());
		_doc[_name] = _str;
	}
	return true;
}

bool JsonParser::SetInt32(rapidjson::Document& _doc, const char* _name, int32_t _val)
{
	if(_doc.HasMember(_name)) {
		_doc[_name].SetInt(_val);
	} 
	else {
		rapidjson::Value intVal(rapidjson::kNumberType);
		intVal.SetInt(_val);
		_doc[_name] = intVal;
	}
	return true;
}

bool JsonParser::SetInt64(rapidjson::Document& _doc, const char* _name, int64_t _val)
{
	if (_doc.HasMember(_name)) {
		_doc[_name].SetInt64(_val);
	}
	else {
		rapidjson::Value intVal(rapidjson::kNumberType);
		intVal.SetInt64(_val);
		_doc[_name] = intVal;
	}
	return true;
}

