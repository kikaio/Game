#pragma once

class GameConfig {
private:
	string host = "";
	int16_t port = 0;
	int32_t iocpThreadCnt = 0;
public:
	const string& Host();
	int16_t Port();
	int32_t IocpThreadCnt();
public:
	void Init(const rapidjson::Value& _val);
};