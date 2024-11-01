#pragma once

class DBWrapper
{
private:
	static void ReadyDatabasePool(JsonReader& _reader);
public:
	static void DatabaseAddFromJsonToManager(const rapidjson::Value& _valArr);
	
};