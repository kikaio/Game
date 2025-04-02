#pragma once

#define MAKE_PACKET_ERROR(_no, _detail) PacketError { ENUM_TO_INT(_no), ENUM_TO_INT(_detail) }

#define COMAPRE_PACKET_ERROR(_err_packet, _no, _detail) _err_packet.Compare(ENUM_TO_INT(_no), ENUM_TO_INT(_detail))


DECL_REF_USING(Logger);
DECL_WREF_USING(Logger);

DECL_REF_USING(ChatUser);
DECL_WREF_USING(ChatUser);

DECL_REF_USING(ChatProfile);
DECL_WREF_USING(ChatProfile);

DECL_REF_USING(ChatData);
DECL_WREF_USING(ChatData);

DECL_REF_USING(ChatRoom);
DECL_WREF_USING(ChatRoom);

DECL_REF_USING(UserSession);
DECL_WREF_USING(UserSession);

DECL_REF_USING(MasterServerSession);
DECL_WREF_USING(MasterServerSession);


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
