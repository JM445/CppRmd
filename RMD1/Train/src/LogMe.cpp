#include <iostream>
#include <string>
#include <LogMe/LogMe.hpp>

namespace LogMe {

    void    Logger::log(logging_level level, const std::string& msg) {
        if (this->_lvl >= level) {
            std::cerr << msg << std::endl;
            if (this->_file.is_open()) {
                this->_file << msg << std::endl;
            }
        }
    }

    void    Logger::set_debug_level(logging_level lvl) {
        _lvl = lvl;
    }

    void    Logger::debug(const std::string& msg) {
        this->log(logging_level::Debug, msg);
    }

    void    Logger::info(const std::string& msg) {
        this->log(logging_level::Info, msg);
    }

    void    Logger::warn(const std::string& msg) {
        this->log(logging_level::Warning, msg);
    }

    void    Logger::error(const std::string& msg) {
        this->log(logging_level::Error, msg);
    }

    void    Logger::critical(const std::string& msg) {
        this->log(logging_level::Critical, msg);
    }


    // PART 2

    namespace {
        auto default_logger = Logger{logging_level::Warning, "default.log"};
    }

    void set_debug_level(logging_level level) {
        default_logger.set_debug_level(level);
    }

    void debug(const std::string& msg) {
        default_logger.debug(msg);
    }

    void info(const std::string& msg) {
        default_logger.info(msg);
    }

    void warn(const std::string& msg) {
        default_logger.warn(msg);
    }

    void critical(const std::string& msg) {
        default_logger.critical(msg);
    }

    void error(const std::string& msg) {
        default_logger.error(msg);
    }
}
