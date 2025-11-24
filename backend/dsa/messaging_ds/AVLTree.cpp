#include "AVLTree.h"
#include "../messaging_ds/Message.h"
template <typename T>
AVLTree<T>::AVLTree() : root(nullptr) {}

template <typename T>
AVLTree<T>::~AVLTree() {
    clear(root);
}

template <typename T>
void AVLTree<T>::clear(AVLNode<T>* node) {
    if (!node) return;
    clear(node->left);
    clear(node->right);
    delete node;
}

template <typename T>
int AVLTree<T>::getHeight(AVLNode<T>* node) {
    return node ? node->height : 0;
}

template <typename T>
int AVLTree<T>::getBalance(AVLNode<T>* node) {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotateRight(AVLNode<T>* y) {
    AVLNode<T>* x = y->left;
    AVLNode<T>* T2 = x->right;

    // Perform rotation
    x->right = y;
    y->left = T2;

    // Update heights
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));

    return x;
}

template <typename T>
AVLNode<T>* AVLTree<T>::rotateLeft(AVLNode<T>* x) {
    AVLNode<T>* y = x->right;
    AVLNode<T>* T2 = y->left;

    // Perform rotation
    y->left = x;
    x->right = T2;

    // Update heights
    x->height = 1 + std::max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

template <typename T>
AVLNode<T>* AVLTree<T>::insert(AVLNode<T>* node, const T& key) {
    // 1. Perform standard BST insertion
    if (!node) {
        return new AVLNode<T>(key);
    }

    if (key < node->key) {
        node->left = insert(node->left, key);
    } else if (key > node->key) {
        node->right = insert(node->right, key);
    } else {
        // Duplicate keys not allowed
        return node;
    }

    // 2. Update height of this ancestor node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // 4. Balance the tree if unbalanced
    // Left-Left Case
    if (balance > 1 && key < node->left->key) {
        return rotateRight(node);
    }

    // Right-Right Case
    if (balance < -1 && key > node->right->key) {
        return rotateLeft(node);
    }

    // Left-Right Case
    if (balance > 1 && key > node->left->key) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Left Case
    if (balance < -1 && key < node->right->key) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
AVLNode<T>* AVLTree<T>::remove(AVLNode<T>* node, const T& key) {
    if (!node) return node;

    // 1. Perform standard BST delete
    if (key < node->key) {
        node->left = remove(node->left, key);
    } else if (key > node->key) {
        node->right = remove(node->right, key);
    } else {
        // Node with only one child or no child
        if (!node->left || !node->right) {
            AVLNode<T>* temp = node->left ? node->left : node->right;

            // No child case
            if (!temp) {
                temp = node;
                node = nullptr;
            } else {
                // One child case
                *node = *temp;
            }
            delete temp;
        } else {
            // Node with two children: Get the inorder successor
            AVLNode<T>* temp = node->right;
            while (temp->left) {
                temp = temp->left;
            }

            // Copy the inorder successor's data to this node
            node->key = temp->key;

            // Delete the inorder successor
            node->right = remove(node->right, temp->key);
        }
    }

    if (!node) return node;

    // 2. Update height of current node
    node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));

    // 3. Get the balance factor
    int balance = getBalance(node);

    // 4. Balance the tree if unbalanced
    // Left-Left Case
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    // Left-Right Case
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    // Right-Right Case
    if (balance < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    // Right-Left Case
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

template <typename T>
void AVLTree<T>::insert(const T& key) {
    root = insert(root, key);
}

template <typename T>
void AVLTree<T>::remove(const T& key) {
    root = remove(root, key);
}

template <typename T>
bool AVLTree<T>::search(const T& key) const {
    AVLNode<T>* current = root;
    
    while (current) {
        if (key == current->key) {
            return true;
        } else if (key < current->key) {
            current = current->left;
        } else {
            current = current->right;
        }
    }
    
    return false;
}

template <typename T>
void AVLTree<T>::inorderTraversal(AVLNode<T>* node, DynamicArray<T>& result) {
    if (!node) return;
    
    inorderTraversal(node->left, result);
    result.push_back(node->key);
    inorderTraversal(node->right, result);
}

template <typename T>
DynamicArray<T> AVLTree<T>::inorder() const {
    DynamicArray<T> result;
    inorderTraversal(root, result);
    return result;
}

// Explicit template instantiations for common types
template class AVLTree<int>;
template class AVLTree<double>;
template class AVLTree<float>;
template class AVLTree<long>;
template class AVLTree<char>;
template class AVLTree<Message>;
