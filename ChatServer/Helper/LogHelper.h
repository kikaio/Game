#pragma once

#define CHAT_LOGGER LogHelper::chatLogger
#define CS_DEBUG_LOG(_fmt, ...) CHAT_LOGGER->Debug(_fmt, __VA_ARGS__)
#define CS_WARN_LOG(_fmt, ...) CHAT_LOGGER->Warn(_fmt, __VA_ARGS__)
#define CS_TRACE_LOG(_fmt, ...) CHAT_LOGGER->Trace(_fmt, __VA_ARGS__)
#define CS_INFO_LOG(_fmt, ...) CHAT_LOGGER->Info(_fmt, __VA_ARGS__)
#define CS_ERROR_LOG(_fmt, ...) CHAT_LOGGER->Error(_fmt, __VA_ARGS__)

#define MASTER_LOGGER LogHelper::masterLogger
#define MS_DEBUG_LOG(_fmt, ...) MASTER_LOGGER->Debug(_fmt, __VA_ARGS__)
#define MS_WARN_LOG(_fmt, ...) MASTER_LOGGER->Warn(_fmt, __VA_ARGS__)
#define MS_TRACE_LOG(_fmt, ...) MASTER_LOGGER->Trace(_fmt, __VA_ARGS__)
#define MS_INFO_LOG(_fmt, ...) MASTER_LOGGER->Info(_fmt, __VA_ARGS__)
#define MS_ERROR_LOG(_fmt, ...) MASTER_LOGGER->Error(_fmt, __VA_ARGS__)

class LogHelper {
public:
	static LoggerSptr masterLogger;
	static LoggerSptr chatLogger;
private:
	static LoggerSptr CreateChatLogger(string _fullPath);
	static LoggerSptr CreateMasterLogger(string _fullPath);
public:
	static void Init(string _logPath = "", string _logLv = "debug");
};