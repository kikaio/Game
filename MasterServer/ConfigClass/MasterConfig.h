#pragma once

class MasterConfig
{
public:
private:
	uint16_t gameListenPort = 0;
	int32_t gameAcceptCnt = 1;
	int32_t gameBackLog = 100;

	uint16_t chatListenPort = 0;
	int32_t chatAcceptCnt = 1;
	int32_t chatBackLog = 100;



public:
	const uint16_t GameListenPort() { return gameListenPort; }
	const int32_t GameAcceptCnt() { return gameAcceptCnt; }
	const int32_t GameBackLog() { return gameBackLog; }

	const uint16_t ChatListenPort() { return chatListenPort; }
	const int32_t ChatAcceptCnt() { return chatAcceptCnt; }
	const int32_t ChatBackLog() { return chatBackLog; }


public:
	bool ReadFromJson(const rapidjson::Value& _val) {

		for(auto _iter = _val.MemberBegin(); _iter != _val.MemberEnd(); _iter++) {
			printf("name : %s, val : %d\n", _iter->name.GetString(), _iter->value.GetInt());
		}

		ASSERT_CRASH(_val.HasMember("game_listen_port"));
		ASSERT_CRASH(_val.HasMember("game_accept_cnt"));
		ASSERT_CRASH(_val.HasMember("game_back_log"));
		gameListenPort = _val["game_listen_port"].GetInt();
		gameAcceptCnt = _val["game_accept_cnt"].GetInt();
		gameBackLog = _val["game_back_log"].GetInt();

		ASSERT_CRASH(_val.HasMember("chat_listen_port"));
		ASSERT_CRASH(_val.HasMember("chat_accept_cnt"));
		ASSERT_CRASH(_val.HasMember("chat_back_log"));
		chatListenPort = _val["chat_listen_port"].GetInt();
		chatAcceptCnt = _val["chat_accept_cnt"].GetInt();
		chatBackLog = _val["chat_back_log"].GetInt();

		return true;
	}
public:
	void Render() {
		printf("game listen port : %d\n", gameListenPort);
		printf("game acceptCnt : %d\n", gameAcceptCnt);
		printf("game backLog : %d\n", gameBackLog);

		printf("chat listen port : %d\n", chatListenPort);
		printf("chat acceptCnt : %d\n", chatAcceptCnt);
		printf("chat backLog : %d\n", chatBackLog);
	}
};