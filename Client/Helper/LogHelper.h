#pragma once


#define DUM_LOOGER LogHelper::dumLogger

#define DUM_DEBUG_LOG(_str, ...) DUM_LOOGER->Debug(_str, __VA_ARGS__)
#define DUM_INFO_LOG(_str, ...) DUM_LOOGER->Info(_str, __VA_ARGS__)
#define DUM_WARN_LOG(_str, ...) DUM_LOOGER->Warn(_str, __VA_ARGS__)
#define DUM_TRACE_LOG(_str, ...) DUM_LOOGER->Trace(_str, __VA_ARGS__)
#define DUM_ERR_LOG(_str, ...) DUM_LOOGER->Error(_str, __VA_ARGS__)

#define CLIENT_LOOGER LogHelper::clientLogger
#define CLIENT_DEBUG_LOG(_str, ...) CLIENT_LOOGER->Debug(_str, __VA_ARGS__)
#define CLIENT_INFO_LOG(_str, ...) CLIENT_LOOGER->Info(_str, __VA_ARGS__)
#define CLIENT_WARN_LOG(_str, ...) CLIENT_LOOGER->Warn(_str, __VA_ARGS__)
#define CLIENT_TRACE_LOG(_str, ...) CLIENT_LOOGER->Trace(_str, __VA_ARGS__)
#define CLIENT_ERR_LOG(_str, ...) CLIENT_LOOGER->Error(_str, __VA_ARGS__)

class LogHelper {
public:
	static LoggerSptr dumLogger;
	static LoggerSptr clientLogger;
public:
	static void Init(string _logFolderPath);
private:
	static LoggerSptr CreateDumLogger(string _dumLogPath);
	static LoggerSptr CreateClientLogger(string _dumLogPath);
};

