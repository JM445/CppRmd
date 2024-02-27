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

    namespace internal {
        Logger m_default_logger = Logger("mylog.log");
    }


    void set_debug_level(logging_level level) { internal::m_default_logger.set_debug_level(level); }



    // Part 3

    StreamLogger::StreamLogger(const std::string& path)
        : m_logger{path}
    {
    }

    StreamLogger& operator<< (StreamLogger& s, logging_level level)
    {
        s.m_flag = level;
        return s;
    }

}