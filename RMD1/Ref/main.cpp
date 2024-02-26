#include <LogMe/LogMe.hpp>

int main() {


    // Part 2
    {
        LogMe::info("Le programme a démarré.\n");
        {
            LogMe::Logger l;
            l.warn("Loggé par un autre logger.\n"); 
        }
        LogMe::info("Done!\n");
    }

    // Part 3
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