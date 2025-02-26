#include "pch.h"
#include "ProtoConverter.h"

void ProtoConverter::toProto(const UserAndGameServer::LoginData& _in, LoginData& _out)
{
	_out.deviceKey = _in.device_key();
	return ;
}

void ProtoConverter::fromProto(const LoginResultData& _in, UserAndGameServer::LoginResultData& _out)
{
	_out.set_is_success(_in.isSuccess);
	return;
}
