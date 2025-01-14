#pragma once

using namespace std;
using namespace std::chrono;

#define STRFTIME_BUF_SIZE				128
#define DEF_DT_STR_FORMAT				"%Y-%m-%d %H:%M:%S"

class ClockUtil
{
private:
	static string GetDateTimeStr(tm _tm, const char* _fm = DEF_DT_STR_FORMAT, UInt16 _milli = 0);
public:
	static string GetNowStr(bool _isUTC = true, const char* _fm = DEF_DT_STR_FORMAT);
	static string GetNowStrWithMilli(bool _isUTC = true, const char* _fm = DEF_DT_STR_FORMAT);
	static time_t GetTimeSec();
	static time_t GetTimeMsec();
	static time_t GetTimeUsec();
	static tm GetLocalTime();
	static tm GetUtcTime();

	static void TimeToTmLocal(time_t _time, OUT tm& _local);
	static void TimeToTmUtc(time_t _time, OUT tm& _utc);

	static time_t TmLocalToTime(tm& _local);
	static time_t TmUtcToTime(tm& _utc);
	static time_t GetDeltaUtcAndLocal();

	static string GetCurTimeZone();
};