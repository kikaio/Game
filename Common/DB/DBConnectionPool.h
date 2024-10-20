#pragma once

#include "DBConnection.h"

class DBConnectionPool : public Singleton<DBConnectionPool>
{
public:
	DBConnectionPool();
	~DBConnectionPool();
private:
	VAL_LOCK(sqlConnPool);
	SQLHENV env = SQL_NULL_HANDLE;
	vector<DBConnection*> connections;
public:
	bool Connect(int32_t _connectionCnt, string connStr);
	void Clear();

	DBConnection* Pop();
	void Push(DBConnection* _conn);
};