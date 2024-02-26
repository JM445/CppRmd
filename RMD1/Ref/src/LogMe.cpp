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


    // Part 2

    namespace {

        auto m_default_logger = Logger{"mylog.log"};
    
    }


    void set_debug_level(logging_level level) { m_default_logger.set_debug_level(level); }
    void debug(const std::string& msg) { m_default_logger.debug(msg); }
    void info(const std::string& msg) {m_default_logger.info(msg); }
    void warn(const std::string& msg) { m_default_logger.warn(msg); }
    void critical(const std::string& msg) { m_default_logger.critical(msg); }
    void error(const std::string& msg) { m_default_logger.error(msg); }


}