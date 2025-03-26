#pragma once

class ChatConfig
{
public:
	ChatConfig() {}
	ChatConfig(const MasterConfig& _other) = delete;
public:
	string hostStr = "NONE";
	uint16_t port = 0;
public:
	void Init(rapidjson::Value& _doc);
	void Render();
};
