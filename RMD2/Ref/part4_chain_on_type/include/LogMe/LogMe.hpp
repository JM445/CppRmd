#pragma once
#include <fstream>
#include <memory>
#include <any>

namespace LogMe
{
    enum logging_level {
        Critical = 10,
        Error    = 20,
        Warn     = 30,
        Info     = 40,
        Debug    = 50
    };

    // Abstract base class
    class BoundedLogger{
        private:
            logging_level m_level_upper;
            void verify_no_loop(const std::shared_ptr<BoundedLogger>& elem) const;
            void set_succ(std::shared_ptr<BoundedLogger> next_elem);

        protected:
          std::shared_ptr<BoundedLogger> m_next;

        public:
            BoundedLogger(logging_level max_lvl = Info);
            virtual ~BoundedLogger() = default;

            void append_to_chain(std::shared_ptr<BoundedLogger> next_elem);


            logging_level get_log_lvl() const {
              return m_level_upper;
            }

            virtual void log(logging_level level, const std::any&) = 0;
    };

    class CerrLogger : public BoundedLogger
    {
        public:
            CerrLogger(logging_level max_lvl = Info) : BoundedLogger(max_lvl) {};
            void log(logging_level level, const std::any& msg) override;
    };

    // This one behaves basically like out old logger
    class FileLogger : public  BoundedLogger
    {
        private:
          std::shared_ptr<std::ofstream> m_os;
          std::ostream* m_os_ptr; // Guaranteed to be never null post ctor

          public:
              FileLogger(logging_level max_lvl = Info, std::shared_ptr<std::ofstream> osf = {});
              FileLogger(logging_level max_lvl = Info, const std::string& path = "");

              void log(logging_level level, const std::any& msg) override;
    };

    class ErrorLogger :  public FileLogger{
        public:
            ErrorLogger(std::shared_ptr<std::ofstream> osf);
            ErrorLogger(const std::string& path);

            void log(logging_level level, const std::any& msg) override;
    };

    class ErrorCodeLogger :  public FileLogger{
    public:
      ErrorCodeLogger(std::shared_ptr<std::ofstream> osf);
      ErrorCodeLogger(const std::string& path);

      void log(logging_level level, const std::any& msg) override;
    };

    class CriticalLogger : public FileLogger{

        public:
            CriticalLogger(std::shared_ptr<std::ofstream> osf);
            CriticalLogger(const std::string& path);

            void log(logging_level level, const std::any& msg) override;
    };

    class StringViewConverter : public BoundedLogger{
      public:
          StringViewConverter();
          void log(logging_level level, const std::any& msg) override;
    };

    // Adapting it to the chain
    class StreamLogger
    {
        std::shared_ptr<BoundedLogger> m_logger;
        logging_level m_lvl = Info;

        public:
            StreamLogger(std::shared_ptr<BoundedLogger> logger_chain);

            friend StreamLogger& operator<< (StreamLogger& s, logging_level level);
            friend StreamLogger& operator<< (StreamLogger& s, const std::any& msg);
    };
}