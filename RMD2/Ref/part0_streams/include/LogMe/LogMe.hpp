#pragma once
#include <fstream>

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
            void log(logging_level level, const std::string& msg); // Privée pour factoriser
            void debug(const std::string& msg);
            void info(const std::string& msg);
            void warn(const std::string& msg);
            void critical(const std::string& msg);
            void error(const std::string& msg);
    };



    // Stream Logger -> Pattern Adapter
    class StreamLogger
    {
        Logger         m_logger;
        logging_level  m_flag = Info;

        public:
            StreamLogger() = default;
            StreamLogger(const std::string& path);

            friend StreamLogger& operator<< (StreamLogger& s, logging_level level);
            friend StreamLogger& operator<< (StreamLogger& s, const std::string& msg);
    };
}