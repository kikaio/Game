#pragma once


DECL_REF_USING(UserSession);
DECL_REF_USING(MasterSession);
DECL_REF_USING(GameUser);

#define MAKE_PACKET_ERROR(_no, _detail) PacketError { ENUM_TO_INT(_no), ENUM_TO_INT(_detail) }

#define COMAPRE_PACKET_ERROR(_err_packet, _no, _detail) _err_packet.Compare(ENUM_TO_INT(_no), ENUM_TO_INT(_detail))


struct PacketError {
	int32_t err_no = 0;
	int32_t err_detail = 0;
	string err_desc = "";
public:
	PacketError() {
	}
	PacketError(int32_t _err_no, int32_t _err_detail) 
	 : err_no(_err_no), err_detail(_err_detail)
	{
	}
	PacketError(int32_t _err_no, int32_t _err_detail, string _desc) 
	 : err_no(_err_no), err_detail(_err_detail), err_desc(_desc)
	{
	}
public:
	bool HasError() {
		return err_no != 0;
	}
	bool Compare(int _no, int _detail) {
		return (_no == err_no) && (_detail == err_detail);
	}
};

struct LoginData {
public:
	string sId = ""; // guest 인 경우 device key 가 온다.
	LOGIN_PLATFORM loginPlatform = LOGIN_PLATFORM::GUEST;
	string loginToken = "";
	string refreshToken = "";
};

struct LoginResultData {
	bool isSuccess = false;
	string loginToken = "";
};
