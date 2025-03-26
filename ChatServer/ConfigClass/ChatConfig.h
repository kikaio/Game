#pragma once

class ChatConfig {
private:
	uint16_t listenPort = 0;
	int32_t acceptCnt = 1;
	int32_t backLog = 100;
	string name = "defName";
	int32_t no = 0;
public:
	uint16_t ListenPort();
	int32_t AcceptCnt();
	int32_t BackLog();
	const string& Name();
	int32_t No();
public:
	void Init(rapidjson::Value& _val);
public:
	void Render();
};