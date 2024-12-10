#include "pch.h"
#include "GameConfig.h"

void MasterConfig::Init(rapidjson::Value& _doc) {
	ASSERT_CRASH(_doc.HasMember("host"));
	string _host = _doc["host"].GetString();
	int pivot = _host.find(':');
	if (pivot == string::npos) {
		//todo : domain 일 때 처리
	}
	else {
		hostStr = _host.substr(0, pivot);
		port = std::atoi(_host.substr(pivot + 1).c_str());
	}
}

void MasterConfig::Render() {
	printf("======master config======\n");
	printf("host : %s:%d\n", hostStr.c_str(), port);
}
