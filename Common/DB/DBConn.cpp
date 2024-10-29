#include "pch.h"
#include "DBConn.h"

DBConn::DBConn(const DBProfile& _profile, uint8_t _tagNo)
	: profile(_profile) 
{
}

bool DBConn::TryConn()
{
	try{
		sql::Driver* driver = DBManager::Get().Driver();
		conn = driver->connect(profile.host, profile.user, profile.pw);
	}
	catch(sql::SQLException e) {
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
		// todo : impl logic
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

