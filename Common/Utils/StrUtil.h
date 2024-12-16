#pragma once

class StrUtil
{
public:
	static std::vector<std::string> Split(const std::string& _in, char _delimiter);
	static std::vector<std::string> SplitFirstOf(const std::string& _in, char _delimiter);

	static bool ParseToInt32(const string _in, int32_t& _out);
	static bool ParseToInt64(const string& _in, int64_t& _out);
	static bool ParseToiTimeT(const string& _in, time_t& _out);

	static string GetFileName(const string& _path);
	static string GetRandomStr(int _len = 100);
	static char GetRandomAscii(char _minAscii, char _maxAscii);
	static string GetRandomHex(int32_t _len, int _minAscii, int _maxAscii);

	template<typename... ARGS>
	static string StrFormat(const std::string& _fmt, ARGS... args) {
		size_t size = snprintf(nullptr, 0, _fmt.c_str(), args...)  + 1;
		ASSERT_CRASH(size <= 0);
		unique_ptr<char*> buf = char[size] {0, };
		snprintf(buf.get(), size, _fmt.c_str(), args...);
		return std::string(buf.get(), buf.get() + size -1);
	}
};