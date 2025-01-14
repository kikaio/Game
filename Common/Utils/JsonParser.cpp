#include "pch.h"
#include "JsonParser.h"

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

rapidjson::Document JsonParser::ReadFromFile(std::string _path)
{
	rapidjson::Document doc;
	FILE* fp = nullptr;
	fopen_s(&fp, _path.c_str(), "rb");
	if(fp == nullptr) {
		//todo : error logging
		return doc;
	}

	array<char, 60000> readBuf;
	rapidjson::FileReadStream fs(fp, readBuf.data(), readBuf.size());
	doc.ParseStream(fs);
	return doc;
}

bool JsonParser::WriteToFile(rapidjson::Document& _doc, std::string _path)
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

bool JsonParser::GetInt32(rapidjson::Value& _doc, const char* _name, OUT int32_t& _val)
{
	if(_doc.HasMember(_name)) {
		if(_doc[_name].IsInt()) {
			_val = _doc[_name].GetInt();
			return true;
		}
	}
	return false;
}

bool JsonParser::GetInt32(rapidjson::Value& _doc, std::string _name, OUT int32_t& _val)
{
	return GetInt32(_doc, _name.c_str(), _val);
}

bool JsonParser::GetStr(rapidjson::Value& _doc, const char* _name, OUT std::string& _val)
{
	if(_doc.HasMember(_name)) {
		if(_doc[_name].IsString()) {
			_val = _doc[_name].GetString();
			return true;
		}
	}
	return false;
}

bool JsonParser::GetStr(rapidjson::Value& _doc, string _name, OUT std::string& _val)
{
	return GetStr(_doc, _name.c_str(), _val);
}

bool JsonParser::GetValue(rapidjson::Value& _doc, const char* _name, OUT rapidjson::Value& _val)
{
	if(_doc.HasMember(_name) == false) {
		return false;
	}
	_val = _doc[_name];
	return true;
}

bool JsonParser::GetValue(rapidjson::Value& _doc, std::string _name, OUT rapidjson::Value& _val)
{
	return GetValue(_doc, _name.c_str(), _val);
}

bool JsonParser::GetBool(rapidjson::Value& _doc, const char* _name, OUT bool& _ret)
{
	if(_doc.HasMember(_name)) {
		if(_doc[_name].IsBool()) {
			return _doc[_name].GetBool();
		}
	}
	return false;
}

bool JsonParser::GetBool(rapidjson::Value& _doc, const string& _name, OUT bool& _ret)
{
	return GetBool(_doc, _name.c_str(), _ret);;
}

bool JsonParser::GetFromArr(rapidjson::Value& _arr, int32_t _idx, OUT rapidjson::Value& _ele)
{
	if(_arr.IsArray() == false) {
		return false;
	}

	if(_arr.Size() <= _idx) {
		return false;
	}

	_ele = _arr[_idx];

	return true;
}

bool JsonParser::ForEach(rapidjson::Value& _arr, function<void(rapidjson::Value&)> _func)
{
	if (_arr.IsArray() == false) {
		return false;
	}
	for(Value::ValueIterator _iter = _arr.Begin(); _iter != _arr.End(); _iter++) {
		_func(*_iter);
	}
	return true;
}

bool JsonParser::GetArray(rapidjson::Value& _val, const char* _name, OUT rapidjson::Value& _arr)
{
	if(_val.HasMember(_name)) {
		if(_val[_name].IsArray()) {
			_arr = _val[_name].GetArray();
			return true;
		}
	}
	return false;
}

bool JsonParser::GetArray(rapidjson::Value& _val, const string& _name, OUT rapidjson::Value& _arr)
{
	return GetArray(_val, _name.c_str(), _arr);
}

bool JsonParser::SetString(rapidjson::Value& _doc, const char* _name, OUT std::string& _val)
{
	if(_doc.HasMember(_name)) {
		if(_doc[_name].IsString()) {
			_doc[_name].SetString(_val.c_str(), _val.size());
			return true;
		}
		return false;
	}
	else {
		rapidjson::Value _str(rapidjson::kStringType);
		_str.SetString(_val.c_str(), _val.size());
		_doc[_name] = _str;
	}
	return true;
}

bool JsonParser::SetInt32(rapidjson::Value& _doc, const char* _name, int32_t _val)
{
	if(_doc.HasMember(_name)) {
		if(_doc[_name].IsInt()) {
			_doc[_name].SetInt(_val);
			return true;
		}
		return false;
	} 
	else {
		rapidjson::Value intVal(rapidjson::kNumberType);
		intVal.SetInt(_val);
		_doc[_name] = intVal;
	}
	return true;
}

bool JsonParser::SetInt64(rapidjson::Value& _doc, const char* _name, int64_t _val)
{
	if (_doc.HasMember(_name)) {
		if(_doc[_name].IsInt64()) {
			_doc[_name].SetInt64(_val);
			return true;
		}
		return false;
	}
	else {
		rapidjson::Value intVal(rapidjson::kNumberType);
		intVal.SetInt64(_val);
		_doc[_name] = intVal;
	}
	return true;
}

