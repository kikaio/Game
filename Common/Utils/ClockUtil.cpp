#include "pch.h"
#include "CommonMacro.h"
#include "StrUtil.h"

string ClockUtil::GetDateTimeStr(tm _tm, const char* _fm, UInt16 _milli)
{
	array<char, STRFTIME_BUF_SIZE> tmpBuf = {0, };
	strftime(tmpBuf.data(), tmpBuf.size(), _fm, &_tm);
	string ret = tmpBuf.data();
	if(_milli > 0 ){
		ret += "." + to_string(_milli);
	}
	return ret;
}

string ClockUtil::GetNowStr(bool _isUTC, const char* _fm)
{
	auto utcNowTimePoint = system_clock::now();
	const time_t time = system_clock::to_time_t(utcNowTimePoint);
	tm inputTm = {};
	if(_isUTC == false) {
		localtime_s(&inputTm, &time);
	}
	else {
		gmtime_s(&inputTm, &time);
	}
	return GetDateTimeStr(inputTm, _fm);
}

string ClockUtil::GetNowStrWithMilli(bool _isUTC, const char* _fm)
{
	auto utcNowTimePoint = system_clock::now();
	const time_t time = system_clock::to_time_t(utcNowTimePoint);
	tm inputTm = {};
	if (_isUTC == false) {
		localtime_s(&inputTm, &time);
	}
	else {
		gmtime_s(&inputTm, &time);
	}
	UInt16 milliSec =  utcNowTimePoint.time_since_epoch().count() % 1000;
	return GetDateTimeStr(inputTm, _fm, milliSec);
}

time_t ClockUtil::GetTimeSec()
{
	return std::chrono::duration_cast<seconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}

time_t ClockUtil::GetTimeMsec()
{
	return std::chrono::duration_cast<milliseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}

time_t ClockUtil::GetTimeUsec()
{
	return std::chrono::duration_cast<microseconds>(
		std::chrono::system_clock::now().time_since_epoch()
	).count();
}

tm ClockUtil::GetLocalTime()
{
	time_t time = GetTimeSec();
	tm local = {0, };
	localtime_s(&local, &time);
	return local;
}

tm ClockUtil::GetUtcTime()
{
	time_t time = GetTimeSec();
	tm utc = {0, };
	gmtime_s(&utc, &time);
	return utc;
}

void ClockUtil::TimeToTmLocal(time_t _time, OUT tm& _local)
{
	localtime_s(&_local, &_time);
	return ;
}

void ClockUtil::TimeToTmUtc(time_t _time, OUT tm& _utc)
{
	_gmtime64_s(&_utc, &_time);
	return ;
}

time_t ClockUtil::TmLocalToTime(tm& _local)
{
	return _mktime64(&_local);
}

time_t ClockUtil::TmUtcToTime(tm& _utc)
{
	return _mkgmtime64(&_utc);
}

time_t ClockUtil::GetDeltaUtcAndLocal()
{
	time_t timeVal = time(NULL);
	tm local;
	tm utc;
	TimeToTmLocal(timeVal, OUT local);
	TimeToTmUtc(timeVal, OUT utc);

	time_t localTime = TmLocalToTime(local);
	time_t utcTime = TmUtcToTime(utc);
	return localTime - utcTime;
}

string ClockUtil::GetCurTimeZone()
{
	array<char, BUF_128> buf = {0, };
	TIME_ZONE_INFORMATION tz;
	GetTimeZoneInformation(&tz);
	std::wstring wName = tz.StandardName;
	WideCharToMultiByte(0, 0, wName.c_str(), wName.size(), buf.data(), buf.size(), 0, 0);
	return buf.data();
}
