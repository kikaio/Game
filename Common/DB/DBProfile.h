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

class DBProfile
{
public:
	static DBProfile dummyProfile;
public:
	DBProfile() {
	}
	DBProfile(string _host, int32_t _port, string _user, string _pw, string _database, int32_t _connTimeOut = 10, int32_t _readTimeOut = 3, int32_t _writeTimeOut = 3) 
		: host(_host), port(_port), user(_user), pw(_pw), database(_database)
		, connTimeoutSec(_connTimeOut), readTimeoutSec(_readTimeOut), writeTimeoutSec(_writeTimeOut)
	{
	}
private:
	string host = "";
	string user = "";
	string pw = "";
	string database = "";
	string rwType = "";
	int32_t port = 0;
public:
	int32_t connTimeoutSec = 10;
	int32_t readTimeoutSec = 3;
	int32_t writeTimeoutSec = 3;
public:
	string Host() const {
		return host;
	}
	string User() const{
		return user;
	}
	string Pw() const {
		return pw;
	}
	string Database() const {
		return database;
	}
	int32_t Port() const {
		return port;
	}
};
