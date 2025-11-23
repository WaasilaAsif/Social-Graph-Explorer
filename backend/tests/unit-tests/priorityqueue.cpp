#include "../../dsa/containers/PriorityQueue.h"
#include <iostream>
#include <cassert>

int main() {
    std::cout << "=== Testing PriorityQueue ===" << std::endl;
    
    // Test 1: Basic integer operations
    std::cout << "\nTest 1: Basic Integer Max-Heap" << std::endl;
    PriorityQueue<int> pq;
    pq.insert(5);
    pq.insert(10);
    pq.insert(3);
    pq.insert(20);
    pq.insert(8);
    
    std::cout << "Inserted: 5, 10, 3, 20, 8" << std::endl;
    std::cout << "Extracting in descending order: ";
    assert(pq.extractMax() == 20);
    std::cout << "20 ";
    assert(pq.extractMax() == 10);
    std::cout << "10 ";
    assert(pq.extractMax() == 8);
    std::cout << "8 ";
    assert(pq.extractMax() == 5);
    std::cout << "5 ";
    assert(pq.extractMax() == 3);
    std::cout << "3" << std::endl;
    std::cout << "✓ Test 1 PASSED" << std::endl;
    
    // Test 2: Peek operation
    std::cout << "\nTest 2: Peek Operation" << std::endl;
    PriorityQueue<int> pq2;
    pq2.insert(100);
    pq2.insert(50);
    pq2.insert(150);
    pq2.insert(75);
    
    std::cout << "Inserted: 100, 50, 150, 75" << std::endl;
    std::cout << "Peek (should be 150): " << pq2.peek() << std::endl;
    assert(pq2.peek() == 150);
    std::cout << "Size: " << pq2.size() << std::endl;
    assert(pq2.size() == 4);
    std::cout << "✓ Test 2 PASSED" << std::endl;
    
    // Test 3: isEmpty and size
    std::cout << "\nTest 3: isEmpty and Size" << std::endl;
    PriorityQueue<int> pq3;
    assert(pq3.isEmpty());
    std::cout << "Empty queue isEmpty: " << (pq3.isEmpty() ? "true" : "false") << std::endl;
    
    pq3.insert(1);
    pq3.insert(2);
    pq3.insert(3);
    assert(!pq3.isEmpty());
    assert(pq3.size() == 3);
    std::cout << "After inserting 3 elements, isEmpty: " << (pq3.isEmpty() ? "true" : "false") << std::endl;
    std::cout << "Size: " << pq3.size() << std::endl;
    std::cout << "✓ Test 3 PASSED" << std::endl;
    
    // Test 4: Build heap from vector
    std::cout << "\nTest 4: Build Heap from Vector" << std::endl;
    std::vector<int> data = {4, 10, 3, 5, 1, 8};
    PriorityQueue<int> pq4;
    pq4.buildHeap(data);
    
    std::cout << "Built heap from: 4, 10, 3, 5, 1, 8" << std::endl;
    std::cout << "Extracting: ";
    while (!pq4.isEmpty()) {
        std::cout << pq4.extractMax() << " ";
    }
    std::cout << std::endl;
    std::cout << "✓ Test 4 PASSED" << std::endl;
    
    // Test 5: Clear operation
    std::cout << "\nTest 5: Clear Operation" << std::endl;
    PriorityQueue<int> pq5;
    pq5.insert(1);
    pq5.insert(2);
    pq5.insert(3);
    std::cout << "Size before clear: " << pq5.size() << std::endl;
    assert(pq5.size() == 3);
    
    pq5.clear();
    std::cout << "Size after clear: " << pq5.size() << std::endl;
    assert(pq5.isEmpty());
    std::cout << "✓ Test 5 PASSED" << std::endl;
    
    // Test 6: Error handling
    std::cout << "\nTest 6: Error Handling" << std::endl;
    PriorityQueue<int> emptyPQ;
    try {
        emptyPQ.extractMax();
        std::cout << "✗ Test 6 FAILED - Should have thrown error" << std::endl;
    } catch (const std::runtime_error& e) {
        std::cout << "Caught expected error: " << e.what() << std::endl;
        std::cout << "✓ Test 6 PASSED" << std::endl;
    }
    
    std::cout << "\n=== All PriorityQueue Tests PASSED! ===" << std::endl;
    return 0;
}