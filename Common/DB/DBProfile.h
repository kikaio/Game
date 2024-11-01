#pragma once
//#include <mysqlx/xdevapi.h>


class DBProfile
{
public:
	static DBProfile dummyProfile;
public:
	DBProfile() {
	}
	DBProfile(string _host, int32_t _port, string _user, string _pw, string _database
	, string _rwType
	, int32_t _connTimeOut = 10, int32_t _readTimeOut = 3, int32_t _writeTimeOut = 3
	) 
		: host(_host), port(_port), user(_user), pw(_pw), database(_database), rwTypeStr(_rwType)
		, connTimeoutSec(_connTimeOut), readTimeoutSec(_readTimeOut), writeTimeoutSec(_writeTimeOut)
	{
	}
	DBProfile(const DBProfile& _other)
		: host(_other.host), port(_other.port), user(_other.user), pw(_other.pw), database(_other.database)
		, connTimeoutSec(_other.connTimeoutSec)
		, readTimeoutSec(_other.readTimeoutSec)
		, writeTimeoutSec(_other.writeTimeoutSec)
	{
	}
private:
	string host = "";
	string user = "";
	string pw = "";
	string database = "";
	string rwTypeStr = "";
	int32_t port = 0;
private:
	int32_t connTimeoutSec = 10;
	int32_t readTimeoutSec = 3;
	int32_t writeTimeoutSec = 3;
public:
	string Host() const {
		return host;
	}
	string User() const{
		return user;
	}
	string Pw() const {
		return pw;
	}
	string Database() const {
		return database;
	}
	int32_t Port() const {
		return port;
	}
	RWType RwType() const {
		if(rwTypeStr == "r" || rwTypeStr == "read") {
			return RWType::READ;
		}
		if(rwTypeStr == "w" || rwTypeStr == "write") {
			return RWType::WRITE;
		}
		if(rwTypeStr == "rw" || rwTypeStr == "wr") {
			return RWType::READ_WRITE;
		}
		return RWType::NONE;;
	}

	uint8_t RwTypeVal() {
		auto ret = ENUM_TO_INT(RwType());
		return ret;
	}

	int32_t ConnectTimeoutSec() {
		return connTimeoutSec;
	}
	int32_t ReadTimeoutSec() {
		return readTimeoutSec;
	}
	int32_t WriteTimeout() {
		return writeTimeoutSec;
	}
};


class DBPoolKey
{
public:
	DBPoolKey(uint16_t _val) {
		dbNameVal = _val>>8;
		rwType = 0x00FF & _val;
	}
	DBPoolKey(uint8_t _dbNameVal, uint8_t _rwType) 
		: dbNameVal(_dbNameVal), rwType(_rwType)
	{
	}
private:
	uint8_t dbNameVal = 0;
	uint8_t rwType = 0;
public:
	uint16_t GetKey() const {
		return dbNameVal <<8 | rwType;
	}
};