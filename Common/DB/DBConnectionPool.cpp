#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32_t _connCnt, const char* _connStr)
{
	LOCK_GUARDDING(dbPoolLock);
	if(SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) != SQL_SUCCESS) {
		return false;
	}
	if(SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS) {
		return false;
	}

	for(int32_t idx = 0; idx < _connCnt; idx++) {
		DBConnection* conn = new DBConnection();
		if(conn->~DBConnection(env, _connStr) == false) {
			return false;
		}
	}

	return true;
}

void DBConnectionPool::Clear()
{
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
