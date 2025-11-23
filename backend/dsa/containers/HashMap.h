#ifndef HASHMAP_H
#define HASHMAP_H

#include <vector>
#include "Pair.h"
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
    //should I use dynamic array here?
     
    Pair<Key, Value>* buckets;
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
};

#include "HashMap.cpp" // template implementation

#endif
