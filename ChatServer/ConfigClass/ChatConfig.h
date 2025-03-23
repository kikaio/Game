#pragma once

class ChatConfig {
private:
	uint16_t listenPort = 0;
	int32_t acceptCnt = 1;
	int32_t backLog = 100;
	string name;
	int32_t no;
public:
	void Init(rapidjson::Value& _val);
public:
	void Render();
};