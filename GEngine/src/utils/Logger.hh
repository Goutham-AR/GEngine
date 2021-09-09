#pragma once

// cpp std
#include <memory>

// external
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

#include "common.hh"

namespace GE::utils
{
class GE_PUBLIC Logger
{

public:
    static void init();

    inline static Sptr<spdlog::logger>& getEngineLogger() { return m_engineLogger; }
    inline static Sptr<spdlog::logger>& getClientLogger() { return m_clientLogger; }

private:
    static Sptr<spdlog::logger> m_engineLogger;
    static Sptr<spdlog::logger> m_clientLogger;
};
}

#if defined(GE_DEBUG) | !defined(NDEBUG)

#define ENGINE_LOG_INFO(...) ::GE::utils::Logger::getEngineLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_WARN(...) ::GE::utils::Logger::getEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) ::GE::utils::Logger::getEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...) ::GE::utils::Logger::getEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_FATAL(...) ::GE::utils::Logger::getEngineLogger()->fatal(__VA_ARGS__)

#define LOG_INFO(...) ::GE::utils::Logger::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::GE::utils::Logger::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::GE::utils::Logger::getClientLogger()->error(__VA_ARGS__)
#define LOG_TRACE(...) ::GE::utils::Logger::getClientLogger()->trace(__VA_ARGS__)
#define LOG_FATAL(...) ::GE::utils::Logger::getClientLogger()->fatal(__VA_ARGS__)

#else // GE_DEBUG

#define ENGINE_LOG_INFO(...)
#define ENGINE_LOG_WARN(...)
#define ENGINE_LOG_ERROR(...)
#define ENGINE_LOG_TRACE(...)
#define ENGINE_LOG_FATAL(...)

#define LOG_INFO(...)
#define LOG_WARN(...)
#define LOG_ERROR(...)
#define LOG_TRACE(...)
#define LOG_FATAL(...)

#endif // GE_DEBUG