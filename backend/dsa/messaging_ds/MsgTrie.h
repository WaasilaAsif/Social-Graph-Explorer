#ifndef MSGTRIE_H
#define MSGTRIE_H

#include "../containers/HashMap.h"
#include "../containers/DynamicArray.h"
#include <string>
using namespace std;
class MsgTrie {
private:
    struct TrieNode {
        bool isEnd;                        // Marks end of a word
        DynamicArray<int> messageIds;      // IDs of messages containing this word
        HashMap<char, TrieNode*> children; // Children nodes for next char

        TrieNode() : isEnd(false) {}
    };

    TrieNode* root;

    void clear(TrieNode* node);

public:
    MsgTrie();
    ~MsgTrie();

    // Insert a word from a message with messageId
    void insert(const std::string& word, int messageId);

    // Search exact word, return message IDs
    DynamicArray<int> search(const std::string& word) const;

    // Search prefix, return all message IDs containing words starting with prefix
    DynamicArray<int> startsWith(const std::string& prefix) const;
};

#endif
