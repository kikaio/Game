#pragma once

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
		int32_t colNo = 1;
		_binder.GetInt64(colNo++, OUT pId);
		_binder.GetInt64(colNo++, OUT aId);
		_binder.GetStr(colNo++, OUT nickName);
		_binder.GetInt64(colNo++, OUT mainHeroId);
		_binder.GetInt32(colNo++, OUT mainFrameId);

		_binder.GetStr(colNo++, OUT greetingMent);

		_binder.GetInt64(colNo++, OUT cDate);
		_binder.GetInt64(colNo++, OUT mDate);

		return;
	}
public:
	void Render() {
		printf("========[]========\n");
		printf("%s\n", fmt::format("").c_str());
		printf("==================\n");
	}
};
