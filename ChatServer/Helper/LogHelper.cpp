#include "pch.h"
#include "LogHelper.h"


LoggerSptr LogHelper::chatLogger = nullptr;
LoggerSptr LogHelper::masterLogger = nullptr;

LoggerSptr LogHelper::CreateChatLogger(string _fullPath) {
	return make_shared<Logger>("chat", _fullPath, true);
}
LoggerSptr LogHelper::CreateMasterLogger(string _fullPath) {
	return make_shared<Logger>("master", _fullPath, true);
}


void LogHelper::Init(string _logPath, string _logLv) {
	CHAT_LOGGER = CreateChatLogger(_logPath + "/chat.log");
	MASTER_LOGGER = CreateMasterLogger(_logPath + "/master.log");

	transform(_logLv.begin(), _logLv.end(), _logLv.begin(), ::toupper);
	if(_logLv == "ERROR") {
		CHAT_LOGGER->SetLevel(spdlog::level::err);
		MASTER_LOGGER->SetLevel(spdlog::level::err);
	}
	else if (_logLv == "WARN") {
		CHAT_LOGGER->SetLevel(spdlog::level::warn);
		MASTER_LOGGER->SetLevel(spdlog::level::warn);
	}
	else if (_logLv == "INFO") {
		CHAT_LOGGER->SetLevel(spdlog::level::info);
		MASTER_LOGGER->SetLevel(spdlog::level::info);
	}
	else if (_logLv == "TRACE") {
		CHAT_LOGGER->SetLevel(spdlog::level::trace);
		MASTER_LOGGER->SetLevel(spdlog::level::trace);
	}
	else if (_logLv == "CRITICAL") {
		CHAT_LOGGER->SetLevel(spdlog::level::critical);
		MASTER_LOGGER->SetLevel(spdlog::level::critical);
	}
	else {
		CHAT_LOGGER->SetLevel(spdlog::level::debug);
		MASTER_LOGGER->SetLevel(spdlog::level::debug);
	}
}
