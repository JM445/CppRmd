#include <LogMe/LogMe.hpp>

void B();
void C();

int main()
{
    B();
    C();
    LogMe::set_debug_level(LogMe::Debug);
    B();
    C();
}

