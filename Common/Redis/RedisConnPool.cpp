#include "pch.h"
#include "RedisConnPool.h"

bool RedisConnPool::Add(RedisName _name, string _host, int16_t _port, string _pw
	, int32_t _dbNo, int32_t _poolCnt)
{
	sw::redis::ConnectionOptions connOpt;
	connOpt.host = _host;
	connOpt.port = _port;
	if(_pw != "") {
		connOpt.password = _pw;
	}
	connOpt.db = _dbNo;

	sw::redis::ConnectionPoolOptions poolOpt;
	poolOpt.size = _poolCnt;

	switch(_name) {
	case RedisName::Common: {
		commonConn = make_shared<RedisConn>(connOpt, poolOpt);
		break;
	}
	case RedisName::Session: {
		sessionConn = make_shared<RedisConn>(connOpt, poolOpt);
		break;
	}
	default: {
		//todo : error logging
		return false;
	}
	}
	return true;
}

std::shared_ptr<RedisConn> RedisConnPool::GetCommonConn()
{
	return commonConn;
}

std::shared_ptr<RedisConn> RedisConnPool::GetSessionConn()
{
	return sessionConn;
}
