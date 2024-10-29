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

class DBConn;

class DBProfile
{
	friend class DBConn;
public:
	DBProfile() {
	}
	DBProfile(string _host, string _user, string _pw, string _database) 
		: host(_host), user(_user), pw(_pw), database(_database)
	{
	}
private:
	string host = "";
	string user = "";
	string pw = "";
	string database = "";
	string rwType = "";

	int32_t connTimeoutSec = 10;
	int32_t readTimeoutSec = 3;
	int32_t writeTimeoutSec = 3;
};

class DBConnKey 
{
public:
	DBConnKey() : dbKey(0, 0, 0){
		
	}
	DBConnKey(uint8_t _tagNo, uint8_t _dbNameType, uint16_t _rwType) : dbKey(_tagNo, _dbNameType, _rwType) {
	}
private:
	tuple<uint8_t, uint8_t, uint16_t> dbKey;
public:
	uint32_t GetKey() const {
		return std::get<0>(dbKey) << 16 | std::get<1>(dbKey) << 8 | std::get<2>(dbKey);
	}

	uint8_t GetTagNo() const {
		return std::get<0>(dbKey);
	}

	uint8_t GetDbNameType() const {
		return std::get<1>(dbKey);
	}
	uint16_t GetRWType() const {
		return std::get<2>(dbKey);
	}
};

struct DBConnHasher
{
public:
	uint32_t operator() (const DBConnKey& _key) const {
		return _key.GetKey();
	}
};
