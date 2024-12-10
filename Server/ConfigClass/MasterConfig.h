#pragma once

class MasterConfig
{
public:
	MasterConfig() {}
	MasterConfig(const MasterConfig& _other) = delete;
public:
	string hostStr = "NONE";
	int32_t port = 0;
public:
	void Init(rapidjson::Value& _doc);
	void Render();
};
