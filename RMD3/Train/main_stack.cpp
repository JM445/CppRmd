#include <GenericStack.hpp>

#include <iostream>

int main() {
    Stack stack = Stack<int>();

    std::cout << stack << std::endl;

    stack.push(5);
    stack.push(10);
    stack.push(8);
    stack.push(4);
    stack.push(2);
    stack.push(12);

    std::cout << "Stack top:" << stack.top() << std::endl;
    stack.pop();

    std::cout << "Stack after pop:" << stack << std::endl;
}
