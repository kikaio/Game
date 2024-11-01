#pragma once

class DBConnPool
{
private :
	static DBConn defDBConn;
public:
	DBConnPool() {
	}
	DBConnPool(const DBProfile& _profile) 
		: dbProfile(_profile)
	{}
private:
	DBProfile dbProfile;
	vector<DBConn> connections;
	int32_t curIdx = 0;
public:
	void ReadyConnections(uint32_t _poolCnt);
public:
	DBConn& GetConnect(bool _isRand = false);
	const DBProfile& Profile();
	void CheckConnect();
	void KeepAlive();
};

