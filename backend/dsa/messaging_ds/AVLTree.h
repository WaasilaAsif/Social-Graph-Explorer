#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "DynamicArray.h"

// Node structure for AVL Tree
template <typename T>
struct AVLNode {
    T key;
    int height;
    AVLNode* left;
    AVLNode* right;

    AVLNode(const T& k) : key(k), height(1), left(nullptr), right(nullptr) {}
};

template <typename T>
class AVLTree {
private:
    AVLNode<T>* root;

    // Helper functions (to implement later)
    AVLNode<T>* insert(AVLNode<T>* node, const T& key);
    AVLNode<T>* remove(AVLNode<T>* node, const T& key);
    AVLNode<T>* rotateLeft(AVLNode<T>* node);
    AVLNode<T>* rotateRight(AVLNode<T>* node);
    int getHeight(AVLNode<T>* node);
    int getBalance(AVLNode<T>* node);
    void inorderTraversal(AVLNode<T>* node, DynamicArray<T>& result);

    void clear(AVLNode<T>* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(const T& key);
    void remove(const T& key);
    bool search(const T& key) const;
    DynamicArray<T> inorder() const;
};

#endif
