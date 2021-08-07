#pragma once

#include "common.hh"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#include <memory>

namespace GE
{
class GE_PUBLIC Logger
{

public:
    static void init();

    inline static std::shared_ptr<spdlog::logger>& getEngineLogger() { return m_engineLogger; }
    inline static std::shared_ptr<spdlog::logger>& getClientLogger() { return m_clientLogger; }

private:
    static std::shared_ptr<spdlog::logger> m_engineLogger;
    static std::shared_ptr<spdlog::logger> m_clientLogger;
};
}

#if defined GE_DEBUG

#define ENGINE_LOG_INFO(...) ::GE::Logger::getEngineLogger()->info(__VA_ARGS__)
#define ENGINE_LOG_WARN(...) ::GE::Logger::getEngineLogger()->warn(__VA_ARGS__)
#define ENGINE_LOG_ERROR(...) ::GE::Logger::getEngineLogger()->error(__VA_ARGS__)
#define ENGINE_LOG_TRACE(...) ::GE::Logger::getEngineLogger()->trace(__VA_ARGS__)
#define ENGINE_LOG_FATAL(...) ::GE::Logger::getEngineLogger()->fatal(__VA_ARGS__)

#define LOG_INFO(...) ::GE::Logger::getClientLogger()->info(__VA_ARGS__)
#define LOG_WARN(...) ::GE::Logger::getClientLogger()->warn(__VA_ARGS__)
#define LOG_ERROR(...) ::GE::Logger::getClientLogger()->error(__VA_ARGS__)
#define LOG_TRACE(...) ::GE::Logger::getClientLogger()->trace(__VA_ARGS__)
#define LOG_FATAL(...) ::GE::Logger::getClientLogger()->fatal(__VA_ARGS__)

#else

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