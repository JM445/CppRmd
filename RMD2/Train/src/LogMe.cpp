#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe {

    //
    // Part 1
    //

    LoggerBase::LoggerBase() : _lvl(Info) {}

    LoggerBase::LoggerBase(logging_level lvl) : _lvl{lvl}
    {}

    logging_level LoggerBase::get_level() {
        return _lvl;
    }

    void LoggerBase::chain(std::shared_ptr<LoggerBase> elem) {
        if (_next) {
            _next->chain(elem);
        } else {
            _next = elem;
        }
    }

    /////////////////////////////////////////////

    FileLogger::FileLogger(const std::string& file) : LoggerBase{Warning}, _stream{file} {}

    FileLogger::FileLogger(const std::string& file, logging_level lvl) : LoggerBase{lvl}, _stream{file} {}

    void FileLogger::log(logging_level level, const std::string& msg) {
        if (_stream.is_open()) {
            if (get_level() >= level) {
                _stream << msg << std::endl;
            } else if (_next){
                _next->log(level, msg);
            }
        } else {
            throw std::runtime_error("Unable to log to file\n");
        }
    }

    ////////////////////////////////////////////

    ErrorLogger::ErrorLogger(const std::string& file) : FileLogger{file, Error} {}

    void ErrorLogger::log(logging_level lvl, const std::string& msg) {
        if (lvl <= get_level()) {
            std::string newMsg = "[Error Log] " + msg;
            FileLogger::log(lvl, newMsg);
        } else if (_next) {
            _next->log(lvl, msg);
        }
    }

    ////////////////////////////////////////////

    CerrLogger::CerrLogger(logging_level lvl) : LoggerBase{lvl} {}

    void CerrLogger::log(logging_level lvl, const std::string& msg) {
        if (lvl <= get_level())
            std::cerr << "[Cerr Log] " + msg << std::endl;
        else if (_next)
            _next->log(lvl, msg);
    }

    ////////////////////////////////////////////

    CriticalLogger::CriticalLogger(const std::string& file) : FileLogger{file, Critical} {}

    void CriticalLogger::log(logging_level lvl, const std::string& msg) {
        auto newMsg = "[Critical Log] " + msg;
        if (lvl <= get_level())
            FileLogger::log(lvl, newMsg);
        else
            FileLogger::log(lvl, msg);
    }

    StreamLogger::StreamLogger(const std::string& path) : _logger{std::make_shared<FileLogger>(path)}
    {}

    StreamLogger::StreamLogger(std::shared_ptr<LoggerBase> logger) : _logger{logger} {}


    StreamLogger& operator << (StreamLogger& logger, logging_level lvl) {
        logger._lvl = lvl;
        return logger;
    }

    StreamLogger& operator << (StreamLogger& logger, const std::string& msg) {
        logger._logger->log(logger._lvl, msg);
        return logger;
    }
}
