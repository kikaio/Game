#include "pch.h"
#include "LogHelper.h"


LoggerSptr LogHelper::dumLogger = nullptr;

LoggerSptr LogHelper::CreateDumLogger(string _dumLogPath)
{
	return LoggerSptr();
}

void LogHelper::Init(string _logFilePath)
{
	DUM_LOOGER = CreateDumLogger(_logFilePath);
	DUM_LOOGER->SetLevel(spdlog::level::debug);
}
