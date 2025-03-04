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
	map<RWType, DBConfig> commonDBConfMap;
	map<RWType, DBConfig> gameDBConfMap;
private:
	map<RWType, vector<DBConnection*>> commonDBConnMap;
	map<RWType, vector<DBConnection*>> gameDBConnMap;
private:
	void Push(DBConnection* _conn);
public:
	bool Connect(const DBConfig& _conf);
	void Clear();
public:
	shared_ptr<DBConnection> PopCommonDB(RWType _rwType = RWType::READ_WRITE);
	shared_ptr<DBConnection> PopGameDB(RWType _rwType = RWType::READ_WRITE);
public:
	static void ReleaseConn(DBConnection* _conn);
};