#pragma once
//#include <mysqlx/xdevapi.h>


class DBProfile
{
public:
	static DBProfile dummyProfile;
public:
	DBProfile() {
	}
	DBProfile(string _host, int32_t _port, string _user, string _pw, string _database, int32_t _connTimeOut = 10, int32_t _readTimeOut = 3, int32_t _writeTimeOut = 3) 
		: host(_host), port(_port), user(_user), pw(_pw), database(_database)
		, connTimeoutSec(_connTimeOut), readTimeoutSec(_readTimeOut), writeTimeoutSec(_writeTimeOut)
	{
	}
private:
	string host = "";
	string user = "";
	string pw = "";
	string database = "";
	string rwType = "";
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
		if(rwType == "r" || rwType == "read") {
			return RWType::READ;
		}
		if(rwType == "w" || rwType == "write") {
			return RWType::WRITE;
		}
		if(rwType == "rw" || rwType == "wr") {
			return RWType::READ_WRITE;
		}
		return RWType::NONE;;
	}

	int8_t RwTypeVal() {
		auto ret = magic_enum::enum_integer(RwType());
		return ret;
	}
};


class DBPoolKey
{
public:
	DBPoolKey(uint8_t _dbType, uint8_t _rwType);
private:
	uint8_t dbType = 0;
	uint8_t rwType = 0;
public:
	uint16_t GetKey() {
		return dbType<<8 | rwType;
	}
};