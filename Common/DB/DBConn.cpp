#include "pch.h"
#include "DBConn.h"


DBConn::DBConn() 
{
}

DBConn::DBConn(const DBProfile& _profile, uint8_t _tagNo)
 : profile(_profile)
{
}

bool DBConn::CheckConnect()
{
	try {
		// todo : impl logic
		if (conn == nullptr) {
			//todo : logging
			connectTryCnt++;
			sql::ConnectOptionsMap optMap;
			optMap["hostName"] = profile.Host();
			optMap["userName"] = profile.User();
			optMap["password"] = profile.Pw();
			optMap["schema"] = profile.Database();
			optMap["OPT_CONNECT_TIMEOUT"] = profile.ConnectTimeoutSec();
			optMap["OPT_READ_TIMEOUT"] = profile.ReadTimeoutSec();
			optMap["OPT_WRITE_TIMEOUT"] = profile.WriteTimeout();
			optMap["OPT_SSL_MODE"] = sql::SSL_MODE_DISABLED;

			conn = DBManager::Get().Driver()->connect(optMap);
			if(conn == nullptr) {
				return false;
			}
			conn->setTransactionIsolation(sql::TRANSACTION_READ_COMMITTED);
			conn->setSchema(profile.Database());
			connected = true;

			printf("connect success. connect try cont : %d\n", connectTryCnt);
		}
		else if(conn->isValid() == false || conn->isClosed()) {
			Close();
			return CheckConnect();
		}
	}
	catch (sql::SQLException e) {
	}
	return false;
}

void DBConn::KeepAlive()
{
	CheckConnect();
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

