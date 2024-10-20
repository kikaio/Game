#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}

bool DBConnectionPool::Connect(int32_t _connectionCnt, string connStr)
{
	LOCK_GUARDDING(sqlConnPool);
	if(::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env) != SQL_SUCCESS) {
		return false;
	}

	if(SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0) != SQL_SUCCESS) {
		return false;
	}
	
	for(int32_t idx = 0; idx < _connectionCnt; idx++) {
		auto _conn = xnew<DBConnection>();
		if(_conn->Connect(env, connStr) == false) {
			return false;
		}



		connections.push_back(_conn);
	}

	return true;
}

void DBConnectionPool::Clear()
{
	LOCK_GUARDDING(sqlConnPool);
	if(env != SQL_NULL_HANDLE) {
		::SQLFreeHandle(SQL_HANDLE_ENV, env);
		env = SQL_NULL_HANDLE;
	}

	for (auto _conn : connections) {
		xfree(_conn);
	}
	connections.clear();
}

DBConnection* DBConnectionPool::Pop()
{
	LOCK_GUARDDING(sqlConnPool);
	if(connections.empty()) {
		return nullptr;
	}

	DBConnection* conn = connections.back();
	connections.pop_back();
	return conn;
}

void DBConnectionPool::Push(DBConnection* _conn)
{
	if(_conn == nullptr) {
		return ;
	}
	LOCK_GUARDDING(sqlConnPool);
	connections.push_back(_conn);
}
