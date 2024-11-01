#pragma once

class DBWrapper
{
private:
	static void ReadyDatabasePool(JsonReader& _reader);
public:
	static void DatabaseAddFromJsonToManager(const rapidjson::Value& _valArr);
public:
	static DBConn& GetCommonDBConn(RWType _rwType = RWType::READ_WRITE);
};