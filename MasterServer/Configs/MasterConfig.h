#pragma once

class MasterConfig
{
public:
	MasterConfig() {}
private:
	uint16_t listenPort = 0;
	int32_t acceptCnt = 1;
	int32_t backLog = 100;
public:
	const uint16_t ListenPort() { return listenPort; }
	const int32_t AcceptCnt() { return acceptCnt; }
	const int32_t BackLog() { return backLog; }
public:
	bool ReadFromJson(const rapidjson::Value& _val) {
		for(auto _iter = _val.MemberBegin(); _iter != _val.MemberEnd(); _iter++) {
			printf("name : %s, val : %d\n", _iter->name.GetString(), _iter->value.GetInt());
		}
		return true;
	}
public:
	void Render() {
		printf("listen port : %d\n", listenPort);
		printf("acceptCnt : %d\n", acceptCnt);
		printf("backLog : %d\n", backLog);
	}
};