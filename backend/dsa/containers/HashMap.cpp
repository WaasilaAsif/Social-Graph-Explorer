#include "HashMap.h"
#include <stdexcept>

template<typename Key, typename Value>
int HashMap<Key, Value>::hash(const Key& key) const {
    // Simple hash: works for char, int, string (string will use std::hash)
    return std::hash<Key>{}(key) % capacity;
}


template<typename Key, typename Value>
HashMap<Key, Value>::HashMap(int cap) : capacity(cap), size(0) {
    buckets.resize(capacity, nullptr);
}


template<typename Key, typename Value>
HashMap<Key, Value>::~HashMap() {
    for (int i = 0; i < capacity; i++) {
        Node* curr = buckets[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
    }
}


template<typename Key, typename Value>
void HashMap<Key, Value>::put(const Key& key, const Value& value) {
    int idx = hash(key);
    Node* curr = buckets[idx];

    while (curr) {
        if (curr->key == key) {
            curr->value = value; // update
            return;
        }
        curr = curr->next;
    }

    Node* newNode = new Node(key, value);
    newNode->next = buckets[idx];
    buckets[idx] = newNode;
    size++;
}


template<typename Key, typename Value>
bool HashMap<Key, Value>::contains(const Key& key) const {
    int idx = hash(key);
    Node* curr = buckets[idx];

    while (curr) {
        if (curr->key == key)
            return true;
        curr = curr->next;
    }
    return false;
}


template<typename Key, typename Value>
Value* HashMap<Key, Value>::get(const Key& key) {
    int idx = hash(key);
    Node* curr = buckets[idx];

    while (curr) {
        if (curr->key == key)
            return &curr->value;
        curr = curr->next;
    }
    return nullptr; // not found
}


template<typename Key, typename Value>
void HashMap<Key, Value>::remove(const Key& key) {
    int idx = hash(key);
    Node* curr = buckets[idx];
    Node* prev = nullptr;

    while (curr) {
        if (curr->key == key) {
            if (prev)
                prev->next = curr->next;
            else
                buckets[idx] = curr->next;
            delete curr;
            size--;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}


template<typename Key, typename Value>
int HashMap<Key, Value>::getSize() const {
    return size;
}

template<typename Key, typename Value>
bool HashMap<Key, Value>::isEmpty() const {
    return size == 0;
}

template<typename Key, typename Value>
void HashMap<Key, Value>::clear() {
    for (int i = 0; i < capacity; i++) {
        Node* curr = buckets[i];
        while (curr) {
            Node* temp = curr;
            curr = curr->next;
            delete temp;
        }
        buckets[i] = nullptr;
    }
    size = 0;
}
