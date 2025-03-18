#pragma once


class PlatformRow {
public:
	int64_t pId = 0;
	string sId = "";
	int32_t pType = 0;
	int64_t aId = 0;
	string token = 0;
	string refreshToken = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		_binder.GetInt64(1, OUT pId);
		_binder.GetStr(2, OUT sId);
		_binder.GetInt32(3, OUT pType);
		_binder.GetInt64(4, OUT aId);
		_binder.GetStr(5, OUT token);
		_binder.GetStr(6, OUT refreshToken);
		_binder.GetInt64(7, OUT cDate);
		_binder.GetInt64(8, OUT mDate);
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
		_binder.GetInt64(1, OUT aId);
		_binder.GetInt64(2, OUT cDate);
		_binder.GetInt64(3, OUT mDate);
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
		_binder.GetInt64(1, OUT sId);
		_binder.GetInt64(2, OUT aId);
		_binder.GetInt64(3, OUT cDate);
		_binder.GetInt64(4, OUT mDate);
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
	int64_t mainHeroId = 0;
	int32_t mainFrameId = 0;
	string greetingMent = "";
	int64_t cDate = 0;
	int64_t mDate = 0;
	char greetingMent2[50] = { 0, };
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder) {
		_binder.GetInt64(1, OUT pId);
		_binder.GetInt64(2, OUT aId);
		_binder.GetInt64(3, OUT mainHeroId);
		_binder.GetInt32(4, OUT mainFrameId);
		
		_binder.GetStr(5, OUT greetingMent);

		_binder.GetInt64(6, OUT cDate);
		_binder.GetInt64(7, OUT mDate);

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
		_binder.GetInt64(1, OUT gameUserId);
		_binder.GetInt64(2, OUT accountId);
		_binder.GetInt64(3, OUT cDate);
		_binder.GetInt64(4, OUT mDate);
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
		_binder.GetInt64(1, OUT id);
		_binder.GetInt64(2, OUT gameUserId);
		_binder.GetInt64(3, OUT basisId);
		_binder.GetInt64(4, OUT cDate);
		_binder.GetInt64(5, OUT mDate);
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
		_binder.GetInt64(1, OUT id);
		_binder.GetInt64(2, OUT gameUserId);
		_binder.GetInt64(3, OUT basisId);
		_binder.GetInt64(4, OUT itemCnt);
		_binder.GetInt64(5, OUT itemCntPrev);
		_binder.GetInt64(6, OUT cDate);
		_binder.GetInt64(7, OUT mDate);
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
		_binder.GetInt64(1, OUT id);
		_binder.GetInt64(2, OUT gameUserId);
		_binder.GetInt64(3, OUT basisId);
		_binder.GetInt64(4, OUT cDate);
		_binder.GetInt64(5, OUT mDate);
	}
public:
	void Render() {
		printf("========[CostumeRow]========\n");
		printf("%s\n", fmt::format("gameuser id : {}, basis id : {}", gameUserId, basisId).c_str());
		printf("==================\n");
	}
};