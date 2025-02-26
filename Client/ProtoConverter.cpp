
#include "pch.h"
#include "ProtoConverter.h"

void ProtoConverter::toProto(const LoginData& _in, UserAndGameServer::LoginData& _out)
{
	_out.set_device_key(_in.deviceKey);
}

void ProtoConverter::fromProto(const UserAndGameServer::LoginResultData& _in, LoginResultData& _out)
{
	_out.isSuccess = _in.is_success();
}
