#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <iostream>
#include <string>
#include <stdexcept>

// Singly Linked List Node
template <typename T>
struct ListNode {
    T data;
    ListNode<T>* next;

    ListNode(const T& value) : data(value), next(nullptr) {}
};

// LinkedList Class
template <typename T>
class LinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int length;

public:
    // Constructor / Destructor
    LinkedList();
    ~LinkedList();

    // Copy Constructor & Assignment (Rule of Five)
    LinkedList(const LinkedList& other);
    LinkedList& operator=(const LinkedList& other);
    LinkedList(LinkedList&& other) noexcept;
    LinkedList& operator=(LinkedList&& other) noexcept;

    // Core Operations
    void append(const T& value);
    void prepend(const T& value);
    bool remove(const T& value);
    T removeHead();
    T removeTail();
    bool contains(const T& value) const;
    void clear();

    // Access Operations
    T& at(int index);
    const T& at(int index) const;
    T& operator[](int index);
    const T& operator[](int index) const;

    // Accessors
    int size() const;
    bool isEmpty() const;
    ListNode<T>* getHead() const;
    ListNode<T>* getTail() const;

    // Debug
    void print() const;
};

// Implementation
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), tail(nullptr), length(0) {}

template <typename T>
LinkedList<T>::~LinkedList() {
    clear();
}

// Copy Constructor
template <typename T>
LinkedList<T>::LinkedList(const LinkedList& other) : head(nullptr), tail(nullptr), length(0) {
    ListNode<T>* curr = other.head;
    while (curr) {
        append(curr->data);
        curr = curr->next;
    }
}

// Copy Assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList& other) {
    if (this != &other) {
        clear();
        ListNode<T>* curr = other.head;
        while (curr) {
            append(curr->data);
            curr = curr->next;
        }
    }
    return *this;
}

// Move Constructor
template <typename T>
LinkedList<T>::LinkedList(LinkedList&& other) noexcept 
    : head(other.head), tail(other.tail), length(other.length) {
    other.head = nullptr;
    other.tail = nullptr;
    other.length = 0;
}

// Move Assignment
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList&& other) noexcept {
    if (this != &other) {
        clear();
        head = other.head;
        tail = other.tail;
        length = other.length;
        
        other.head = nullptr;
        other.tail = nullptr;
        other.length = 0;
    }
    return *this;
}

// Append,O(1) with tail pointer
template <typename T>
void LinkedList<T>::append(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);

    if (!head) {
        head = tail = newNode;
    } else {
        tail->next = newNode;
        tail = newNode;
    }
    length++;
}

// Prepend,O(1) insertion at front
template <typename T>
void LinkedList<T>::prepend(const T& value) {
    ListNode<T>* newNode = new ListNode<T>(value);
    
    if (!head) {
        head = tail = newNode;
    } else {
        newNode->next = head;
        head = newNode;
    }
    length++;
}

// Remove by value,O(n)
template <typename T>
bool LinkedList<T>::remove(const T& value) {
    if (!head)
        return false;

    // Remove head node
    if (head->data == value) {
        ListNode<T>* temp = head;
        head = head->next;
        
        if (!head) // List is now empty
            tail = nullptr;
        
        delete temp;
        length--;
        return true;
    }

    // Remove inner/tail node
    ListNode<T>* curr = head;
    while (curr->next && curr->next->data != value) {
        curr = curr->next;
    }

    if (!curr->next)
        return false;

    ListNode<T>* temp = curr->next;
    curr->next = temp->next;
    
    if (temp == tail) // Removing tail
        tail = curr;
    
    delete temp;
    length--;
    return true;
}

// Remove head node,O(1), returns the removed value
template <typename T>
T LinkedList<T>::removeHead() {
    if (!head)
        throw std::out_of_range("List is empty");

    T value = head->data;
    ListNode<T>* temp = head;
    head = head->next;
    
    if (!head) // List became empty
        tail = nullptr;
    
    delete temp;
    length--;
    return value;
}

// Remove tail node 
template <typename T>
T LinkedList<T>::removeTail() {
    if (!head)
        throw std::out_of_range("List is empty");
    
    T value = tail->data;
    
    // Single node
    if (head == tail) {
        delete head;
        head = tail = nullptr;
        length--;
        return value;
    }
    
    // Find second to last node
    ListNode<T>* curr = head;
    while (curr->next != tail) {
        curr = curr->next;
    }
    
    delete tail;
    tail = curr;
    tail->next = nullptr;
    length--;
    return value;
}

// Check if list contains value,O(n)
template <typename T>
bool LinkedList<T>::contains(const T& value) const {
    ListNode<T>* curr = head;
    while (curr) {
        if (curr->data == value)
            return true;
        curr = curr->next;
    }
    return false;
}

// Clear all nodes,O(n)
template <typename T>
void LinkedList<T>::clear() {
    ListNode<T>* curr = head;

    while (curr) {
        ListNode<T>* temp = curr;
        curr = curr->next;
        delete temp;
    }

    head = nullptr;
    tail = nullptr;
    length = 0;
}

// Access with bounds checking,O(n)
template <typename T>
T& LinkedList<T>::at(int index) {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of bounds");
    
    ListNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
const T& LinkedList<T>::at(int index) const {
    if (index < 0 || index >= length)
        throw std::out_of_range("Index out of bounds");
    
    ListNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

// Operator[] without bounds checking,O(n)
template <typename T>
T& LinkedList<T>::operator[](int index) {
    ListNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

template <typename T>
const T& LinkedList<T>::operator[](int index) const {
    ListNode<T>* curr = head;
    for (int i = 0; i < index; i++) {
        curr = curr->next;
    }
    return curr->data;
}

// Get size,O(1)
template <typename T>
int LinkedList<T>::size() const {
    return length;
}

// Check if empty, O(1)
template <typename T>
bool LinkedList<T>::isEmpty() const {
    return length == 0;
}

// Get head pointer,O(1)
template <typename T>
ListNode<T>* LinkedList<T>::getHead() const {
    return head;
}

// Get tail pointer,O(1)
template <typename T>
ListNode<T>* LinkedList<T>::getTail() const {
    return tail;
}

// Print list,O(n)
template <typename T>
void LinkedList<T>::print() const {
    ListNode<T>* curr = head;
    while (curr) {
        std::cout << curr->data;
        if (curr->next)
            std::cout << " -> ";
        curr = curr->next;
    }
    std::cout << std::endl;
}

#endif 