// ChatServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"


static MasterConfig masterConfig;
static ChatConfig chatConfig;

void Init();

void StartMasterThread();
void StartChatThread();


int main()
{
	Init();

	ThreadManager::Get().PushThread(StartMasterThread
		, "for master server"
		, "thread about with master server"
	);

	ThreadManager::Get().PushThread(StartChatThread
		, "for chat server role"
		, "thread about with chat server"
	);

	ThreadManager::Get().StartAll();

	ThreadManager::Get().JoinAll();
	ThreadManager::Get().Clear();

	CS_DEBUG_LOG("chat server fin");
	return 0;
}
void Init() {
	const string logFolderPath = "logs";
	LogHelper::Init(logFolderPath, "debug");

	JsonReader jr;
	string configFilePath = "./configs/ServerConfig.json";
	jr.ReadFile(configFilePath.c_str());

	rapidjson::Value dbValues(rapidjson::kArrayType);
	jr.GetArray("db_configs", dbValues);
	for(auto _iter = dbValues.Begin(); _iter != dbValues.End(); ++_iter) {
		DBConfig dbConf;
		dbConf.Init(*_iter);
		ASSERT_CRASH(DBConnectionPool::Get().Connect(dbConf));
	}


	rapidjson::Value masterValue(rapidjson::kObjectType);
	jr.GetObjectW("master", masterValue);
	masterConfig.Init(masterValue);
	masterConfig.Render();
		
	rapidjson::Value chatValue(rapidjson::kObjectType);
	jr.GetObjectW("chat", chatValue);
	chatConfig.Init(chatValue);
	chatConfig.Render();


	rapidjson::Value mongoDBValue(rapidjson::kObjectType);
	jr.GetObjectW("mongo_db", mongoDBValue);

	rapidjson::Value redisDBValues(rapidjson::kArrayType);
	jr.GetObjectW("redis", redisDBValues);
	for(auto _iter = redisDBValues.Begin(); _iter != redisDBValues.End(); _iter++) {
		const auto& _val = *_iter;
		//todo : init for redis
	}

}

void StartMasterThread() {

	NetworkCoreSptr masterNet = MakeShared<NetworkCore>();
	this_thread::sleep_for(3s);
	const string& host = masterConfig.Host();
	uint16_t port = masterConfig.Port();
	int32_t serverNo = 1;
	string serverName = "chat_instance";
	
	MasterPacketDiscriminator::Init();
	ASSERT_CRASH(masterNet->Ready(1));
	ASSERT_CRASH(masterNet->ReadyToConnect(host, port));

	masterNet->CreateSessionFactory = [serverNo, serverName](){
		auto _session = MakeShared<MasterServerSession>();
		_session->SetOnSessionConnectedFunc([_session, serverNo, serverName](){
			MS_DEBUG_LOG("chat server connected to master server! - serverNo : {}, serverName : {}", serverNo, serverName);
			MasterAndChatServer::ReqChatConnectMaster _packet;
			_packet.set_server_name(serverName.c_str());
			_packet.set_server_no(serverNo);
			_session->SendPacket(_packet);

		});
		return _session;
	};
	masterNet->StartConnect(1);
	UInt32 waitMilliSec = INFINITE;
	while (true) {
		masterNet->Dispatch(waitMilliSec);
	}

	return ;
}

void StartChatThread() {
	NetworkCoreSptr chatNet = MakeShared<NetworkCore>();
	int32_t acceptCnt = chatConfig.AcceptCnt();
	int32_t backLog = chatConfig.BackLog();
	uint16_t listenPort = chatConfig.ListenPort();
	int32_t iocpThreadCnt = 1;

	string serverName = chatConfig.Name();
	int32_t tag1 = chatConfig.No();
	UInt32 tag2 = 0;


	UserPacketDiscriminator::Init();
	ASSERT_CRASH(chatNet->Ready(iocpThreadCnt));
	CS_DEBUG_LOG("wsa standby");
	
	ListenerSptr listener = MakeShared<Listener>(listenPort);
	CS_DEBUG_LOG("ready listener for chat server");

	chatNet->CreateSessionFactory = [] {
		UserSessionSptr _session = MakeShared<UserSession>();
		ChatUserSptr chatUser = MakeShared<ChatUser>();
		_session->SetChatUser(chatUser);
		chatUser->SetSession(_session);
		_session->SetOnSessionDisconnectedFunc([_session]() {
			auto chatUser = _session->GetChatUser();
			if (chatUser != nullptr) {
				auto chatRoom = chatUser->GetChatRoom();
				if (chatRoom != nullptr) {
					chatRoom->DoAsync(&ChatRoom::Leave, chatUser);
				}
			}
		});
		return static_pointer_cast<Session>(_session);
	};

	ASSERT_CRASH(chatNet->ReadyToAccept(listener, backLog, acceptCnt));
	CS_DEBUG_LOG("accept ready");
	
	int32_t initNormalRoomSize = 3;
	int32_t initGuildRoomSize = 0;
	int32_t maxUserCntInChatRoom = 3;
	int32_t maxRoomCntInChatRoom = 10;

	ChatRoomMng::initGuildRoomSize = initGuildRoomSize;
	ChatRoomMng::initNormalRoomSize = initNormalRoomSize;
	ChatRoom::maxUserCnt = maxUserCntInChatRoom;
	ChatRoom::maxRoomCnt = maxRoomCntInChatRoom;

	ChatRoomMng::Get().Init();


	UInt32 waitMilliSec = INFINITE;
	while (true) {
		chatNet->Dispatch(waitMilliSec);
	}
	return ;
}