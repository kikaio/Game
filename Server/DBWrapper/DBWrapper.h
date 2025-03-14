#pragma once

class DBWrapper
{
public:
	static int32_t DoDatabaseTest();
public:
	static PacketError PlatformSelect(
		const LoginData& _loginData, GameUserSptr _gameUser
		, OUT bool& _is_old_user
		, int32_t _def_main_hero_id, int32_t _def_main_frame_id, string _def_main_greeting_ment
	);

	static PacketError GameUserCreate(GameUserSptr _gameUser);

	static PacketError GameUserSelect(GameUserSptr _gameUser);
};