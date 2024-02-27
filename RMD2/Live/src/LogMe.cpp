#include <LogMe/LogMe.hpp>
#include <iostream>

namespace LogMe {

    //
    // Part 1
    //

    LoggerBase::LoggerBase(logging_level lvl) : _lvl(lvl){}

    LoggerBase::LoggerBase() : _lvl(Info) {}

    logging_level LoggerBase::get_level() const { return _lvl; }

    void LoggerBase::chain(std::shared_ptr<LoggerBase> elem) {
        if (_next) {
            _next->chain(elem);
        } else {
            _next = elem;
        }
    }

    FileLogger::FileLogger(const std::string &file, logging_level lvl) : LoggerBase(lvl), _stream{file} {}

    void FileLogger::log(logging_level level, const std::string &msg) {
        if (get_level() >= level) {
            if (_stream.is_open()) {
                _stream << msg << std::endl;
                return;
            }
            if (_next) {
                _next->log(Critical, "Cannot write to file");
            }
        }
        if (_next) {
            _next->log(level, msg);
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

}
