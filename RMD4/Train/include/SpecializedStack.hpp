#ifndef SPECIALIZEDSTACK_H_
#define SPECIALIZEDSTACK_H_
#include <iostream>
#include <memory>

template <>
class Stack<bool> {

    struct Node {
        uint data;
        uint size;
        std::unique_ptr<Node> next;

        Node(uint d, std::unique_ptr<Node>& n) : data{d}, size{1}, next{std::move(n)} {}
    };

    std::unique_ptr<Node> _head = nullptr;

    public: // CTOR - DTOR
        Stack() = default;
        ~Stack() = default;

    public: // Methods
        bool           pop() {
            if (!_head) {
                throw std::out_of_range("Stack is empty");
            }

            uint data = _head->data;
            bool res  = (data & 0x01) > 0;
            _head->size--;
            _head->data >>= 1;
            if (_head->size <= 0) {
                _head = std::move(_head->next);
                std::cout << "Deleted element" << std::endl;
            }
            return res;
        }

        void        push(bool elem) {
            if (_head && _head->size < sizeof(uint) * 8) {
                _head->data <<= 1;
                _head->data |= elem;
                _head->size ++;
            } else {
                std::cout << "Created new element" << std::endl;
                _head = std::make_unique<Node>(elem, _head);
            }
        }

        bool    top() const {
            if (!_head) throw std::out_of_range("Stack is empty");
            return  _head->data & 0x1;
        }

        friend std::ostream& operator <<(std::ostream& os, const Stack<bool> &st) {
            // "[1, 2, 3] []"
            os << "[";
            auto head = st._head.get();
            while (head) {
                auto data = head->data;
                for (uint i = 0; i < head->size; i++) {
                    os << (((data & 0x1) == 0) ? "False" : "True");
                    data >>= 1;
                    if (i < head->size - 1)
                        os << ", ";
                }
                if (head->next) {
                    os << ", ";
                }
                head = head->next.get();
            }
            os << "]";
            return os;
        }
};

#endif // SPECIALIZEDSTACK_H_
