#include "pch.h"
#include "DBConn.h"
#include "DBConnPool.h"

DBConn DBConnPool::defDBConn = DBConn();

void DBConnPool::ReadyConnections(uint32_t _poolCnt)
{
	for(int32_t idx = 0; idx < _poolCnt; idx++) {
		connections.emplace_back(dbProfile, idx);
	}
}

DBConn& DBConnPool::GetConnect(bool _isRand)
{

	if(connections.empty()) {
		return defDBConn;
	}
	//random 방식이 아닌 경우 roundRobin 방식으로 반환한다.
	if(_isRand == false) {
		curIdx %= connections.size();
		return connections[curIdx++];
	}
	else {
		curIdx %= connections.size();
		return connections[curIdx++];
	}
	
}

const DBProfile& DBConnPool::Profile()
{
	return dbProfile;
}
