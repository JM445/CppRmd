#include <LogMe/LogMeContainer.hpp>
#include <vector>
#include <list>

int main() {
   LogMe::StreamLogger mylogger("stream.log");

   {
      auto vec = std::vector{1, 2, 3};
      mylogger << "Vec=" << vec << "\n";
   }
   {
      auto list = std::list{1, 2, 3};
      mylogger << "List=" << list << "\n";
   }
}