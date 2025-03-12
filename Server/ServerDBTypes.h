#pragma once


class PlatformRow {
public:
	int64_t pId = 0;
	string sId = "";
	int64_t aId = 0;
	int32_t pType = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, int32_t _curColNo, OUT int32_t& _nextCol) {
		_binder.GetInt64(_curColNo++, OUT pId);
		_binder.GetStr(_curColNo++, OUT sId);
		_binder.GetInt32(_curColNo++, OUT pType);
		_binder.GetInt64(_curColNo++, OUT aId);
		_binder.GetInt64(_curColNo++, OUT cDate);
		_binder.GetInt64(_curColNo++, OUT mDate);
		
		_nextCol = _curColNo;
	}
};

class AccountRow {
public:
	int64_t aId = 0;
	int64_t cDate = 0;
	int64_t mDate = 0;
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, int32_t _curColNo, OUT int32_t& _nextCol) {
		_binder.GetInt64(_curColNo++, OUT aId);
		_binder.GetInt64(_curColNo++, OUT cDate);
		_binder.GetInt64(_curColNo++, OUT mDate);
		_nextCol = _curColNo;
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
	void FromDB(DB_BINDER& _binder, OUT int32_t _curColNo, OUT int32_t& _nextCol) {
		_binder.GetInt64(_curColNo++, OUT sId);
		_binder.GetInt64(_curColNo++, OUT aId);
		_binder.GetInt64(_curColNo++, OUT cDate);
		_binder.GetInt64(_curColNo++, OUT mDate);

		_nextCol = _curColNo;
		return ;
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
public:
	template<typename DB_BINDER>
	void FromDB(DB_BINDER& _binder, OUT int32_t _curColNo, OUT int32_t& _nextCol) {
		_binder.GetInt64(_curColNo++, OUT pId);
		_binder.GetInt64(_curColNo++, OUT aId);
		_binder.GetInt64(_curColNo++, OUT mainHeroId);
		_binder.GetInt32(_curColNo++, OUT mainFrameId);
		
		_binder.GetStr(_curColNo++, OUT greetingMent);

		_binder.GetInt64(_curColNo++, OUT cDate);
		_binder.GetInt64(_curColNo++, OUT mDate);

		_nextCol = _curColNo;
	}

public:
};