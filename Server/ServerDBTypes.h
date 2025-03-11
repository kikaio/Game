#pragma once


class PlatformRow {
public:
	int64_t pId = 0;
	char sIdBuf[50] = {0, };
	int64_t aId = 0;
	int32_t pType = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, int32_t _curIdx, OUT int32_t& _nextCol) {
		_binder.BindCol(_curIdx++, OUT pId);
		memset(sIdBuf, sizeof(sIdBuf), 0);
		_binder.BindCol(_curIdx++, OUT sIdBuf);
		_binder.BindCol(_curIdx++, OUT pType);
		_binder.BindCol(_curIdx++, OUT aId);
		_binder.BindCol(_curIdx++, OUT cDate);
		_binder.BindCol(_curIdx++, OUT mDate);
		_nextCol = _curIdx;
	}

	string GetSid() {
		return sIdBuf;
	}
};

class AccountRow {
public:
	int64_t aId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, int32_t _curIdx, OUT int32_t& _nextCol) {
		_binder.BindCol(_curIdx++, OUT aId);
		_binder.BindCol(_curIdx++, OUT cDate);
		_binder.BindCol(_curIdx++, OUT mDate);
		_nextCol = _curIdx;
		return ;
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
	void FromDB(DB_BINDER& _binder, OUT int32_t _curIdx, OUT int32_t& _nextCol) {
		_binder.BindCol(_curIdx++, OUT sId);
		_binder.BindCol(_curIdx++, OUT aId);
		_binder.BindCol(_curIdx++, OUT cDate);
		_binder.BindCol(_curIdx++, OUT mDate);

		_nextCol = _curIdx;
		return ;
	}
};

class ProfileRow {
public:
	int64_t pId = 0;
	int64_t aId = 0;
	int64_t main_hero_id = 0;
	int32_t main_frame_id = 0;
	char greetingMent[50] = {0, };
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, OUT int32_t _curIdx, OUT int32_t& _nextCol) {
		_binder.BindCol(_curIdx++, OUT pId);
		_binder.BindCol(_curIdx++, OUT aId);
		_binder.BindCol(_curIdx++, OUT main_hero_id);
		_binder.BindCol(_curIdx++, OUT main_frame_id);
		memset(greetingMent, sizeof(greetingMent), 0);
		_binder.BindCol(_curIdx++, OUT greetingMent);
		_binder.BindCol(_curIdx++, OUT cDate);
		_binder.BindCol(_curIdx++, OUT mDate);

		_nextCol = _curIdx;
	}

public:
	string GetGreetingMent() {
		return greetingMent;
	}
};