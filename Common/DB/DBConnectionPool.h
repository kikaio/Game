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
	atomic<bool> isCleared = false;
	SQLHENV env = SQL_NULL_HANDLE;
	vector<DBConnection*> connections;
private:
	map<RWType, vector<DBConnection*>> commonDBConnMap;
	map<RWType, vector<DBConnection*>> gameDBConnMap;
public:
	bool Connect(int32_t _connCnt, string _odbcName, string _host, string _user, string _pwd, DBNameType _dbNameType, RWType _rwType);
	void Clear();
public:
	DBConnection* PopCommonDB(RWType _rwType = RWType::READ_WRITE);
	DBConnection* PopGameDB(RWType _rwType = RWType::READ_WRITE);
	void Push(DBConnection* _conn);

};