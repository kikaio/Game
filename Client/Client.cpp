#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	PacketBuffer buf;
	BufWriter writer(buf);
	UInt16 testVal = 1000;
	UInt16 testVal2 = 10;
	string testStr = "test_msg";

	writer << testVal;
	writer << testVal2;
	writer << testStr;

	BufReader reader(buf);
	UInt16 retVal = 0;
	UInt16 retVal2 = 0;
	string retStr;
	reader >> retVal;
	reader >> retVal2;
	reader >> retStr;

	printf("read val : %d\n", retVal);
	printf("read val2 : %d\n", retVal2);
	printf("read retStr : %s\n", retStr.c_str());

	return 0;
}