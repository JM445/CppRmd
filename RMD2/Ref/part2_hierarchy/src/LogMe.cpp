#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe
{

    LoggerBase::LoggerBase()
        : m_os{}
        , m_os_ptr{&std::cerr}
    {
    }

    LoggerBase::LoggerBase(const std::string& path)
        : m_os{path},
          m_os_ptr{&m_os}
    {
    }

    void Logger::log(logging_level level, const std::string& msg)
    {
        if (level <= m_level)
            (*m_os_ptr) << msg;
    }

    void LoggerBase::set_debug_level(logging_level level)
    {
        m_level = level;
    }

    void LoggerBase::debug(const std::string& msg)    { log(Debug, msg); }
    void LoggerBase::info(const std::string& msg)     { log(Info, msg); }
    void LoggerBase::warn(const std::string& msg)     { log(Warn, msg); }
    void LoggerBase::error(const std::string& msg)    { log(Error, msg); }
    void LoggerBase::critical(const std::string& msg) { log(Critical, msg); }

}