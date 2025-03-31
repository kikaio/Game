#pragma once

class DummyUser : public JobQueue
{
#pragma region dummy 자체정보
private:
	int32_t dummyIdx = 0;
	bool dummyUserRecycle = false; //dummy user를 계속 재활용할지 여부.
public:
	void SetDummyUserIdx(int32_t _idx) {
		dummyIdx = _idx;
	}
	int32_t GetDummyIdx() {
		return dummyIdx;
	}
public:
	DummyUserSptr GetSptr();
	void ClearUser();
#pragma endregion

#pragma region test scenario 관련
private:
	int32_t dumActIdx = 0;
	bool isLoopTest = false;
	vector<DumActSptr> dumActs;
public:
	void SetTestScenario(const std::vector<DumActSptr>& _dumActs, bool _isLoopTest = false);
	void DoDumAct();
#pragma endregion

#pragma region network 관련
public:
	NetworkCoreSptr gameServerNetCore = nullptr;
	ProtocolCallbackMap gameServerProtoCallback; //game server 용 protocol callback 담당.
	tuple<int, int> waitingGamePacket = std::make_tuple(0, 0);
	const tuple<int, int> noneWaitingPacket = std::make_tuple(0, 0);
private:
	GameServerSessionSptr gameServerSession = nullptr;
public:
	bool IsConnected();
	void SetGameServerSession(GameServerSessionSptr _dummySession);
	GameServerSessionSptr GetGameServerSession() {
		return gameServerSession;
	}
public:
	void OnGameServerSessionDisconnected();
	void OnGameServerSessionConnected();
private:
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void ReserveGameServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto, DUM_PROTOCOL_CB&& _cb) {
		gameServerProtoCallback.ReserveCallback(_msg, _proto, std::move(_cb));
	}
public:
	
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void SetWaitGamePacket(MSG_TYPE _msg, PROTO_TYPE _proto) {
		waitingGamePacket = std::make_tuple((int32_t)_msg, (int32_t)_proto);
	}

	template<typename MSG_TYPE, typename PROTO_TYPE>
	bool CheckAndClearWaitGamePacket(MSG_TYPE _msg, PROTO_TYPE _proto) {
		if (waitingGamePacket == std::make_tuple((int32_t)_msg, (int32_t)_proto)) { 
			waitingGamePacket = noneWaitingPacket;
			return true;
		}
		return false;
	}
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void SetWaitGamePacket(MSG_TYPE _msg, PROTO_TYPE _proto, DUM_PROTOCOL_CB&& _cb) {
		waitingGamePacket = std::make_tuple((int32_t)_msg, (int32_t)_proto);
		ReserveGameServerProtocol(_msg, _proto, std::move(_cb));
	}
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void RecvGameServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto) {
		if(waitingGamePacket == std::make_tuple((int32_t)_msg, (int32_t)_proto)) {
			gameServerProtoCallback.RecvProtocol(_msg, _proto);
			waitingGamePacket = noneWaitingPacket;
		}
	}

#pragma endregion 

#pragma region chat server network 관련
public:
	NetworkCoreSptr chatServerNetCore = nullptr;
	ProtocolCallbackMap chatServerProtoCallback; //game server 용 protocol callback 담당.
	tuple<int, int> waitingChatPacket = std::make_tuple(0, 0);
private:
	ChatServerSessionSptr chatServerSession = nullptr;
	string chatHost = "";
	int32_t chatPort = 0;
	vector<ChatProfileSptr> otherUserChatProfiles;
	int32_t curChatRoomNo = 0;
public:
	void SetChatServerInfo(const string& _host, int16_t _port);
	void SetChatServerSession(ChatServerSessionSptr _session) {
		chatServerSession = _session;
	}
	ChatServerSessionSptr GetChatServerSession() {
		return chatServerSession;
	}
	vector<ChatProfileSptr>& GetOtherUserChatProfiles();
	int32_t GetCurChatRoomNo();
	void SetCurChatRoomNo(int32_t _no);
public:
	bool IsChatConnected();
public:
	void OnChatServerSessionDisconnected();
	void OnChatServerSessionConnected();
private:
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void ReserveChatServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto, DUM_PROTOCOL_CB&& _cb) {
		chatServerProtoCallback.ReserveCallback(_msg, _proto, std::move(_cb));
	}
public:
	template<typename MSG_TYPE, typename PROTO_TYPE>
	bool CheckAndClearWaitChatPacket(MSG_TYPE _msg, PROTO_TYPE _proto) {
		if (waitingChatPacket == std::make_tuple((int32_t)_msg, (int32_t)_proto)) {
			waitingChatPacket = noneWaitingPacket;
			return true;
		}
		return false;
	}
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void SetWaitChatPacket(MSG_TYPE _msg, PROTO_TYPE _proto, DUM_PROTOCOL_CB&& _cb) {
		waitingChatPacket = std::make_tuple((int32_t)_msg, (int32_t)_proto);
		ReserveChatServerProtocol(_msg, _proto, std::move(_cb));
	}
	template<typename MSG_TYPE, typename PROTO_TYPE>
	void RecvChatServerProtocol(MSG_TYPE _msg, PROTO_TYPE _proto) {
		if(waitingChatPacket == std::make_tuple((int32_t)_msg, (int32_t)_proto)) {
			chatServerProtoCallback.RecvProtocol(_msg, _proto);
			waitingChatPacket = noneWaitingPacket;
		}
	}
#pragma endregion 


private:
	DummyProfile profile;
	Inventory inventory;
	LoginData loginData;
	LoginResultData loginResultData;
	ChatProfileSptr chatProfile;
public:
	void SetLoginData(const LoginData& _loginData);
	const LoginData& GetLoginData();

	void SetChatProfile(ChatProfileSptr _chatProfile);
	ChatProfileSptr GetChatProfile();

	void SetProfile(const DummyProfile& _profile);
	DummyProfile& GetProfile();
	
	void SetInventory(const Inventory& _inven);
	Inventory& GetInventory();

	void SetLoginResultData(const LoginResultData& _data);
	LoginResultData& GetLoginResultData();

public:
	void Render();
};