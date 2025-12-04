#include "../../dsa/messaging_ds/AVLTree.h"
#include <iostream>
#include <cassert>

using namespace std;

void testInsertAndSearch() {
    cout << "Testing insert and search..." << endl;
    AVLTree<int> tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    
    assert(tree.search(50));
    assert(tree.search(30));
    assert(tree.search(70));
    assert(tree.search(20));
    assert(tree.search(40));
    assert(!tree.search(100));
    assert(!tree.search(10));
    
    cout << " Insert/Search tests passed!" << endl;
}

void testInorderTraversal() {
    cout << "Testing inorder traversal (sorted output)..." << endl;
    AVLTree<int> tree;
    
    // Insert in random order
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    tree.insert(60);
    tree.insert(80);
    
    DynamicArray<int> result = tree.inorder();
    
    // Should be in sorted order: 20, 30, 40, 50, 60, 70, 80
    assert(result.size() == 7);
    assert(result.get(0) == 20);
    assert(result.get(1) == 30);
    assert(result.get(2) == 40);
    assert(result.get(3) == 50);
    assert(result.get(4) == 60);
    assert(result.get(5) == 70);
    assert(result.get(6) == 80);
    
    cout << " Inorder traversal tests passed!" << endl;
}

void testRemove() {
    cout << "Testing remove operation..." << endl;
    AVLTree<int> tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(70);
    tree.insert(20);
    tree.insert(40);
    
    // Remove leaf node
    tree.remove(20);
    assert(!tree.search(20));
    assert(tree.search(30));
    
    // Remove node with one child
    tree.remove(30);
    assert(!tree.search(30));
    assert(tree.search(40));
    
    // Remove node with two children
    tree.insert(60);
    tree.insert(80);
    tree.remove(70);
    assert(!tree.search(70));
    assert(tree.search(60));
    assert(tree.search(80));
    
    cout << " Remove tests passed!" << endl;
}

void testBalancing() {
    cout << "Testing AVL balancing..." << endl;
    AVLTree<int> tree;
    
    // Insert in ascending order (would create unbalanced tree without AVL)
    for (int i = 1; i <= 10; i++) {
        tree.insert(i);
    }
    
    // All elements should be searchable
    for (int i = 1; i <= 10; i++) {
        assert(tree.search(i));
    }
    
    // Inorder should still give sorted result
    DynamicArray<int> result = tree.inorder();
    assert(result.size() == 10);
    for (int i = 0; i < 10; i++) {
        assert(result.get(i) == i + 1);
    }
    
    cout << " Balancing tests passed!" << endl;
}

void testDuplicates() {
    cout << "Testing duplicate handling..." << endl;
    AVLTree<int> tree;
    
    tree.insert(50);
    tree.insert(30);
    tree.insert(50); // Duplicate
    tree.insert(30); // Duplicate
    
    DynamicArray<int> result = tree.inorder();
    assert(result.size() == 2); // Duplicates not allowed
    
    cout << " Duplicate handling tests passed!" << endl;
}

void testLargeTree() {
    cout << "Testing large tree (performance)..." << endl;
    AVLTree<int> tree;
    
    // Insert 1000 elements
    for (int i = 0; i < 1000; i++) {
        tree.insert(i);
    }
    
    // Search all elements
    for (int i = 0; i < 1000; i++) {
        assert(tree.search(i));
    }
    
    // Verify inorder size
    DynamicArray<int> result = tree.inorder();
    assert(result.size() == 1000);
    
    cout << " Large tree tests passed!" << endl;
}

int main() {
    cout << "=== AVLTree Unit Tests ===" << endl;
    
    try {
        testInsertAndSearch();
        testInorderTraversal();
        testRemove();
        testBalancing();
        testDuplicates();
        testLargeTree();
        
        cout << "\n ALL AVLTREE TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
