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
	static time_t getTimeSec();
	static time_t getTimeMsec();
	static time_t getTimeUsec();
	static tm* getLocalTime();
};