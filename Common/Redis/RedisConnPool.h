#pragma once

class RedisConnPool : public Singleton<RedisConnPool>{
private:
private:
	std::shared_ptr<RedisConn> commonConn;
	std::shared_ptr<RedisConn> sessionConn;
public:
	bool Add(RedisName _name, string _host, int16_t _port, string _pw
		, int32_t _dbNo, int32_t _poolCnt
	);
public:
	std::shared_ptr<RedisConn> GetCommonConn();
	std::shared_ptr<RedisConn> GetSessionConn();
};