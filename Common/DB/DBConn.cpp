#include "pch.h"
#include "DBConn.h"


DBConn::DBConn() 
{
}

DBConn::DBConn(const DBProfile& _profile, uint8_t _tagNo)
{
}

void DBConn::KeepAlive()
{
	if(conn == nullptr) {
		//todo : logging
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

