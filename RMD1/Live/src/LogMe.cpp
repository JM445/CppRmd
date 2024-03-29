#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe {
    void Logger::set_debug_level(logging_level level) {
        _lvl = level;
    }

    void Logger::log(logging_level level, const std::string& msg) {
        if (_lvl >= level) {
            std::cerr << msg << std::endl;
            if (_file.is_open()) {
                _file << msg << std::endl;
            }
        }
    }

    void Logger::debug(const std::string& msg) {
        log(logging_level::Debug, msg);
    }

    void Logger::info(const std::string& msg) {
        log(logging_level::Info, msg);
    }

    void Logger::warn(const std::string& msg) {
        log(logging_level::Warning, msg);
    }

    void Logger::critical(const std::string& msg) {
        log(logging_level::Critical, msg);
    }

    void Logger::error(const std::string& msg) {
        log(logging_level::Error, msg);
    }


    namespace {
        auto default_logger = Logger();
    }


    void set_debug_level(logging_level level) {
        default_logger.set_debug_level(level);
    }

    void debug(const std::string& msg);
    void info(const std::string& msg);
    void warn(const std::string& msg);
    void critical(const std::string& msg);
    void error(const std::string& msg);
}