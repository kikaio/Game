#include "pch.h"
#include "DBWrapper.h"


ChatProfileSptr DBWrapper::ChatProfileSelect(int64_t _accountId) {
	
	
	DBConnectionSptr conn = DBConnectionPool::Get().PopCommonDB();
	if (conn == nullptr) {
		GS_DEBUG_LOG("db connection pool is empty, check this. - PlatformSelect");
		return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::CONNECTION_NOT_EXIST);
	}
	DBBind<1, 0> dbBinder(*conn, "call usp_profile_select(?);");
	int32_t bindIdx = 0;
	dbBinder.BindParam(bindIdx++, IN _accountId);
	if (dbBinder.Execute() == false) {
		CS_ERROR_LOG("call usp_profile_select failed. param : {}", _accountId);
		return MAKE_PACKET_ERROR(ERR_CATEGORY::DB, DB_ERR_DETAIL::PROCEDURE_FAILED);
	}

	ProfileRow profileRow;

	while (dbBinder.Fetch()) {
		profileRow.FromDB(dbBinder);
	}

	return ChatProfileMng::Get().CreateProfile(
		profileRow.aId
		, profileRow.nickName
		, profileRow.mainHeroId
		, profileRow.mainFrameId
	);
}