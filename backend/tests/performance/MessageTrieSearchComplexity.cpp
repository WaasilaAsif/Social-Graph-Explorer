// MessageTrieSearchComplexity.cpp
// Test script for measuring message trie search complexity for 1000, 10000, and 100000 users/messages

#include "../../dsa/messaging_ds/MsgTrie.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;

// Generate random lowercase word of given length
string randomWord(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz";
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 25);
    string word;
    for (int i = 0; i < length; ++i) {
        word += charset[dis(gen)];
    }
    return word;
}

void testTrieSearch(int numMessages) {
    MsgTrie trie;
    vector<string> words;
    // Insert random words into trie
    for (int i = 0; i < numMessages; ++i) {
        string word = randomWord(8);
        words.push_back(word);
        trie.insert(word, i+1);
    }
    // Search for all inserted words and measure time
    auto start = high_resolution_clock::now();
    for (int i = 0; i < numMessages; ++i) {
        trie.search(words[i]);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Searched " << numMessages << " words in " << duration.count() << " ms." << endl;
}

int main() {
    cout << "Testing message trie search complexity..." << endl;
    testTrieSearch(1000);
    testTrieSearch(10000);
    testTrieSearch(100000);
    return 0;
}
