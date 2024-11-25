#include "pch.h"

int main()
{
	ASSERT_CRASH(DBWrapper::ReadDBConfigFile());

	printf("Master Server start\n");

	JsonReader jr;
	string configPath = "./Configs/ServerConfig.json";
	jr.ReadFile(configPath.c_str());
	rapidjson::Value masterConfigVal(kObjectType);
	ASSERT_CRASH(jr.GetObject("master_config", OUT masterConfigVal));

	MasterConfig masterConfig;
	masterConfig.ReadFromJson(masterConfigVal);
	masterConfig.Render();

	NetworkCoreSptr masterServiceNetCore = MakeShared<NetworkCore>();
	ASSERT_CRASH(masterServiceNetCore->Ready());
	printf("master corenet read.\n");
	masterServiceNetCore->CreateSessionFactory = []() {
		auto session= MakeShared<ServerSession>();
		return session;
	};
	return 0;
}
