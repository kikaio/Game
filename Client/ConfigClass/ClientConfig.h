#pragma once

class ClientConfig {
private:
	int32_t dummyCnt = 0;
	int32_t workerThreadCnt = 0;
	string loggerLv = "DEBUG";
public:
	int32_t DummyCnt();
	const string& LoggerLv();
	int32_t WorkerThreadCnt();
public:
	void Init(const rapidjson::Value& _val);
	void Render();
};