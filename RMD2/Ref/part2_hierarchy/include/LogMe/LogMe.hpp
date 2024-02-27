#pragma once
#include <fstream>
#include <memory>



namespace LogMe
{
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warn     = 30,
        Info     = 40,
        Debug    = 50
    };

    // Part 1, now with errors
    class LoggerBase
    {
        protected:
            std::ofstream m_os;
            std::ostream* m_os_ptr; // Guaranteed to be never null post ctor
            logging_level m_level = Info;

        public:
            LoggerBase();
            LoggerBase(const std::string& path);
            virtual ~LoggerBase() = default;

            virtual void log(logging_level level, const std::string& msg) = 0; 
            
            void set_debug_level(logging_level level); 
            void debug(const std::string& msg);
            void info(const std::string& msg);
            void warn(const std::string& msg);
            void critical(const std::string& msg);
            void error(const std::string& msg);
    };

    class Logger : public LoggerBase
    {
        using LoggerBase::LoggerBase; // Héritage des constructeurs

        void log(logging_level level, const std::string& msg) override; 
    };
}
