#pragma once

class DBConnection;

class DBConnectionPool
{
public:
	DBConnectionPool();
	~DBConnectionPool();
private:
	VAL_LOCK(dbPoolLock);
private:
	SQLHENV env = SQL_NULL_HANDLE;
	vector<DBConnection*> connections;
public:
	bool Connect(int32_t _cnnCnt, const char* _connStr);
	void Clear();
public:
	DBConnection* Pop();
	void Push(DBConnection* _conn);
};