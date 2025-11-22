#ifndef STACK_H
#define STACK_H

#include "LinkedList.h"
#include <stdexcept>
#include <iostream>

template <typename T>
class Stack {
private:
    LinkedList<T> list;

public:
    Stack() = default;
    ~Stack() = default;

    // Copy / Move semantics
    Stack(const Stack&) = default;
    Stack& operator=(const Stack&) = default;
    Stack(Stack&&) = default;
    Stack& operator=(Stack&&) = default;

    // Push element onto the stack - O(1)
    void push(const T& value) {
        list.prepend(value); // push to front
    }

    // Pop element from the stack - O(1)
    T pop() {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return list.removeHead();
    }

    // Peek at the top element
    T& top() {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return list.getHead()->data;
    }

    const T& top() const {
        if (isEmpty())
            throw std::out_of_range("Stack is empty");
        return list.getHead()->data;
    }

    // Check if stack is empty
    bool isEmpty() const {
        return list.isEmpty();
    }

    // Get number of elements in stack
    int size() const {
        return list.size();
    }

    // Clear all elements
    void clear() {
        list.clear();
    }

    void print() const {
        std::cout << "Top -> ";
        list.print();
    }
};

#endif 
