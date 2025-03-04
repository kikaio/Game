#include "pch.h"
#include "RedisConnPool.h"

bool RedisConnPool::Add(const RedisConfig& _conf) {
	
	RedisName _name = _conf.redisName;
	string _host = _conf.hostStr;
	int16_t _port = _conf.port;
	string _pw = _conf.pw;
	int32_t _dbNo = _conf.dbNo;
	int32_t _poolCnt = _conf.poolCnt;

	sw::redis::ConnectionOptions connOpt;
	connOpt.host = _host;
	connOpt.port = _port;
	if (_pw != "") {
		connOpt.password = _pw;
	}
	connOpt.db = _dbNo;

	sw::redis::ConnectionPoolOptions poolOpt;
	poolOpt.size = _poolCnt;

	switch (_name) {
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
