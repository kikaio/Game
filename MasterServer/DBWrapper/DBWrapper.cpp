#include "pch.h"
#include "DBWrapper.h"
#include "DBWrapper.h"

bool DBWrapper::ReadDBConfigFile()
{
	JsonReader jr;
	jr.ReadFile("./Configs/ServerConfig.json");
	rapidjson::Value dbs(kArrayType);
	jr.GetArray("db_configs", OUT dbs);
	for (auto iter = dbs.Begin(); iter != dbs.End(); iter++) {
		JsonReader _jr;
		string name, host, user, pw, rwTypeStr;
		int32_t port = 0, poolCnt = 0;
		_jr.CopyValue(*iter);
		_jr.GetStr("name", OUT name);
		_jr.GetStr("host", OUT host);
		_jr.GetStr("user", OUT user);
		_jr.GetStr("pw", OUT pw);
		_jr.GetInt32("port", OUT port);
		_jr.GetStr("rw_type", OUT rwTypeStr);
		_jr.GetInt32("pool_cnt", OUT poolCnt);

		auto rwCastRet = magic_enum::enum_cast<RWType>(rwTypeStr.c_str());
		ASSERT_CRASH(rwCastRet.has_value());
		RWType rwType = rwCastRet.value();
		auto dbNameCastRet = magic_enum::enum_cast<DBNameType>(name.c_str());
		ASSERT_CRASH(dbNameCastRet.has_value());
		DBNameType dbNameType = dbNameCastRet.value();
		array<char, MAX_PATH> connStrArr = { 0, };

		string odbcName = "MysqlODBC";
		ASSERT_CRASH(DBConnectionPool::Get().Connect(poolCnt, odbcName, host, user, pw, dbNameType, rwType));
		continue;
	}
	return true;
}
