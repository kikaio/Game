#pragma once

class RedisConn {
private:
	RedisName name;
	sw::redis::Redis conn;
public:
	RedisConn(string _hostStr) : conn(_hostStr) {
	}
	RedisConn(sw::redis::ConnectionOptions _connOpt, sw::redis::ConnectionPoolOptions _poolOpt) : conn(_connOpt, _poolOpt) {
	}
public:
	void set(const char* _key, const char* _val) {
		conn.set(_key, _val);
	}
	void set(const char* _key, string _val) {
		conn.set(_key, _val.c_str());
	}

	bool get(const char* _key, OUT string& _outVal) {
		auto val = conn.get(_key);
		if (val) {
			_outVal = val->c_str();
		}
		return val.has_value();
	}

	void setList(const char* _key, vector<string> _vect) {
		conn.rpush(_key, _vect.begin(), _vect.end());
		return;
	}

	void getList(const char* _key, OUT vector<string>& _outVect, int _start = 0, int _end = -1) {
		_outVect.clear();
		conn.lrange(_key, _start, _end, std::back_inserter(_outVect));
		return;
	}

	void setMap(const char* _key, map<string, string> _map) {
		conn.hmset(_key, _map.begin(), _map.end());
	}

	void getMap(const char* _key, OUT map<string, string>& _outMap) {
		conn.hgetall(_key, std::inserter(_outMap, _outMap.begin()));
	}
};