#pragma once


class PlatformRow {
public:
	int64_t pId = 0;
	string sId = "";
	int32_t pType = 0;
	int64_t aId = 0;
	string token = "";
	string refreshToken = "";
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT pId);
		_binder.GetStr(colNo++, OUT sId);
		_binder.GetInt32(colNo++, OUT pType);
		_binder.GetInt64(colNo++, OUT aId);
		_binder.GetStr(colNo++, OUT token);
		_binder.GetStr(colNo++, OUT refreshToken);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
		return ;
	}
public:
	void Render() {
		printf("========[]========\n");
		printf("%s\n", fmt::format("").c_str());
		printf("==================\n");
	}
};

class AccountRow {
public:
	int64_t aId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT aId);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
		return ;
	}
public:
	void Render() {
		printf("========[]========\n");
		printf("%s\n", fmt::format("").c_str());
		printf("==================\n");
	}
};

class SummaryRow {
public:
	int64_t sId = 0;
	int64_t aId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER> 
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT sId);
		_binder.GetInt64(colNo++, OUT aId);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
		return ;
	}
public:
	void Render() {
		printf("========[]========\n");
		printf("%s\n", fmt::format("").c_str());
		printf("==================\n");
	}
};

class ProfileRow {
public:
	int64_t pId = 0;
	int64_t aId = 0;
	string nickName = "";
	int64_t mainHeroId = 0;
	int32_t mainFrameId = 0;
	string greetingMent = "";
	int64_t cDate = 0;
	int64_t mDate = 0;
	char greetingMent2[50] = { 0, };
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo= 1;
		_binder.GetInt64(colNo++, OUT pId);
		_binder.GetInt64(colNo++, OUT aId);
		_binder.GetStr(colNo++, OUT nickName);
		_binder.GetInt64(colNo++, OUT mainHeroId);
		_binder.GetInt32(colNo++, OUT mainFrameId);
		
		_binder.GetStr(colNo++, OUT greetingMent);

		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);

		return ;
	}
public:
	void Render() {
		printf("========[]========\n");
		printf("%s\n", fmt::format("").c_str());
		printf("==================\n");
	}
};

class GameUserRow {
public:
	int64_t gameUserId = 0;
	int64_t accountId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT gameUserId);
		_binder.GetInt64(colNo++, OUT accountId);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
	}
public:
	void Render() {
		printf("========[GameUserRow]========\n");
		printf("%s\n", fmt::format("account id : {}, gameuser id : {}", accountId, gameUserId).c_str());
		printf("==================\n");
	}
};


class CharacterRow {
public:
	int64_t id = 0;
	int64_t gameUserId = 0;
	int64_t basisId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT id);
		_binder.GetInt64(colNo++, OUT gameUserId);
		_binder.GetInt64(colNo++, OUT basisId);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
	}
public:
	void Render() {
		printf("========[CharacterRow]========\n");
		printf("%s\n", fmt::format("gameuser id : {}, basis id : {}", gameUserId, basisId).c_str());
		printf("==================\n");
	}
};


class ItemRow {
public:
	int64_t id = 0;
	int64_t gameUserId = 0;
	int64_t basisId = 0;
	int64_t itemCnt = 0;
	int64_t itemCntPrev = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT id);
		_binder.GetInt64(colNo++, OUT gameUserId);
		_binder.GetInt64(colNo++, OUT basisId);
		_binder.GetInt64(colNo++, OUT itemCnt);
		_binder.GetInt64(colNo++, OUT itemCntPrev);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
	}
public:
	void Render() {
		printf("========[ItemRow]========\n");
		printf("%s\n", fmt::format("gameuser id : {}, basis id : {}", gameUserId, basisId).c_str());
		printf("%s\n", fmt::format("item cnt : {}, item cnt prev : {}", itemCnt, itemCntPrev).c_str());
		printf("==================\n");
	}
};


class CostumeRow {
public:
	int64_t id = 0;
	int64_t gameUserId = 0;
	int64_t basisId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT id);
		_binder.GetInt64(colNo++, OUT gameUserId);
		_binder.GetInt64(colNo++, OUT basisId);
		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);
	}
public:
	void Render() {
		printf("========[CostumeRow]========\n");
		printf("%s\n", fmt::format("gameuser id : {}, basis id : {}", gameUserId, basisId).c_str());
		printf("==================\n");
	}
};