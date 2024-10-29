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

enum class DBNameType : uint8_t {
	NONE = 0
	, DB_COMMON = 1
	, DB_GAME = 2
};

enum class DBRWType : uint16_t {
	NONE = 0
	, READ = 1
	, WRITE = 1 << 1
	, READ_AND_WRITE = READ | WRITE
};


class DBConn
{
public:
	DBConn(const DBProfile& _profile, uint8_t _tagNo = 0);
	DBConn(const DBConn& _other) = delete;
	DBConn(DBConn&& _other) = delete;
private:
	const DBProfile& profile;
private:
	sql::Connection* conn = nullptr;
	DBConnKey connKey;
public:
	sql::Connection* GetConn() {
		return conn;
	}
	void SetConnKey(const DBConnKey& _other) {
		connKey = _other;
	}
	DBConnKey GetConnKey() {
		return connKey;
	}
public:
	bool TryConn();
	void KeepAlive();
	void Close();
};