#include "pch.h"
#include "DBConfig.h"

string DBConfig::odbcName = "MysqlODBC";


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
	port = _other.port;
	poolCnt = _other.poolCnt;
	connTimeoutSec = _other.connTimeoutSec;
	readTimeoutSec = _other.readTimeoutSec;
	writeTimeoutSec = _other.writeTimeoutSec;
}

void DBConfig::Init(rapidjson::Value& _val)
{
	ASSERT_CRASH(_val.HasMember("name") && _val["name"].IsString());
	ASSERT_CRASH(_val.HasMember("host") && _val["host"].IsString());
	ASSERT_CRASH(_val.HasMember("user") && _val["user"].IsString());
	ASSERT_CRASH(_val.HasMember("pw") && _val["pw"].IsString());
	ASSERT_CRASH(_val.HasMember("rw_type") && _val["rw_type"].IsString());
	ASSERT_CRASH(_val.HasMember("pool_cnt") && _val["pool_cnt"].IsUint());
	ASSERT_CRASH(_val.HasMember("port") && _val["port"].IsUint());
	ASSERT_CRASH(_val.HasMember("conn_timeout_sec") && _val["conn_timeout_sec"].IsUint());
	ASSERT_CRASH(_val.HasMember("read_timeout_sec") && _val["read_timeout_sec"].IsUint());
	ASSERT_CRASH(_val.HasMember("write_timeout_sec") && _val["write_timeout_sec"].IsUint());


	dbNameStr = _val["name"].GetString();
	hostStr = _val["host"].GetString();
	userStr = _val["user"].GetString();
	pwStr = _val["pw"].GetString();
	rwTypeStr = _val["rw_type"].GetString();
	port = _val["port"].GetUint();
	poolCnt = _val["pool_cnt"].GetUint();
	//해당 DB에 대한 pool의 최대 수.
	if(_val.HasMember("max_pool_cnt") == false || _val["max_pool_cnt"].GetInt() <= poolCnt) {
		maxPoolCnt = poolCnt;
	}
	else {
		maxPoolCnt = _val["max_pool_cnt"].GetInt();
	}

	connTimeoutSec = _val["conn_timeout_sec"].GetUint();
	readTimeoutSec = _val["read_timeout_sec"].GetUint();
	writeTimeoutSec = _val["write_timeout_sec"].GetUint();

	auto magicDBName = magic_enum::enum_cast<DBNameType>(dbNameStr.c_str());
	ASSERT_CRASH(magicDBName.has_value());
	dbNameType = magicDBName.value_or(DBNameType::NONE);
	ASSERT_CRASH(dbNameType != DBNameType::NONE);

	auto magicRWType = magic_enum::enum_cast<RWType>(rwTypeStr.c_str());
	ASSERT_CRASH(magicRWType.has_value());
	rwType = magicRWType.value_or(RWType::NONE);
	ASSERT_CRASH(rwType != RWType::NONE);
}

void DBConfig::Render()
{
	printf("============[config]=========\n");
	printf("DBName : %s\n", dbNameStr.c_str());
	printf("Host : %s\n", hostStr.c_str());
	printf("User : %s\n", userStr.c_str());
	printf("Pw : %s\n", pwStr.c_str());
	printf("Port : %d\n", port);
	printf("RW_Type : %s\n", rwTypeStr.c_str());
	printf("PoolCnt : %d\n", poolCnt);
	printf("connTimeoutSec : %d\n", connTimeoutSec);
	printf("readTimeoutSec : %d\n", readTimeoutSec);
	printf("writeTimeoutSec : %d\n", writeTimeoutSec);
	printf("=============================\n");
}


