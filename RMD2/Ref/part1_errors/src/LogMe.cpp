#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe
{

    Logger::Logger()
        : m_os{}
        , m_os_ptr{&std::cerr}
    {
    }

    Logger::Logger(const std::string& path)
        : m_os{path}
    {
        if (m_os.is_open())
            m_os_ptr = &m_os;
        else
            throw std::runtime_error(
                "Logger::Logger(path): Could not open " + path + '\n');
    }

    void Logger::log(logging_level level, const std::string& msg)
    {
        if (m_os_ptr->bad()){
            if (m_os.is_open()){
              m_os.close();
              m_os_ptr = &std::cerr;
              log(Error, "Write to file error, switch to cerr\n");
            } else {
              throw std::runtime_error("Logger::log(): Failed on cerr.\n");
            }
        }

        if (level <= m_level)
            (*m_os_ptr) << msg;
    }

    void Logger::set_debug_level(logging_level level)
    {
        m_level = level;
    }

    void Logger::debug(const std::string& msg)    { log(Debug, msg); }
    void Logger::info(const std::string& msg)     { log(Info, msg); }
    void Logger::warn(const std::string& msg)     { log(Warn, msg); }
    void Logger::error(const std::string& msg)    { log(Error, msg); }
    void Logger::critical(const std::string& msg) { log(Critical, msg); }

    // As before

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