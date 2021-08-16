#include "utils/Logger.hh"
#include <spdlog/sinks/stdout_color_sinks.h>

namespace GE::utils
{

Sptr<spdlog::logger> Logger::m_engineLogger;
Sptr<spdlog::logger> Logger::m_clientLogger;

void Logger::init()
{
    spdlog::set_pattern("%^[%T] %n: %v%$");

    m_engineLogger = spdlog::stdout_color_mt("Engine");
    m_engineLogger->set_level(spdlog::level::trace);

    m_clientLogger = spdlog::stdout_color_mt("Client");
    m_clientLogger->set_level(spdlog::level::trace);
}

}