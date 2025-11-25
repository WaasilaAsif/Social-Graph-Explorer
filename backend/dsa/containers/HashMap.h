#pragma once
#include "DynamicArray.h"
#include "../utils/Pair.h"
#include <string>

template <typename K, typename V>
class HashMap {
private:
    int numBuckets;
    DynamicArray<Pair<K,V>>* buckets;  
    int entryCount;

    int hash(const K& key) const {
        return hashHelper(key);
    }
    
    // Helper for int keys
    int hashHelper(const int& key) const {
        return key % numBuckets;
    }
    
    // Helper for string keys
    int hashHelper(const std::string& key) const {
        int hash = 0;
        for (char c : key) hash += c;
        return hash % numBuckets;
    }

public:
    HashMap(int bucketsCount = 10) {
        numBuckets = bucketsCount;
        buckets = new DynamicArray<Pair<K,V>>[numBuckets];
        entryCount = 0;
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
        entryCount++;
    }

    bool contains(const K& key) const {
        int index = hash(key);
        const DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return true;

        return false;
    }

    V& get(const K& key) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return bucket.get(i).second;

        throw std::out_of_range("Key not found");
    }

    // Const overload of get()
    const V& get(const K& key) const {
        int index = hash(key);
        const DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return bucket.get(i).second;

        throw std::out_of_range("Key not found");
    }

    // Operator[] for convenient access (creates entry if doesn't exist)
    V& operator[](const K& key) {
        if (!contains(key)) {
            put(key, V()); // Insert with default-constructed value
        }
        return get(key);
    }

    // forEach: iterate over all key-value pairs
    // Callback signature: void callback(const K& key, V& value)
    template<typename Func>
    void forEach(Func callback) {
        for (int i = 0; i < numBuckets; i++) {
            DynamicArray<Pair<K,V>>& bucket = buckets[i];
            for (int j = 0; j < bucket.size(); j++) {
                callback(bucket.get(j).first, bucket.get(j).second);
            }
        }
    }
    //aman added
    V& getRef(const K& key) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i=0; i<bucket.size(); i++)
            if (bucket.get(i).first == key)
                return bucket.get(i).second;

        throw std::out_of_range("Key not found");
    }
    void remove(const K& key) {
        int index = hash(key);
        DynamicArray<Pair<K,V>>& bucket = buckets[index];

        for (int i = 0; i < bucket.size(); i++) {
            if (bucket.get(i).first == key) {
                // shift
                for (int j = i; j < bucket.size() - 1; j++)
                    bucket.get(j) = bucket.get(j + 1);

                bucket.pop_back();
                entryCount--;
                return;
            }
        }

        throw std::out_of_range("Key not found");
    }
    int size() const { return entryCount; }
    bool isEmpty() const { return entryCount == 0; }
    DynamicArray<K> keys() const {
        DynamicArray<K> allKeys;

        for (int i = 0; i < numBuckets; i++) {
            const DynamicArray<Pair<K,V>>& bucket = buckets[i];
            for (int j = 0; j < bucket.size(); j++)
                allKeys.push_back(bucket.get(j).first);
        }

        return allKeys;
    }

    DynamicArray<V> values() const {
        DynamicArray<V> allValues;

        for (int i = 0; i < numBuckets; i++) {
            const DynamicArray<Pair<K,V>>& bucket = buckets[i];
            for (int j = 0; j < bucket.size(); j++)
                allValues.push_back(bucket.get(j).second);
        }

        return allValues;
    }

    void clear() {
        for (int i = 0; i < numBuckets; i++) {
            while (buckets[i].size() > 0)
                buckets[i].pop_back();
        }
        entryCount = 0;
    }
};