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

	return 0;
}
