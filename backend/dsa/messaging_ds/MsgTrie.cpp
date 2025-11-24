#include "MsgTrie.h"
#include <iostream>
using namespace std;

MsgTrie::MsgTrie() {
    root = new TrieNode();
}

MsgTrie::~MsgTrie() {
    clear(root);
}

void MsgTrie::clear(TrieNode* node) {
    if (!node) return;

    // Use forEach to iterate over all children
    node->children.forEach([this](char key, TrieNode* childNode) {
        clear(childNode); // recursively clear child TrieNode
    });

    delete node;
}


// Insert a word and link it to messageId
void MsgTrie::insert(const std::string& word, int messageId) {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.contains(c)) {
            curr->children[c] = new TrieNode();
        }
        curr = curr->children[c];
    }
    curr->isEnd = true;
    curr->messageIds.push_back(messageId);
}

// Search exact word
DynamicArray<int> MsgTrie::search(const std::string& word) const {
    TrieNode* curr = root;
    for (char c : word) {
        if (!curr->children.contains(c)) {
            return DynamicArray<int>(); // word not found
        }
        curr = curr->children[c];
    }
    if (curr->isEnd)
        return curr->messageIds;
    return DynamicArray<int>();
}

// Search prefix
DynamicArray<int> MsgTrie::startsWith(const std::string& prefix) const {
    TrieNode* curr = root;
    for (char c : prefix) {
        if (!curr->children.contains(c)) {
            return DynamicArray<int>(); // prefix not found
        }
        curr = curr->children[c];
    }

    // Collect all messageIds in this subtree
    DynamicArray<int> result;
    DynamicArray<TrieNode*> stack;
    stack.push_back(curr);

    while (stack.size() > 0) {
        TrieNode* node = stack.get(stack.size() - 1);
        stack.pop_back();

        for (int i = 0; i < node->messageIds.size(); i++)
            result.push_back(node->messageIds.get(i));

        // Use forEach to traverse children
        node->children.forEach([&stack](char key, TrieNode* childNode) {
            stack.push_back(childNode);
        });
    }

    return result;
}
