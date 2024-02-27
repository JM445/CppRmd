#include <LogMe/LogMe.hpp>

using namespace LogMe;

int main(int argc, char *argv[]) {
    set_debug_level(LogMe::Critical);

    Logger log1 = LogMe::Logger{};
//    Logger log2 = LogMe::Logger{LogMe::logging_level::Error, "logfile.log"};

//    warn("This is logged by the default logger");

    log1.info("Hello World !");
    log1.debug("This won't be logged");
    log1.error("But this will");

//    log2.critical("This will also be logged to a file");
//    log2.info("This won't");
    return 0;
}
