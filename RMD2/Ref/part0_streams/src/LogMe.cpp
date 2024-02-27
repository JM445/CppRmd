#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe
{
    void Logger::set_debug_level(logging_level level)
    {
        m_level = level;
    }

    Logger::Logger(const std::string& path)
        : m_os{path}
    {            
    }

    void Logger::log(logging_level level, const std::string& msg)
    {            
        if (level <= m_level) {
            std::cerr << msg;
            if (m_os.is_open())
                m_os << msg;
        }
    }

    void Logger::debug(const std::string& msg)    { log(Debug, msg); }
    void Logger::info(const std::string& msg)     { log(Info, msg); }
    void Logger::warn(const std::string& msg)     { log(Warn, msg); }
    void Logger::error(const std::string& msg)    { log(Error, msg); }
    void Logger::critical(const std::string& msg) { log(Critical, msg); }


    StreamLogger::StreamLogger(const std::string& path)
        : m_logger{path}
    {
    }

    StreamLogger& operator<< (StreamLogger& s, logging_level level)
    {
        s.m_flag = level;
        return s;
    }

    StreamLogger& operator<< (StreamLogger& s, const std::string& msg)
    {
        s.m_logger.log(s.m_flag, msg);
        return s;
    }


}