#pragma once
#include "DynamicArray.h"
#include "../utils/Pair.h"
#include <string>

template <typename K, typename V>
class HashMap {
private:
    int numBuckets;
    DynamicArray<Pair<K,V>>* buckets;  
    
    int hash(const K& key) {
        return hashHelper(key);
    }
    
    // Helper for int keys
    int hashHelper(const int& key) {
        return key % numBuckets;
    }
    
    // Helper for string keys
    int hashHelper(const std::string& key) {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % numBuckets;
    }

public:
    HashMap(int bucketsCount = 10) {
        numBuckets = bucketsCount;
        buckets = new DynamicArray<Pair<K,V>>[numBuckets];
    }

    ~HashMap() {
        delete[] buckets;
    }

    void put(const K& key, const V& value) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        // update if key exists
        for (int i=0; i<bucket.size(); i++) {
            if (bucket.get(i).first == key) {
                bucket.get(i).second = value;
                return;
            }
        }

        // otherwise insert new
        bucket.push_back(Pair<K,V>(key,value));
    }

    bool contains(const K& key) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return true;

        return false;
    }

    V get(const K& key) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return bucket.get(i).second;

        throw std::out_of_range("Key not found");
    }
};