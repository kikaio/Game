#pragma once

class JsonReader : public JsonParser
{
private:
	rapidjson::Document doc;
public:
	void ReadFile(string _path);
	bool CopyDoc(const rapidjson::Document& _other);
	bool CopyValue(const rapidjson::Value& _other);
	bool CopyObj(const char* _name, const rapidjson::Value& _val);
	bool CopyObj(const string& _name, const rapidjson::Value& _val);
	
	bool GetInt32(const char* _name, OUT int32_t& _ret);
	bool GetInt32(const string& _name, OUT int32_t& _ret);

	bool GetStr(const char* _name, OUT string& _ret);
	bool GetStr(const string& _name, OUT string& _ret);

	bool GetBool(const char* _name, OUT bool& _ret);
	bool GetBool(const string& _name, OUT bool& _ret);

	bool GetArray(const char* _name, OUT rapidjson::Value& _val);
	bool GetArray(const string& _name, OUT rapidjson::Value& _val);

	bool GetObject(const char* _name, OUT rapidjson::Value& _out);
	bool GetObject(const string& _name, OUT rapidjson::Value& _out);

};