#pragma once

class DBWrapper
{
public:
	static int32_t DoDatabaseTest();
public:
	static PacketError SelectPlatform(
		const LoginData& _loginData, OUT bool& _is_old_user
		, int32_t _def_main_hero_id, int32_t _def_main_frame_id, string _def_main_greeting_ment
	);
};