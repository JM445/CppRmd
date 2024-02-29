#include <GenericStack.hpp>

#include <iostream>
#include <string>

struct A {
    int a;
    float b;
    std::string s;

    A() : a{1}, b{2.5}, s{"42"} { std::cout << "A (Default)" << std::endl; }
    A(const A& other) : a{other.a}, b{other.b}, s{other.s} {
        std::cout << "A (Copy)" << std::endl;
    }

    A operator=(const A& other) {
        return A(other);
    }
};

int main() {
    A a = A{};
    A b = a;
    A c;

    c = a;
}
