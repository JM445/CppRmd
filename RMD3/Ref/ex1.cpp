#include <LogMe/LogMe.hpp>

int main() {
   LogMe::StreamLogger mylogger("stream.log");

   mylogger << LogMe::Warn
            << "Le résultat du programme: "
            << 404
            << "\n";
}