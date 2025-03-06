#pragma once

class DBWrapper
{
public:
	static int32_t DoDatabaseTest();
public:
	static PacketError SelectAccount(const LoginData& _loginData);
};