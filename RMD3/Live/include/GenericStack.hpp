#ifndef GENERICSTACK_H_
#define GENERICSTACK_H_

#include <memory>

template <class T>
class Stack {
    std::unique_ptr<???> _head = nullptr;

    public: // CTOR - DTOR
        Stack() = default;
        ~Stack() = default;

    public: // Methods
        T           pop();
        void        push(const T& elem);
        const T&    top() const;
        T&          top();
};

#endif // GENERICSTACK_H_
