#include "pch.h"
#include "MasterConfig.h"

void MasterConfig::Init(rapidjson::Value& _val) {
	ASSERT_CRASH(_val.HasMember("host"));
	string _host = _val["host"].GetString();
	int pivot = _host.find(':');
	if (pivot == string::npos) {
		hostStr = _host;
	}
	else {
		hostStr = _host.substr(0, pivot);
		port = std::atoi(_host.substr(pivot + 1).c_str());
	}
}

void MasterConfig::Render() {
	MS_DEBUG_LOG("[master config]=======");
	MS_DEBUG_LOG("host : {}:{}", hostStr, port);
}