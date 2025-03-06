#include "pch.h"
#include "StrUtil.h"

std::vector<std::string> StrUtil::Split(const std::string& _in, char _delimiter)
{
	std::vector<std::string> ret;
	std::stringstream ss(_in);
	std::string tmp;

	while(getline(ss, tmp, _delimiter)) {
		ret.push_back(tmp);
	}
	return ret;
}

std::vector<std::string> StrUtil::SplitFirstOf(const std::string& _in, char _delimiter)
{
	std::vector<std::string> ret;
	int32_t pivot = _in.find_first_of(_delimiter);
	if(pivot != string::npos) {
		ret.emplace_back(_in.substr(0, pivot));
		ret.emplace_back(_in.substr(pivot+1));
	}
	return ret;
}

bool StrUtil::ParseToInt32(const string _in, int32_t& _out)
{
	try{
		_out = static_cast<int32_t>(std::stoi(_in.c_str()));
	}
	catch(std::invalid_argument e) {
		return false;
	}
	catch(...) {
		return false;
	}
	return true;
}

bool StrUtil::ParseToInt64(const string& _in, int64_t& _out)
{
	try{
		_out = static_cast<int64_t>(std::stoll(_in));
	}
	catch(std::invalid_argument e) {
		return false;
	}
	catch(...) {
		return false;
	}
	return true;
}

bool StrUtil::ParseToiTimeT(const string& _in, time_t& _out)
{
	try{
		_out = static_cast<time_t>(std::stoll(_in));
	}
	catch(std::invalid_argument e) {
		return false;
	}
	catch(...) {
		return false;
	}
	return true;
}

string StrUtil::GetFileName(const string& _path)
{
	int32_t pivot = _path.find_last_of("/\\");
	if(pivot == string::npos) {
		return _path;
	}
	return _path.substr(pivot+1);
}

string StrUtil::GetRandomStr(int _len)
{
	vector<char> sz(_len + 1, '\0');
//	char sz[101] = {'\0', };
	static const char set[] =
		"0123456789"
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz";
	Random rand;
	for(int i = 0; i < _len; ++i) {
		sz[i] = set[rand.GetRand(sizeof(set) - 2)];
	}
//	sz[_len] = 0;
	return sz.data();
}

char StrUtil::GetRandomAscii(char _minAscii, char _maxAscii)
{
	Random rand;
	return rand.GetRand(_minAscii, _maxAscii);
}

string StrUtil::GetRandomHex(int32_t _len, int _minAscii, int _maxAscii)
{
	Random rand;
	std::stringstream ss;
	for(auto i = 0; i < _len; ++i) {
		ss << rand.GetRand(_minAscii, _maxAscii);
	}
	return ss.str();
}