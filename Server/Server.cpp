#include "pch.h"

void HelloWorld()
{
    printf("helloworld\n");
}

class Test
{
public:
    Test() = default;
    Test(UInt32 _tmp) : tmp(_tmp) {}
public:
    UInt32 tmp = 0;
};

class NetAddr
{
private:
    string hsot;
    UInt8 port;
    
};



int main()
{
    return 0;
}
