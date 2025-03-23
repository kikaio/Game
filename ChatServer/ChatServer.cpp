// ChatServer.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"

int main()
{
	LogHelper::Init("logs", "info");

	CS_DEBUG_LOG("test_chat logger");
	MS_DEBUG_LOG("test_master logger");

	CS_INFO_LOG("test_chat info logger");
	MS_INFO_LOG("test_master info logger");
}