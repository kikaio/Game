#pragma once

class DBWrapper
{
public:
	static int32_t DoDatabaseTest();
public:
	static PacketError SelectPlatform(const LoginData& _loginData);
	static PacketError SelectAccount(const LoginData& _loginData);
//	static PacketError CreateAccount(const LoginData& _loginData);
};