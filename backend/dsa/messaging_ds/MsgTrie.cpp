#include "MsgTrie.h"

MsgTrie::MsgTrie() {
    root = new TrieNode();
}

MsgTrie::~MsgTrie() {
    clear(root);
}

void MsgTrie::clear(TrieNode* node) {}

void MsgTrie::insert(const std::string& word, int messageId) {}

std::vector<int> MsgTrie::search(const std::string& word) const {
    return {};
}

std::vector<int> MsgTrie::startsWith(const std::string& prefix) const {
    return {};
}
