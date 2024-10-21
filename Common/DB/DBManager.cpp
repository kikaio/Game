#include "pch.h"
#include "DBManager.h"

void DBManager::Test()
{
	mysqlx::Session session(mysqlx::SessionOption::HOST, "localhost"
		, mysqlx::SessionOption::PORT, 33306
		, mysqlx::SessionOption::USER, "gameuser"
		, mysqlx::SessionOption::PWD, "gameuser"
	);

	mysqlx::Schema myDb = session.getSchema("testDB");
	mysqlx::Table mytable = myDb.getTable("testTable");
}
