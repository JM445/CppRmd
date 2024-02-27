#ifndef GENERICSTACK_H_
#define GENERICSTACK_H_

#include <memory>
#include <iostream>

template <class T>
class Stack {
    struct Node {
        T                       data;
        std::unique_ptr<Node>   next;

        Node(T data, std::unique_ptr<Node>& next) : data{data}, next{std::move(next)} {}
    };

    std::unique_ptr<Node> _head = nullptr;

    public: // CTOR - DTOR
        Stack() = default;
        ~Stack() = default;

    public: // Methods
        T pop() {
            if (!_head) {
                throw std::out_of_range("Stack is empty");
            }

            T data = _head->data;
            _head  = std::move(_head->next);
            return data;
        }

        void push(const T& elem) {
            _head = std::make_unique<Node>(elem, _head);
        }

        const T&    top() const {
            return _head->data;
        }

        T&          top() {
            return _head->data;
        }

        friend std::ostream& operator <<(std::ostream& stream, const Stack<T>& stack) {
            stream << "[";
            auto head = stack._head.get();
            while (head) {
                stream << head->data;
                if (head->next) {
                    stream << ", ";
                }
                head = head->next.get();
            }
            stream << "]";
            return stream;
        }
};

#endif // GENERICSTACK_H_
