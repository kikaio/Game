#include "pch.h"
#include "LogHelper.h"


LoggerSptr LogHelper::dumLogger = nullptr;

LoggerSptr LogHelper::CreateDumLogger(string _dumLogPath)
{
	return std::make_shared<Logger>("dummy", _dumLogPath, true);
}

void LogHelper::Init(string _logFilePath)
{
	DUM_LOOGER = CreateDumLogger(_logFilePath);
	DUM_LOOGER->SetLevel(spdlog::level::debug);
}
