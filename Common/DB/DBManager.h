#pragma once
//#include <mysqlx/xdevapi.h>

#include "mysql_connection.h"
#include "mysql_driver.h"
#include "mysql_error.h"

#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class DBManager : public TLSSingleton<DBManager>
{
public:
	DBManager();
	~DBManager();
private:
	sql::Driver* driver= nullptr;
	map<uint16_t, DBConnPool> keyToConnPool;
private:
	void Clear();
public:
	sql::Driver* Driver() {
		return driver;
	}
public:
	void ReadyConnectionPool(uint32_t _poolCnt, uint8_t _nameVal, uint8_t _rwVal, DBProfile& _profile);
	DBConn& GetConnect(const DBPoolKey& _poolKey);
};