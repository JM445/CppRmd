#ifndef LOGME_H_
#define LOGME_H_
#include <string>
#include <fstream>
#include <memory>

namespace LogMe {
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warning  = 30,
        Info     = 40,
        Debug    = 50
    };

    class LoggerBase {
        private:
            logging_level               _lvl;

        protected:
            std::shared_ptr<LoggerBase> _next;

        public:
            virtual void log(logging_level level, const std::string& msg) = 0;
            logging_level get_level();
            void chain(std::shared_ptr<LoggerBase> elem);

        public:
            LoggerBase();
            LoggerBase(logging_level _lvl);

    };

    class FileLogger : public LoggerBase {
            std::ofstream _stream;

        public:
            virtual void log(logging_level level, const std::string& msg);

        public:
            FileLogger(const std::string& file);
            FileLogger(const std::string& file, logging_level lvl);
    };

    class ErrorLogger : public FileLogger {
        public:
            virtual void log(logging_level lvl, const std::string& msg) override;

        public:
            ErrorLogger(const std::string& file);
    };

    class CerrLogger : public LoggerBase {
        public:
            virtual void log(logging_level lvl, const std::string& msg) override;

        public:
            CerrLogger(logging_level lvl);
    };

    class CriticalLogger : public FileLogger {
        public:
            virtual void log(logging_level lvl, const std::string& msg) override;

        public:
            CriticalLogger(const std::string& file);
    };


    // Day 2

    class StreamLogger {
        std::shared_ptr<LoggerBase>      _logger;
        logging_level   _lvl;

        public:
            StreamLogger(std::shared_ptr<LoggerBase> logger);
            StreamLogger(const std::string& path);

        public:
            friend StreamLogger& operator << (StreamLogger& logger, logging_level lvl);
            friend StreamLogger& operator << (StreamLogger& logger, const std::string& msg);

    };
}

#endif // LOGME_H_
