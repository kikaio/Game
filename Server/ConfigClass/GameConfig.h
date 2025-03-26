#pragma once

class GameConfig
{
public:
private:
	uint16_t listenPort = 0;
	int32_t acceptCnt = 1;
	int32_t backLog = 100;
	string name;
	int32_t no;
public:
	const uint16_t ListenPort();
	const int32_t AcceptCnt();
	const int32_t BackLog();
	const string& Name();
	const int32_t No();
public:
	bool ReadFromJson(const rapidjson::Value& _val);
public:
	void Render();
};