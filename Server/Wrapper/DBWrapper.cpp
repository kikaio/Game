#include "pch.h"
#include "DBWrapper.h"
#include "../ServerEnums.h"


void DBWrapper::ReadyDatabasePool(JsonReader& _dbReader)
{
	string dbName = "";
	string host = "";
	string user = "";
	string pw = "";
	int32_t port = 0;
	string rwTypeStr = "";
	int32_t poolCnt = 0;
	int32_t connTimeoutSec = 10;
	int32_t readTimeoutSec = 3;
	int32_t writeTimeoutSec = 3;


	ASSERT_CRASH(_dbReader.GetStr("name", dbName));
	ASSERT_CRASH(_dbReader.GetStr("host", host));
	ASSERT_CRASH(_dbReader.GetStr("user", user));
	ASSERT_CRASH(_dbReader.GetStr("pw", pw));
	ASSERT_CRASH(_dbReader.GetInt32("port", port));
	ASSERT_CRASH(_dbReader.GetStr("rw_type", rwTypeStr));
	ASSERT_CRASH(_dbReader.GetInt32("pool_cnt", poolCnt));

	_dbReader.GetInt32("connTimeoutSec", connTimeoutSec);
	_dbReader.GetInt32("readTimeoutSec", readTimeoutSec);
	_dbReader.GetInt32("writeTimeoutSec", writeTimeoutSec);

	DBProfile profile(
		host, port, user, pw, dbName, rwTypeStr
		, connTimeoutSec, readTimeoutSec, writeTimeoutSec
	);

	RWType rwType = profile.RwType();
	ASSERT_CRASH(rwType != RWType::NONE);

	auto magicEnumDbNameType = ENUM_FROM_STR(DBNameType, dbName);
	ASSERT_CRASH(magicEnumDbNameType.has_value());
	uint8_t dbNameTypeVal = (uint8_t)magicEnumDbNameType.value();

	auto rWTypeVal = ENUM_TO_INT(rwType);

	DBManager::Get().ReadyConnectionPool(poolCnt, dbNameTypeVal, rWTypeVal, profile);

}

void DBWrapper::DatabaseAddFromJsonToManager(const rapidjson::Value& _valArr)
{
	for(auto _iter = _valArr.Begin(); _iter != _valArr.End(); _iter++) {
		
		JsonReader _dbReader;
		_dbReader.CopyValue(*_iter);
		ReadyDatabasePool(_dbReader);
	}

	return ;
}

bool DBWrapper::TryConnectToDB()
{	
	try {
		DBManager::Get().TryConnect();
	}
	catch(sql::SQLException e) {
		return false;
	}
	return true;
}

DBConn& DBWrapper::GetCommonDBConn(RWType _rwType)
{
	DBPoolKey poolKey((uint8_t)DBNameType::CommonDB, (uint8_t)_rwType);
	DBManager::Get().GetConnect(poolKey);
}
