#include <LogMe/LogMe.hpp>

int main() {

   {
   LogMe::StreamLogger mylogger("stream.log");

   mylogger << LogMe::Warn
            << "Ceci est un message de warning.\n";
   mylogger << LogMe::Debug
            << "Ceci est un message de debug.\n"
            << LogMe::Critical
            << "Mais ceci est critique.\n";
   }
}