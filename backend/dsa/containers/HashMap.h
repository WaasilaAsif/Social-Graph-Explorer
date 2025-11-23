#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
using namespace std;

template<typename Key, typename Value>
class HashMap {
private:
    struct Node {
        Key key;
        Value value;
        Node* next;

        Node(const Key& k, const Value& v) : key(k), value(v), next(nullptr) {}
    };

    vector<Node*> buckets;
    int capacity;
    int size;

    int hash(const Key& key) const;

public:
    HashMap(int cap = 101); // default prime number
    ~HashMap();

    void put(const Key& key, const Value& value);
    bool contains(const Key& key) const;
    Value* get(const Key& key);
    void remove(const Key& key);
    int getSize() const;
    bool isEmpty() const;
    void clear();
    
    // Operator[] for convenient access (returns reference, creates if not exists)
    Value& operator[](const Key& key) {
        if (!contains(key)) {
            put(key, Value());
        }
        return *get(key);
    }
    
    // Iterator-like access for traversal (needed by Trie)
    template<typename Func>
    void forEach(Func func) const {
        for (int i = 0; i < capacity; i++) {
            Node* curr = buckets[i];
            while (curr) {
                func(curr->key, curr->value);
                curr = curr->next;
            }
        }
    }
};

#include "HashMap.cpp" // template implementation

#endif
