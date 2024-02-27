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
        const logging_level _lvl  = logging_level::Info;

    protected:
        std::shared_ptr<LoggerBase> _next;

    public:
        virtual void log(logging_level level, const std::string& msg) = 0;
        void chain(std::shared_ptr<LoggerBase> logger);
        logging_level get_level() const;

    public:
        LoggerBase(logging_level lvl);
        LoggerBase();
    };

    class FileLogger : public LoggerBase {
        std::ofstream _stream;

    public:
        virtual void log(logging_level level, const std::string& msg);

    public:
        FileLogger(const std::string& file, logging_level lvl = Info);
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


}

#endif // LOGME_H_
