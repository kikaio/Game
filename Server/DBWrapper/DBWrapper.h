#pragma once

class DBWrapper
{
public:
	static bool TryConnectToDatabases();
	static int32_t DoDatabaseTest();
};