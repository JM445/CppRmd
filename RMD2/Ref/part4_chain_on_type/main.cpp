#include <iostream>

#include <LogMe/LogMe.hpp>

int main() {

  // Lets create a chain
  // Critical errors have their own file
  // The others share one
  auto logfile = std::make_shared<std::ofstream>("mylog.txt");
  auto root = std::make_shared<LogMe::StringViewConverter>();
  root->append_to_chain( std::make_shared<LogMe::CriticalLogger>("critlog.txt"));

  root->append_to_chain(std::make_shared<LogMe::ErrorLogger>(logfile));
  root->append_to_chain(std::make_shared<LogMe::ErrorCodeLogger>(logfile));
  root->append_to_chain(std::make_shared<LogMe::FileLogger>(LogMe::Info, logfile));
  root->append_to_chain(std::make_shared<LogMe::CerrLogger>(LogMe::Debug));

  root->log(LogMe::Error, "This is an error.\n");
  root->log(LogMe::Info, "This is an info.\n");
  root->log(LogMe::Debug, std::string("This is a debug msg.\n")); // To test conversion
  root->log(LogMe::Error, 404);

  // root->log(LogMe::Critical, 403);
  // root->log(LogMe::Critical, "This will halt in dbg!\n");

  // Also works for streaming

  auto s_logger = LogMe::StreamLogger(root);

  s_logger << LogMe::Debug << std::string("Another dbg msg.\n");
  s_logger << LogMe::Info << std::string("And another info msg.\n");

  return 0;
}