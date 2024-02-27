#include <LogMe/LogMe.hpp>
#include <iostream>
#include <cassert>

#include "LogMe/utilities.hpp"

namespace LogMe
{

    BoundedLogger::BoundedLogger(logging_level max_lvl)
        : m_level_upper{max_lvl}
        , m_next{}
    {
    }

    void BoundedLogger::verify_no_loop(const std::shared_ptr<BoundedLogger>& elem) const{

          std::shared_ptr<BoundedLogger> next = elem;
          while (next){
              if (next.get() == this)
                  throw std::runtime_error("BoundedLogger::set_succ(): Loop detected!\n");
            next = next->m_next;
          }
    }

    void BoundedLogger::set_succ(std::shared_ptr<BoundedLogger> next_elem) {
        // First, check if this is reachable from next_elem
        verify_no_loop(next_elem);

        m_next = next_elem;
    }

    void BoundedLogger::append_to_chain(std::shared_ptr<BoundedLogger> next_elem) {
        if (m_next)
            m_next->append_to_chain(next_elem);
        else
            set_succ(next_elem);
    }

    void CerrLogger::log(logging_level level, const std::any& msg) {

        if (const auto* msg_ptr = std::any_cast<std::string_view>(&msg);
            msg_ptr && (level <= get_log_lvl())){
            std::cerr << *msg_ptr;
            return; // Done
        }

        if (m_next)
            m_next->log(level, msg);
        // Here msg can be dropped
        // This is either ok or should entail an error
        // depending on what is desired
    }


  FileLogger::FileLogger(logging_level max_lvl, std::shared_ptr<std::ofstream> osf)
      : BoundedLogger(max_lvl)
      , m_os{osf}
    {
        if (osf){
            if (m_os->is_open())
              m_os_ptr = m_os.get();
            else
              throw std::runtime_error(
                  "FileLogger::FileLogger(): Could not open file!\n");
        } else
            m_os_ptr = &std::cerr;

    }
  FileLogger::FileLogger(logging_level max_lvl, const std::string& path)
        : FileLogger(max_lvl, (path == "") ? std::make_shared<std::ofstream>() : std::make_shared<std::ofstream>(path))
    {
    }

    void FileLogger::log(logging_level level, const std::any& msg)
    {
        if (m_os_ptr->bad()){
            if (m_os){
              if (m_os->is_open())
                  m_os->close();
              m_os.reset();
              m_os_ptr = &std::cerr;
              log(level, "Write to file error, switch to cerr\n");
            } else {
              throw std::runtime_error("Logger::log(): Failed on cerr.\n");
            }
        }

        if (auto* msg_ptr = std::any_cast<std::string_view>(&msg);
            (msg_ptr && (level <= get_log_lvl()))){

            (*m_os_ptr) << *msg_ptr;
            return; // Request handled
        }

        if (m_next)
            m_next->log(level, msg);
    }

    ErrorLogger::ErrorLogger(std::shared_ptr<std::ofstream> osf)
        : FileLogger(Error, osf)
    {
    }

    ErrorLogger::ErrorLogger(const std::string& path)
        : FileLogger(Error, path)
    {
    }

    void ErrorLogger::log(logging_level level, const std::any& msg) {
        // If it is an error we want to prepend "ERROR" to the msg
        // and then log it normally
        if (auto* msg_ptr = std::any_cast<std::string_view>(&msg)){
            if (level <= get_log_lvl()){
                return FileLogger::log(level, std::string_view("ERROR: " + std::string(*msg_ptr)));
            } else
                return FileLogger::log(level, msg);
        }

        if (m_next)
            m_next->log(level, msg);
    }

    ErrorCodeLogger::ErrorCodeLogger(std::shared_ptr<std::ofstream> osf)
        : FileLogger(Error, osf)
    {
    }

    ErrorCodeLogger::ErrorCodeLogger(const std::string& path)
        : FileLogger(Error, path)
    {
    }

    void ErrorCodeLogger::log(logging_level level, const std::any& msg) {
      // If it is an error we want to prepend "ERROR" to the msg
      // and then log it normally
      if (auto* msg_ptr = std::any_cast<int>(&msg)){
          // It is important to create a variable here and not use it directly
          // in the constructor, as it becomes a "dangling view" otherwise
          std::string new_message = "Received error-code " + std::to_string(*msg_ptr) + '\n';
          return FileLogger::log(level, std::string_view(new_message) );
      }

      if (m_next)
        m_next->log(level, msg);
    }


    CriticalLogger::CriticalLogger(std::shared_ptr<std::ofstream> osf)
        : FileLogger(Critical, osf)
    {
    }

    CriticalLogger::CriticalLogger(const std::string& path)
        : FileLogger(Critical, path)
    {
    }

    void CriticalLogger::log(logging_level level, const std::any& msg) {
        if (auto* msg_ptr = std::any_cast<std::string_view>(&msg);
            msg_ptr && (level <= get_log_lvl())){
                logging_utilities::safe_data();
                FileLogger::log(level, *msg_ptr);
                assert(false && "Critical Error logged -> Abort for debug;\n");
                return;
        }

        if (m_next)
            m_next->log(level, msg);
    }

    StringViewConverter::StringViewConverter()
        : BoundedLogger(Critical)
    {
    }

    void StringViewConverter::log(logging_level level, const std::any &msg){

        if (const auto* p = std::any_cast<std::string>(&msg))
            return m_next->log(level, std::string_view(*p));
        else if (const auto* p = std::any_cast<char*>(&msg))
          return m_next->log(level, std::string_view(*p));
        else if (const auto* p = std::any_cast<const char*>(&msg))
          return m_next->log(level, std::string_view(*p));
        else
          return m_next->log(level, msg);
    }



    // As before - me or less

    StreamLogger::StreamLogger(std::shared_ptr<BoundedLogger> logger_chain)
        : m_logger{logger_chain}
    {
    }

    StreamLogger& operator<< (StreamLogger& s, logging_level level)
    {
        s.m_lvl = level;
        return s;
    }

    StreamLogger& operator<< (StreamLogger& s, const std::any& msg)
    {
        if (s.m_logger)
            s.m_logger->log(s.m_lvl, msg);
        // Again, messages ca be dropped
        return s;
    }
}