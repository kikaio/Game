#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32_t _connCnt, string _odbcName, string _host, string _user, string _pwd, DBNameType _dbNameType, RWType _rwType)
{
	LOCK_GUARDDING(dbPoolLock);
	SQLRETURN sqlRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	if (sqlRet != SQL_SUCCESS && sqlRet != SQL_SUCCESS_WITH_INFO) {
		printf("SQL Return : %d\n", sqlRet);
		return false;
	}

	sqlRet = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0);
	if (sqlRet != SQL_SUCCESS && sqlRet != SQL_SUCCESS_WITH_INFO) {
		printf("SQL Return : %d\n", sqlRet);
		return false;
	}

	for(int32_t idx = 0; idx < _connCnt; idx++) {
		DBConnection* _conn = new DBConnection();
		if(_conn->Connect(env, _odbcName, _host, _user, _pwd, _dbNameType, _rwType) == false) {
			return false;
		}

		switch (_conn->DbNameType()) {
		case DBNameType::CommonDB: {
			auto ret = commonDBConnMap.emplace(_rwType, vector<DBConnection*>());
			(ret.first)->second.push_back(_conn);
			break;
		}
		case DBNameType::GameDB: {
			auto ret = gameDBConnMap.emplace(_rwType, vector<DBConnection*>());
			(ret.first)->second.push_back(_conn);
			break;
		}
		}
	}

	return true;
}

void DBConnectionPool::Clear()
{
	if (isCleared.exchange(true) == true) {
		return ;	
	}
	LOCK_GUARDDING(dbPoolLock);
	if(env != SQL_NULL_HANDLE) {

		SQLFreeHandle(SQL_HANDLE_ENV, env);
		env = SQL_NULL_HANDLE;
		
	}

	for(auto _dbConn : connections) {
		delete(_dbConn);
	}

	connections.clear();
}

DBConnection* DBConnectionPool::PopCommonDB(RWType _rwType) {
	LOCK_GUARDDING(dbPoolLock);
	if (commonDBConnMap.empty()) {
		return nullptr;
	}
	auto iter = commonDBConnMap.find(_rwType);
	if (iter == commonDBConnMap.end()) {
		return nullptr;
	}
	if (iter->second.empty()) {
		return nullptr;
	}
	auto conn = iter->second.back();
	iter->second.pop_back();
	return conn;
}

DBConnection* DBConnectionPool::PopGameDB(RWType _rwType) {
	LOCK_GUARDDING(dbPoolLock);
	if (gameDBConnMap.empty()) {
		return nullptr;
	}
	auto iter = gameDBConnMap.find(_rwType);
	if (iter == gameDBConnMap.end()) {
		return nullptr;
	}
	if (iter->second.empty()) {
		return nullptr;
	}
	auto conn = iter->second.back();
	iter->second.pop_back();
	return conn;
}

void DBConnectionPool::Push(DBConnection* _conn)
{
	LOCK_GUARDDING(dbPoolLock);
	switch (_conn->DbNameType()) {
	case DBNameType::CommonDB: {
		auto iter = commonDBConnMap.emplace(_conn->RwType(), vector<DBConnection*>());
		iter.first->second.push_back(_conn);
		break;
	}
	case DBNameType::GameDB: {
		auto iter = gameDBConnMap.emplace(_conn->RwType(), vector<DBConnection*>());
		iter.first->second.push_back(_conn);
		break;
	}
	default: {
		//todo : error logging
		break;
	}
	}
}
