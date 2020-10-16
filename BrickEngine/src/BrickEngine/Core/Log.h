#pragma once

#include "pch.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <spdlog/sinks/stdout_color_sinks.h>

namespace BrickEngine {

	class Log
	{
	public:
		static void Init();

		template<typename... Args>
		inline static void CoreFatal(const char* fmt, const Args&... args) { s_CoreLogger->critical(fmt, args...); }
		template<typename... Args>
		inline static void CoreError(const char* fmt, const Args&... args) { s_CoreLogger->error(fmt, args...); }
		template<typename... Args>
		inline static void CoreWarn(const char* fmt, const Args&... args) { s_CoreLogger->warn(fmt, args...); }
		template<typename... Args>
		inline static void CoreInfo(const char* fmt, const Args&... args) { s_CoreLogger->info(fmt, args...); }
		template<typename... Args>
		inline static void CoreTrace(const char* fmt, const Args&... args) { s_CoreLogger->trace(fmt, args...); }

		template<typename... Args>
		inline static void Fatal(const char* fmt, const Args&... args) { s_ClientLogger->critical(fmt, args...); }
		template<typename... Args>
		inline static void Error(const char* fmt, const Args&... args) { s_ClientLogger->error(fmt, args...); }
		template<typename... Args>
		inline static void Warn(const char* fmt, const Args&... args) { s_ClientLogger->warn(fmt, args...); }
		template<typename... Args>
		inline static void Info(const char* fmt, const Args&... args) { s_ClientLogger->info(fmt, args...); }
		template<typename... Args>
		inline static void Trace(const char* fmt, const Args&... args) { s_ClientLogger->trace(fmt, args...); }

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};

}
