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
		DBConfig _config;
		_config.Init(*iter);
		ASSERT_CRASH(DBConnectionPool::Get().Connect(_config));
		continue;
	}
	return true;
}
