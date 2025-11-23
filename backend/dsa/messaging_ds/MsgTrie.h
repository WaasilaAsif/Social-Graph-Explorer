#ifndef MSGTRIE_H
#define MSGTRIE_H

#include <unordered_map>
#include <vector>
#include <string>

class MsgTrie {
private:
    struct TrieNode {
        bool isEnd;
        std::vector<int> messageIds;
        std::unordered_map<char, TrieNode*> children;

        TrieNode() : isEnd(false) {}
    };

    TrieNode* root;

    void clear(TrieNode* node);

public:
    MsgTrie();
    ~MsgTrie();

    void insert(const std::string& word, int messageId);
    std::vector<int> search(const std::string& word) const;
    std::vector<int> startsWith(const std::string& prefix) const;
};

#endif
