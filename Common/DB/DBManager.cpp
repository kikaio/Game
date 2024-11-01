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

//todo : check connect logic이 현재 논리적으로 이상함.
bool DBManager::CheckConnect(DBPoolKey _poolKey)
{
	auto finder = keyToConnPool.find(_poolKey.GetKey());
	ASSERT_CRASH(finder != keyToConnPool.end());
	finder->second.CheckConnect();
	return true;
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

void DBManager::TryConnect()
{
	for(auto& _pair : keyToConnPool) {
		CheckConnect(_pair.first);
	}
}

DBConn& DBManager::GetConnect(const DBPoolKey& _poolKey)
{
	auto finder = keyToConnPool.find(_poolKey.GetKey());
	ASSERT_CRASH(finder != keyToConnPool.end());
	return finder->second.GetConnect(false);
}

void DBManager::KeepAlive()
{
	for(auto& _pair : keyToConnPool) {
		_pair.second.KeepAlive();
	}
}
