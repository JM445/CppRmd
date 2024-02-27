#include <iostream>

#include <LogMe/LogMe.hpp>
#include <chrono>

class MyCustomLogger : public LogMe::LoggerBase
{
  void format(std::ostream& os, LogMe::logging_level level, const std::string& msg) {
    auto time = std::chrono::system_clock::now();
    auto today_time = std::chrono::system_clock::to_time_t(time);
    const char* lvlstr = nullptr;
    switch (level) {
      case LogMe::Critical: lvlstr = "Critical"; break;
      case LogMe::Error   : lvlstr = "Error   "; break;
      case LogMe::Warn    : lvlstr = "Warn    "; break;
      case LogMe::Info    : lvlstr = "Info    "; break;
      case LogMe::Debug   : lvlstr = "Debug   "; break;
    }
    char timeString[std::size("yyyy-mm-dd hh:mm:ssZ")];
    std::strftime(std::data(timeString), std::size(timeString), "%FT%TZ", std::gmtime(&today_time));
    os << '[' << timeString << "][" << lvlstr << "] " << msg;
  }    

  public:
    void log(LogMe::logging_level level, const std::string& msg) override
    {
      if (level <= m_level)
          format(*m_os_ptr, level, msg);
    }
};

int main() {
  {
    LogMe::Logger l;
    l.warn("Ceci est un message de warning par Logger\n");
  }
  {
    MyCustomLogger l;
    l.warn("Ceci est un message de warning par MyCustomLogger\n");
  }
}