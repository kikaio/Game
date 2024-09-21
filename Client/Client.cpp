#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	string nowUtcStr = ClockUtil::GetNowStr();
	printf("cur datetime : %s\n", nowUtcStr.c_str());
	string nowUtcStrWithMilli = ClockUtil::GetNowStrWithMilli();
	printf("cur datetime : %s\n", nowUtcStrWithMilli.c_str());

	string nowLocalStr = ClockUtil::GetNowStr(false);
	printf("cur datetime : %s\n", nowLocalStr.c_str());
	string nowLocalStrWithMilli = ClockUtil::GetNowStrWithMilli(false);
	printf("cur datetime : %s\n", nowLocalStrWithMilli.c_str());

	return 0;
}