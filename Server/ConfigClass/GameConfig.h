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
	const uint16_t ListenPort() { return listenPort; }
	const int32_t AcceptCnt() { return acceptCnt; }
	const int32_t BackLog() { return backLog; }
	const string& Name() { return name; }
	const int32_t No() { return no; }
public:
	bool ReadFromJson(const rapidjson::Value& _val) {

		//for(auto _iter = _val.MemberBegin(); _iter != _val.MemberEnd(); _iter++) {
		//	printf("name : %s, val : %d\n", _iter->name.GetString(), _iter->value.GetInt());
		//}

		ASSERT_CRASH(_val.HasMember("no"));
		ASSERT_CRASH(_val.HasMember("name"));
		ASSERT_CRASH(_val.HasMember("listen_port"));
		ASSERT_CRASH(_val.HasMember("accept_cnt"));
		ASSERT_CRASH(_val.HasMember("back_log"));
		no = _val["no"].GetInt();
		name = _val["name"].GetString();
		listenPort = _val["listen_port"].GetInt();
		acceptCnt = _val["accept_cnt"].GetInt();
		backLog = _val["back_log"].GetInt();

		return true;
	}
public:
	void Render() {
		printf("========== game server ==========\n");
		printf("no : %d\n", no);
		printf("name : %s\n", name.c_str());
		printf("listen port : %d\n", listenPort);
		printf("acceptCnt : %d\n", acceptCnt);
		printf("backLog : %d\n", backLog);
	}
};