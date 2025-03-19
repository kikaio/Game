#include "pch.h"
#include "ClientType.h"

void LoginResultData::Render()
{
	DUM_DEBUG_LOG("[LoginResultData]======");
	DUM_DEBUG_LOG(isSuccess ? "login success" : "login failed");
	DUM_DEBUG_LOG("login token : {}", loginToken);
}
