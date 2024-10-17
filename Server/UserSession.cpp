#include "pch.h"
#include "UserSession.h"

UserSession::~UserSession()
{
	printf("UserSession released\n");
}


IMPL_USER_SESSION_SEND_PACKET(Ans, Chat);