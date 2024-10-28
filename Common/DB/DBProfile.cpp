#include "pch.h"
#include "DBProfile.h"

bool DBConn::DoConn()
{
	try{
		sql::Driver* driver = nullptr;
		sql::Connection* conn = nullptr;
		sql::Statement* statement = nullptr;
		sql::ResultSet* resultSet = nullptr;
		sql::PreparedStatement* preparedState = nullptr;
		sql::ResultSetMetaData* resultSetMeta = nullptr;

		driver = sql::mysql::get_mysql_driver_instance();
		conn = driver->connect(profile.host, profile.user, profile.pw);
		conn->setSchema(profile.database);
		statement = conn->createStatement();
		statement->execute("set names utf-8");
	}
	catch(exception e) {
		
		return false;
	}
	return true;
}

void DBConn::KeepAlive()
{
	if(conn == nullptr) {
		//todo : logging
		printf("db keepAlive failed. conn[%d] is nullptr", connKey.GetDbNameType());
		return ;
	}

	try {
		DBLink link(*this);
	} catch(sql::SQLException e) {
	}
}

void DBConn::Close()
{
	if(conn != nullptr) {
		conn->close();
		delete conn;
	}
	conn = nullptr;
	return ;
}

