#pragma once
//#include <mysqlx/xdevapi.h>

#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>

class DBManager : public Singleton<DBManager>
{
public:
	void Test();
};