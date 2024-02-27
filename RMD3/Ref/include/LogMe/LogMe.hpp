#pragma once
#include <fstream>
#include <iostream>

namespace LogMe
{
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warn     = 30,
        Info     = 40,
        Debug    = 50
    };

    class Logger
    {
        std::ofstream m_os;
        logging_level m_level = Info;

        public:
            Logger() = default;
            Logger(const std::string& path);

            void set_debug_level(logging_level level); 

            template <typename ArgType>
            void log(logging_level level, const ArgType& msg) {
                if (level <= m_level) {
                    std::cerr << msg;
                    if (m_os.is_open())
                        m_os << msg;
                } 
            }

            template <typename ArgType> void debug(const ArgType& msg) { log(Debug, msg); }
            template <typename ArgType> void info(const ArgType& msg) { log(Info, msg); }
            template <typename ArgType> void warn(const ArgType& msg) { log(Warn, msg); }
            template <typename ArgType> void critical(const ArgType& msg) { log(Critical, msg); }
            template <typename ArgType> void error(const ArgType& msg) { log(Error, msg); }

    };


    // Part 2 (Default logger)
    namespace internal {
        extern Logger m_default_logger;
    }


    void set_debug_level(logging_level level); 
    template <typename ArgType> void debug(const ArgType& msg) { internal::m_default_logger.debug(msg); }
    template <typename ArgType> void info(const ArgType& msg) { internal::m_default_logger.info(msg); }
    template <typename ArgType> void warn(const ArgType& msg) { internal::m_default_logger. warn(msg); }
    template <typename ArgType> void critical(const ArgType& msg) { internal::m_default_logger.critical(msg); }
    template <typename ArgType> void error(const ArgType& msg) { internal::m_default_logger.error(msg); }



    // Part 3 (Stream Logger -> Pattern Adapter)
    class StreamLogger
    {
        Logger         m_logger;
        logging_level  m_flag = Info;

        public:
            StreamLogger() = default;
            StreamLogger(const std::string& path);

            friend StreamLogger& operator<< (StreamLogger& s, logging_level level);

            
            template <class ArgType>
            friend
            StreamLogger& operator<< (StreamLogger& s, const ArgType& msg) { s.m_logger.log(s.m_flag, msg); return s; }
    };
}