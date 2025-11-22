#pragma once
#include <iostream>
#include <string>
#include "DynamicArray.h"
#include <algorithm>

using namespace std;

// Convert string to lowercase
string toLower(const string& s) {
    string res = s;
    transform(res.begin(), res.end(), res.begin(), ::tolower);
    return res;
}

class TrieNode {
public:
    bool isEndOfWord;
    TrieNode* children[27]; // 26 letters + 1 space

    TrieNode() {
        isEndOfWord = false;
        for (int i = 0; i < 27; i++)
            children[i] = nullptr;
    }
};

// Convert char to index
inline int charToIndex(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a';
    if (c == ' ') return 26; // space at last index
    return -1; // invalid character
}

class Trie {
private:
    TrieNode* root;

    void collectAllWords(TrieNode* node, string prefix, DynamicArray<string>& result) {
        if (!node) return;
        if (node->isEndOfWord)
            result.push_back(prefix);

        for (int i = 0; i < 27; i++) {
            if (node->children[i]) {
                char nextChar = (i == 26) ? ' ' : ('a' + i);
                collectAllWords(node->children[i], prefix + nextChar, result);
            }
        }
    }

    // Helper function to delete all nodes
    void deleteNodes(TrieNode* node) {
        if (!node) return;
        for (int i = 0; i < 27; i++) {
            if (node->children[i])
                deleteNodes(node->children[i]);
        }
        delete node;
    }

public:
    Trie() {
        root = new TrieNode();
    }

    // Destructor to prevent memory leaks
    ~Trie() {
        deleteNodes(root);
    }

    // Disable copying (or implement proper deep copy)
    Trie(const Trie&) = delete;
    Trie& operator=(const Trie&) = delete;

    // Rest of your methods remain the same...
    void insert(const string& word) {
        TrieNode* current = root;
        string w = toLower(word);
        for (char c : w) {
            int idx = charToIndex(c);
            if (idx == -1) continue;
            if (!current->children[idx])
                current->children[idx] = new TrieNode();
            current = current->children[idx];
        }
        current->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* current = root;
        string w = toLower(word);
        for (char c : w) {
            int idx = charToIndex(c);
            if (idx == -1 || !current->children[idx])
                return false;
            current = current->children[idx];
        }
        return current->isEndOfWord;
    }

    DynamicArray<string> startsWith(const string& prefix) {
        TrieNode* current = root;
        string p = toLower(prefix);
        for (char c : p) {
            int idx = charToIndex(c);
            if (idx == -1 || !current->children[idx])
                return DynamicArray<string>();
            current = current->children[idx];
        }
        DynamicArray<string> result;
        collectAllWords(current, p, result);
        return result;
    }
};
