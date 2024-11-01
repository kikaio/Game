#include "pch.h"
#include "DBManager.h"

DBManager::DBManager()
	: driver(get_driver_instance())
{
}

DBManager::~DBManager()
{
	Clear();
}

void DBManager::Clear()
{
}

void DBManager::ReadyConnectionPool(uint32_t _poolCnt, uint8_t _nameVal, uint8_t _rwVal, DBProfile& _profile)
{
	DBPoolKey poolKey(_nameVal, _rwVal);
	uint16_t keyVal = poolKey.GetKey();
	auto finder = keyToConnPool.find(keyVal);
	ASSERT_CRASH(finder == keyToConnPool.end());
	keyToConnPool[keyVal] = DBConnPool(_profile);
	keyToConnPool[keyVal].ReadyConnections(_poolCnt);
}

DBConn& DBManager::GetConnect(const DBPoolKey& _poolKey)
{
	auto finder = keyToConnPool.find(_poolKey.GetKey());
	ASSERT_CRASH(finder != keyToConnPool.end());
	return finder->second.GetConnect(false);
}
