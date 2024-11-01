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


class DBConn
{
public:
	DBConn();
	DBConn(const DBProfile& _profile, uint8_t _tagNo = 0);

private:
	sql::Connection* conn = nullptr;
	DBProfile profile;
	bool connected = false;
	int32_t connectTryCnt = 0;
public:
	sql::Connection* GetConn() {
		return conn;
	}
	bool Connected() {
		return connected;
	}
public:
	bool CheckConnect();
	void KeepAlive();
	void Close();
};