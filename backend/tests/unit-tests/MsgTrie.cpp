#include "../../dsa/messaging_ds/MsgTrie.h"
#include <iostream>
#include <cassert>

using namespace std;

bool contains(const DynamicArray<int>& arr, int value) {
    for (int i = 0; i < arr.size(); i++) {
        if (arr.get(i) == value) return true;
    }
    return false;
}

void testInsertAndSearch() {
    cout << "Testing insert and exact search..." << endl;
    MsgTrie trie;
    
    // Insert words from different messages
    trie.insert("hello", 1);
    trie.insert("world", 1);
    trie.insert("hello", 2); // Same word, different message
    trie.insert("help", 3);
    
    // Search exact words
    DynamicArray<int> result = trie.search("hello");
    assert(result.size() == 2);
    assert(contains(result, 1));
    assert(contains(result, 2));
    
    result = trie.search("world");
    assert(result.size() == 1);
    assert(result.get(0) == 1);
    
    result = trie.search("help");
    assert(result.size() == 1);
    assert(result.get(0) == 3);
    
    // Search non-existent word
    result = trie.search("goodbye");
    assert(result.size() == 0);
    
    cout << "Insert/Search tests passed!" << endl;
}

void testPrefixSearch() {
    cout << "Testing prefix search..." << endl;
    MsgTrie trie;
    
    trie.insert("hello", 1);
    trie.insert("help", 2);
    trie.insert("helper", 3);
    trie.insert("world", 4);
    
    // Search prefix "hel" - should find hello, help, helper
    DynamicArray<int> result = trie.startsWith("hel");
    assert(result.size() == 3);
    assert(contains(result, 1));
    assert(contains(result, 2));
    assert(contains(result, 3));
    
    // Search prefix "help" - should find help, helper
    result = trie.startsWith("help");
    assert(result.size() == 2);
    
    // Search prefix that doesn't exist
    result = trie.startsWith("xyz");
    assert(result.size() == 0);
    
    cout << "Prefix search tests passed!" << endl;
}

void testMultipleMessages() {
    cout << "Testing multiple messages scenario..." << endl;
    MsgTrie trie;
    
    // Simulate indexing messages
    // Message 1: "how are you"
    trie.insert("how", 1);
    trie.insert("are", 1);
    trie.insert("you", 1);
    
    // Message 2: "how is everything"
    trie.insert("how", 2);
    trie.insert("is", 2);
    trie.insert("everything", 2);
    
    // Message 3: "you are awesome"
    trie.insert("you", 3);
    trie.insert("are", 3);
    trie.insert("awesome", 3);
    
    // Search "how" - should be in messages 1 and 2
    DynamicArray<int> result = trie.search("how");
    assert(result.size() == 2);
    
    // Search "are" - should be in messages 1 and 3
    result = trie.search("are");
    assert(result.size() == 2);
    
    // Search "you" - should be in messages 1 and 3
    result = trie.search("you");
    assert(result.size() == 2);
    
    cout << "Multiple messages tests passed!" << endl;
}

void testEmptyTrie() {
    cout << "Testing empty trie..." << endl;
    MsgTrie trie;
    
    DynamicArray<int> result = trie.search("anything");
    assert(result.size() == 0);
    
    result = trie.startsWith("any");
    assert(result.size() == 0);
    
    cout << "Empty trie tests passed!" << endl;
}

int main() {
    cout << "=== MsgTrie Unit Tests ===" << endl;
    
    try {
        testInsertAndSearch();
        testPrefixSearch();
        testMultipleMessages();
        testEmptyTrie();
        
        cout << "\nALL MSGTRIE TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\nTest failed: " << e.what() << endl;
        return 1;
    }
}
