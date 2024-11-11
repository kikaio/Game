#pragma once

class DBConnection;

class DBConnectionPool : public Singleton<DBConnectionPool>
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
	bool Connect(int32_t _connCnt, string _odbcName, string _host, string _user, string _pwd, int32_t _dbNameVal, int32_t _rwVal);
	void Clear();
public:
	DBConnection* Pop();
	void Push(DBConnection* _conn);
};