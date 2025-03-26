#pragma once

class MasterConfig {
private:
	string hostStr = "";
	int16_t port = 0;
public:
	const string& Host();
	uint16_t Port();
public:
	void Init(rapidjson::Value& _val);
public:
	void Render();
};