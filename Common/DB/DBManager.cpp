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
	for (auto& pair : keyPerConnMap) {
		pair.second.Close();
	}
	keyPerConnMap.clear();
}

void DBManager::MakeDBConnPool(int _cnt, DBProfile _profile, DBNameType _nameType, DBRWType _rwType)
{
	for (uint8_t idx = 0; idx < _cnt; idx++) {
		DBConnKey connKey(idx, (uint8_t)_nameType, (uint16_t)_rwType);
		DBConn conn(_profile);
	}
}
