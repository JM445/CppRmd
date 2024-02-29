#ifndef GENERICSTACK_H_
#define GENERICSTACK_H_

#include <memory>
#include <iostream>

template <class T>
class Stack {

    struct Node {
        T data;
        std::unique_ptr<Node> next;

        Node(T d, std::unique_ptr<Node>& n) : data{d}, next{std::move(n)} {}
    };

    std::unique_ptr<Node> _head = nullptr;

    public: // CTOR - DTOR
        Stack() = default;
        ~Stack() = default;

    public: // Methods
        T           pop() {
            if (!_head) {
                throw std::out_of_range("Stack is empty");
            }

            T data = _head->data;
            _head = std::move(_head->next);
            return data;
        }

        void        push(const T& elem) {
            _head = std::make_unique<Node>(elem, _head);
        }

        const T&    top() const {
            if (!_head) throw std::out_of_range("Stack is empty");
            return  _head->data;
        }

        T&          top() {
            if (!_head) throw std::out_of_range("Stack is empty");
            return  _head->data;
        }

        friend std::ostream& operator <<(std::ostream& os, const Stack<T> &st) {
            // "[1, 2, 3] []"
            os << "[";
            auto head = st._head.get();
            while (head) {
                os << head->data;
                if (head->next) {
                    os << ", ";
                } 
                head = head->next.get();
            }
            os << "]";
            return os;
        }
};

#endif // GENERICSTACK_H_
