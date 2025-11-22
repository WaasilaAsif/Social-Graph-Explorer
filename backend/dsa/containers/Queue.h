#ifndef QUEUE_H
#define QUEUE_H

#include "LinkedList.h"
#include <stdexcept>

template <typename T>
class Queue {
private:
    LinkedList<T> list;

public:
    Queue() = default;
    ~Queue() = default;

    // Enable copy/move semantics
    Queue(const Queue&) = default;
    Queue& operator=(const Queue&) = default;
    Queue(Queue&&) = default;
    Queue& operator=(Queue&&) = default;

    // Add element to the back - O(1)
    void enqueue(const T& value) {
        list.append(value);
    }

    // Remove element from front - O(1)
    T dequeue() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        
        return list.removeHead(); // removeHead() now returns the value directly
    }

    // Peek front element without removing
    T& front() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return list.getHead()->data;
    }

    const T& front() const {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return list.getHead()->data;
    }

    // Peek back element
    T& back() {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return list.getTail()->data;
    }

    const T& back() const {
        if (isEmpty())
            throw std::out_of_range("Queue is empty");
        return list.getTail()->data;
    }

    // Check if queue is empty
    bool isEmpty() const {
        return list.isEmpty();
    }

    // Get queue size
    int size() const {
        return list.size();
    }

    // Clear all elements
    void clear() {
        list.clear();
    }

    void print() const {
        std::cout << "Front -> ";
        list.print();
    }
};

#endif 