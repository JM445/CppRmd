#include <LogMe/LogMe.hpp>
#include <memory>

using namespace LogMe;

int main(int argc, char *argv[]) {
    auto root = std::make_shared<CriticalLogger>("critical.log");
    auto stream  = std::make_shared<StreamLogger>(root);

    root->chain(std::make_shared<ErrorLogger>("log.log"));
    root->chain(std::make_shared<FileLogger>("log.log", LogMe::Warning));
    root->chain(std::make_shared<CerrLogger>(LogMe::Debug));

    root->log(LogMe::Critical, "This is a critical error");
    root->log(LogMe::Error, "This is an error");
    root->log(LogMe::Warning, "This is a warning");
    root->log(LogMe::Info, "This is an info");

    *stream << LogMe::Debug << "This was logged with a stream syntax";

    return 0;
}
