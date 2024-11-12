#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32_t _connCnt, string _odbcName, string _host, string _user, string _pwd, int32_t _dbNameVal, int32_t _rwVal)
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
		if(_conn->Connect(env, _odbcName, _host, _user, _pwd, _dbNameVal, _rwVal) == false) {
			return false;
		}
		connections.push_back(_conn);
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

DBConnection* DBConnectionPool::Pop()
{
	LOCK_GUARDDING(dbPoolLock);
	if(connections.empty()) {
		return nullptr;
	}
	DBConnection* conn = connections.back();
	connections.pop_back();
	return conn;
}

void DBConnectionPool::Push(DBConnection* _conn)
{
	LOCK_GUARDDING(dbPoolLock);
	if(_conn == nullptr) {
		return;
	}
	connections.push_back(_conn);
}
