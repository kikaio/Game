#include "pch.h"


using namespace std;

void PrintLn(const char* _msg) {
	printf("%s\n", _msg);
}

int main()
{
	PacketBuffer pb;
	UInt32 testVal = 1000;
	UInt32 testVal2 = 10;

	pb.WriteBytes(reinterpret_cast<BYTE*>(&testVal), sizeof(UInt32));
	pb.Calc();
	pb.Render();

	UInt32 retVal = 0;
	pb.ReadBytes(reinterpret_cast<BYTE*>(&retVal), sizeof(UInt32));
	printf("read val : %d\n", retVal);

	return 0;
}