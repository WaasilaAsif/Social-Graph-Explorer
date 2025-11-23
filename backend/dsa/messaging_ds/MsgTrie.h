#ifndef MSGTRIE_H
#define MSGTRIE_H

#include "HashMap.h"
#include <vector>
#include <string>
using namespace std;
class MsgTrie {
private:
    struct TrieNode {
        bool isEnd;                        // Marks end of a word
        std::vector<int> messageIds;       // IDs of messages containing this word
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
    std::vector<int> search(const std::string& word) const;

    // Search prefix, return all message IDs containing words starting with prefix
    std::vector<int> startsWith(const std::string& prefix) const;
};

#endif
