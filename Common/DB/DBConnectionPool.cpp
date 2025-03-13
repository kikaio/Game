#include "pch.h"
#include "DBConnectionPool.h"

DBConnectionPool::DBConnectionPool()
{
}

DBConnectionPool::~DBConnectionPool()
{
	Clear();
}
bool DBConnectionPool::Connect(const DBConfig& _conf) {
	int32_t _connCnt = _conf.poolCnt;
	string _odbcName = _conf.odbcName;
	string _host = _conf.hostStr;
	string _user = _conf.userStr;
	string _pwd = _conf.pwStr;
	DBNameType _dbNameType = _conf.dbNameType;
	RWType _rwType = _conf.rwType;

	switch(_dbNameType) {
	case DBNameType::GameDB:{
		gameDBConfMap[_rwType] = _conf;
		break;
	}
	case DBNameType::CommonDB: {
		commonDBConfMap[_rwType] = _conf;
		break;
	}
	}

	LOCK_GUARDDING(dbPoolLock);
	SQLRETURN sqlRet = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env);
	if (sqlRet != SQL_SUCCESS && sqlRet != SQL_SUCCESS_WITH_INFO) {
		printf("SQL Return : %d\n", sqlRet);
		return false;
	}

	sqlRet = SQLSetEnvAttr(env, SQL_ATTR_ODBC_VERSION, reinterpret_cast<SQLPOINTER>(SQL_OV_ODBC3), 0);
	if (sqlRet != SQL_SUCCESS && sqlRet != SQL_SUCCESS_WITH_INFO) {
		printf("SQL Return : %d\n", sqlRet);
		return false;
	}

	for (int32_t idx = 0; idx < _connCnt; idx++) {
		DBConnection* _conn = new DBConnection();
		if (_conn->Connect(env, _odbcName, _host, _user, _pwd, _dbNameType, _rwType) == false) {
			return false;
		}

		switch (_conn->DbNameType()) {
		case DBNameType::CommonDB: {
			commonDBConfMap[_rwType].curPoolCnt++;
			auto ret = commonDBConnMap.emplace(_rwType, vector<DBConnection*>());
			(ret.first)->second.push_back(_conn);
			break;
		}
		case DBNameType::GameDB: {
			gameDBConfMap[_rwType].curPoolCnt++;
			auto ret = gameDBConnMap.emplace(_rwType, vector<DBConnection*>());
			(ret.first)->second.push_back(_conn);
			break;
		}
		}
	}

	return true;
}

void DBConnectionPool::Clear()
{
	if (isCleared.exchange(true) == true) {
		return ;	
	}
	LOCK_GUARDDING(dbPoolLock);
	if(env != SQL_NULL_HANDLE) {

		SQLFreeHandle(SQL_HANDLE_ENV, env);
		env = SQL_NULL_HANDLE;
		
	}

	for(auto _dbConn : connections) {
		delete(_dbConn);
	}

	connections.clear();
}

shared_ptr<DBConnection> DBConnectionPool::PopCommonDB(RWType _rwType) {
	
	auto start = std::chrono::steady_clock::now();
	int32_t timeoutMsec = 100;

	auto iterConf = commonDBConfMap.find(_rwType);
	ASSERT_CRASH(iterConf != commonDBConfMap.end());
	const DBConfig& _conf = iterConf->second;
	
	ASSERT_CRASH(commonDBConnMap.empty() == false);

	while(true) {
		LOCK_GUARDDING(dbPoolLock);

		auto iter = commonDBConnMap.find(_rwType);
		ASSERT_CRASH(iter != commonDBConnMap.end());
		
		//생성 안하고 반환된 conn을 기다려야 할 때.
		if(iter->second.empty() && _conf.curPoolCnt == _conf.maxPoolCnt) {
			auto deltaMsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
			if(deltaMsec > timeoutMsec) {
				return nullptr;
			}
			this_thread::sleep_for(10ms);
			continue;
		}
		if(iter->second.empty()) {
			//신규 conn 생성
			DBConnection* _conn = new DBConnection();
			ASSERT_CRASH(_conn->Connect(env, _conf.odbcName, _conf.hostStr, _conf.userStr, _conf.pwStr, _conf.dbNameType, _conf.rwType));
			
			commonDBConfMap[_rwType].curPoolCnt++;
			shared_ptr<DBConnection> _connSptr{ _conn, DBConnectionPool::ReleaseConn };
			return _connSptr;
		}
		else {
			auto conn = iter->second.back();
			iter->second.pop_back();
			shared_ptr<DBConnection> _connSptr{ conn, DBConnectionPool::ReleaseConn };
			_connSptr->Unbind();
			return _connSptr;
		}
	}
	return nullptr;
}

shared_ptr<DBConnection> DBConnectionPool::PopGameDB(RWType _rwType) {

	auto start = std::chrono::steady_clock::now();
	int32_t timeoutMsec = 100;

	auto iterConf = gameDBConfMap.find(_rwType);
	ASSERT_CRASH(iterConf != gameDBConfMap.end());
	const DBConfig& _conf = iterConf->second;

	ASSERT_CRASH(gameDBConnMap.empty() == false);

	while (true) {
		LOCK_GUARDDING(dbPoolLock);

		auto iter = gameDBConnMap.find(_rwType);
		ASSERT_CRASH(iter != gameDBConnMap.end());

		//생성 안하고 반환된 conn을 기다려야 할 때.
		if (iter->second.empty() && _conf.curPoolCnt == _conf.maxPoolCnt) {
			auto deltaMsec = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - start).count();
			if (deltaMsec > timeoutMsec) {
				//timeout 시 nullptr 반환
				return nullptr;
			}
			this_thread::sleep_for(10ms);
			continue;
		}
		if (iter->second.empty()) {
			//신규 conn 생성
			DBConnection* _conn = new DBConnection();
			ASSERT_CRASH(_conn->Connect(env, _conf.odbcName, _conf.hostStr, _conf.userStr, _conf.pwStr, _conf.dbNameType, _conf.rwType));

			commonDBConfMap[_rwType].curPoolCnt++;
			shared_ptr<DBConnection> _connSptr{ _conn, DBConnectionPool::ReleaseConn };
			return _connSptr;
		}
		else {
			auto conn = iter->second.back();
			iter->second.pop_back();
			shared_ptr<DBConnection> _connSptr{ conn, DBConnectionPool::ReleaseConn };
			return _connSptr;
		}
	}
	return nullptr;
}

void DBConnectionPool::Push(DBConnection* _conn)
{
	LOCK_GUARDDING(dbPoolLock);
	switch (_conn->DbNameType()) {
	case DBNameType::CommonDB: {
		auto iter = commonDBConnMap.emplace(_conn->RwType(), vector<DBConnection*>());
		iter.first->second.push_back(_conn);
		break;
	}
	case DBNameType::GameDB: {
		auto iter = gameDBConnMap.emplace(_conn->RwType(), vector<DBConnection*>());
		iter.first->second.push_back(_conn);
		break;
	}
	default: {
		//todo : error logging
		break;
	}
	}
}

void DBConnectionPool::ReleaseConn(DBConnection* _conn) {
	Get().Push(_conn);
	return ;
}