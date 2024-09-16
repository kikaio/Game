#include "pch.h"

void HelloWorld()
{
    printf("helloworld\n");
}

int main()
{
    Thread tmpThread = {HelloWorld, 1, "test Thread", "thread for test"};
    tmpThread.RenderInfo();
    tmpThread.Start();
    tmpThread.Join();
    return 0;
}
