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
	unordered_map < DBConnKey, DBConn, DBConnHasher> keyPerConnMap;
private:
	void Clear();
public:
	sql::Driver* Driver() {
		return driver;
	}
	void MakeDBConnPool(int _cnt, DBProfile _profile, DBNameType _nameType, DBRWType _rwType);
};