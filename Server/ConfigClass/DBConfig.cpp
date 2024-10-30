#include "pch.h"
#include "DBConfig.h"


DBConfig::DBConfig()
{
}

DBConfig::~DBConfig()
{
}

DBConfig::DBConfig(const DBConfig& _other)
{
	dbNameStr = _other.dbNameStr;
	hostStr= _other.hostStr;
	userStr= _other.userStr;
	pwStr= _other.pwStr;
	rwTypeStr= _other.rwTypeStr;
	poolCnt= _other.poolCnt;
}

void DBConfig::Init(rapidjson::Value& _val)
{
	JsonReader reader;
	reader.CopyValue(_val);
	ASSERT_CRASH(reader.GetStr("name", OUT dbNameStr));
	ASSERT_CRASH(reader.GetStr("host", OUT hostStr));
	ASSERT_CRASH(reader.GetStr("user", OUT userStr));
	ASSERT_CRASH(reader.GetStr("pw", OUT pwStr));
	ASSERT_CRASH(reader.GetStr("rw_type", OUT rwTypeStr));

	int32_t _poolCnt = 0;
	ASSERT_CRASH(reader.GetInt32("pool_cnt", OUT _poolCnt));
	poolCnt = static_cast<int8_t>(_poolCnt);
}

void DBConfig::Render()
{
	printf("============[config]=========\n");
	printf("DBName : %s\n", dbNameStr.c_str());
	printf("Host : %s\n", hostStr.c_str());
	printf("User : %s\n", userStr.c_str());
	printf("Pw : %s\n", pwStr.c_str());
	printf("RW_Type : %s\n", rwTypeStr.c_str());
	printf("PoolCnt : %d\n", poolCnt);
	printf("=============================\n");
}


