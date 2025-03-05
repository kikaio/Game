#pragma once

#include "spdlog/spdlog.h"
#include "spdlog/logger.h"

class Logger {
private:
	std::shared_ptr<spdlog::logger> logger = nullptr;
	string loggerName = "";
	string fileName = "";
	bool isActive = false;
public:
	Logger(string _loggerName, string _fileName, bool _isActive);
	Logger(string _loggerName, spdlog::sinks_init_list _initList, bool _isActive);
	Logger() = delete;
	Logger(const Logger& _other) = delete;
	Logger(Logger&& _other) = delete;
	Logger& operator=(Logger&& _other) = delete;
public:
	void ToggleActive();
	void SetLevel(spdlog::level::level_enum _lv);
	void SetPattern(string _pattern);
public :
	template<typename... Args>
	inline void Trace(spdlog::format_string_t<Args...> _fmt, Args&&... _args) {
		if (isActive == false || logger == nullptr) {
			return;
		}
		logger->trace(_fmt, std::forward<Args>(_args)...);
	}
	template<typename... Args>
	inline void Debug(spdlog::format_string_t<Args...> _fmt, Args&&... _args) {
		if(isActive == false || logger == nullptr) {
			return ;
		}
		logger->debug(_fmt, std::forward<Args>(_args)...);
	}
	template<typename... Args>
	inline void Warn(spdlog::format_string_t<Args...> _fmt, Args&&... _args) {
		if (isActive == false || logger == nullptr) {
			return;
		}
		logger->warn(_fmt, std::forward<Args>(_args)...);
	}
	template<typename... Args>
	inline void Error(spdlog::format_string_t<Args...> _fmt, Args&&... _args) {
		if (isActive == false || logger == nullptr) {
			return;
		}
		logger->error(_fmt, std::forward<Args>(_args)...);
	}
	template<typename... Args>
	inline void Info(spdlog::format_string_t<Args...> _fmt, Args&&... _args) {
		if (isActive == false || logger == nullptr) {
			return;
		}
		logger->info(_fmt, std::forward<Args>(_args)...);
	}
};