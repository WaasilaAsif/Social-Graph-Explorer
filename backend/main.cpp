#include <iostream>
#include "dsa/containers/trie.h" 
#include "dsa/containers/DynamicArray.h" 

int main() {
    Trie trie;

    // Insert some usernames
    trie.insert("anna");
    trie.insert("anum");
    trie.insert("Bob");
    trie.insert("alice");
    trie.insert("Alfred");

    // Search exact names
    std::cout << "Search Anna: " << trie.search("anna") << std::endl; // 1 = found
    std::cout << "Search Bob: " << trie.search("Bob") << std::endl;   // 1 = found
    std::cout << "Search John: " << trie.search("john") << std::endl; // 0 = not found

    // Prefix search
    DynamicArray<std::string> result = trie.startsWith("an");
    std::cout << "Users starting with 'An':\n";
    for (int i = 0; i < result.size(); i++)
        std::cout << result.get(i) << std::endl;

    result = trie.startsWith("Al");
    std::cout << "Users starting with 'Al':\n";
    for (int i = 0; i < result.size(); i++)
        std::cout << result.get(i) << std::endl;

    result = trie.startsWith("B");
    std::cout << "Users starting with 'B':\n";
    for (int i = 0; i < result.size(); i++)
        std::cout << result.get(i) << std::endl;

    return 0;
}
