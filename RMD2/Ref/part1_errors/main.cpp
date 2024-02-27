#include <iostream>

#include <LogMe/LogMe.hpp>

int main() {

  // Uncomment this later
  // ./main 2> /dev/full needs to throw
  // Full error
  {
  auto mylogger = LogMe::StreamLogger();
  try{
      mylogger << LogMe::Warn
               << "Ceci est un message de warning.\n";
      mylogger << LogMe::Debug
               << "Ceci est un message de debug.\n"
               << LogMe::Critical
               << "Mais ceci est critique.\n";
  } catch (std::runtime_error& e) {
    std::cout << "What happened??\n";
    std::cout << e.what();
    std::cout.flush();
  }
  return 0; // We only want to test this part in the end
  }

   // Test regular 1
   {
   auto mylogger = LogMe::StreamLogger("stream.log");

   mylogger << LogMe::Warn
            << "Ceci est un message de warning.\n";
   mylogger << LogMe::Debug
            << "Ceci est un message de debug.\n"
            << LogMe::Critical
            << "Mais ceci est critique.\n";
   }

  // Test regular 2
  {
    auto mylogger = LogMe::StreamLogger();

    mylogger << LogMe::Warn
             << "Ceci est un message de warning.\n";
    mylogger << LogMe::Debug
             << "Ceci est un message de debug.\n"
             << LogMe::Critical
             << "Mais ceci est critique.\n";
  }

  // Test file found
  {
    auto fn = std::string("abrakadabra/mylog.txt");
    try
    {
      LogMe::StreamLogger mylogger(fn);
    }
    catch(std::runtime_error& e)
    {
      std::cout << e.what() << '\n';
    }
  }

}