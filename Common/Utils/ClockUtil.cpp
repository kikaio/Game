#include "pch.h"
#include "CommonMacro.h"

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
