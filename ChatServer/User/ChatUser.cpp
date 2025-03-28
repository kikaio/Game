#include "pch.h"
#include "ChatUser.h"


int64_t ChatUser::GetProfileId() {
	return profile.GetProfileId();
}

UserSessionSptr ChatUser::GetSession()
{
	return userSession.lock();;
}

void ChatUser::SetSession(UserSessionSptr _session)
{
	userSession = _session;
}
