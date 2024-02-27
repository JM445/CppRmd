#ifndef LOGME_H_
#define LOGME_H_
#include <string>
#include <fstream>

namespace LogMe {
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warning  = 30,
        Info     = 40,
        Debug    = 50
    };

    class Logger {
        logging_level _lvl  = logging_level::Info;
        std::ofstream _file;

        void log(logging_level level, const std::string& msg); // Privée

    public:
        void set_debug_level(logging_level level);
        void debug(const std::string& msg);
        void info(const std::string& msg);
        void warn(const std::string& msg);
        void critical(const std::string& msg);
        void error(const std::string& msg);

    public:
        Logger() = default;
        Logger(logging_level lvl, const char* filename = nullptr) : _lvl(lvl), _file(filename) {}

    };

    void set_debug_level(logging_level level);
    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void critical(const std::string& msg);
    void error(const std::string& msg);


    // Day 2
}

#endif // LOGME_H_
