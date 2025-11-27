#include "../../dsa/messaging_ds/MsgHeap.h"
#include <iostream>
#include <cassert>

using namespace std;

void testMinHeap() {
    cout << "Testing Min Heap..." << endl;
    MsgHeap minHeap(true);
    
    // Test empty heap
    assert(minHeap.isEmpty());
    assert(minHeap.size() == 0);
    
    // Test push and peek
    minHeap.push(50);
    minHeap.push(30);
    minHeap.push(70);
    minHeap.push(10);
    minHeap.push(60);
    
    assert(minHeap.size() == 5);
    assert(!minHeap.isEmpty());
    
    int top;
    assert(minHeap.peek(top));
    assert(top == 10); // Min element should be at top
    
    // Test pop (should give sorted order for min heap)
    assert(minHeap.pop(top));
    assert(top == 10);
    
    assert(minHeap.pop(top));
    assert(top == 30);
    
    assert(minHeap.pop(top));
    assert(top == 50);
    
    cout << " Min Heap tests passed!" << endl;
}

void testMaxHeap() {
    cout << "Testing Max Heap..." << endl;
    MsgHeap maxHeap(false);
    
    // Test push
    maxHeap.push(50);
    maxHeap.push(30);
    maxHeap.push(70);
    maxHeap.push(10);
    maxHeap.push(60);
    
    int top;
    assert(maxHeap.peek(top));
    assert(top == 70); // Max element should be at top
    
    // Test pop (should give reverse sorted order)
    assert(maxHeap.pop(top));
    assert(top == 70);
    
    assert(maxHeap.pop(top));
    assert(top == 60);
    
    assert(maxHeap.pop(top));
    assert(top == 50);
    
    cout << " Max Heap tests passed!" << endl;
}

void testEmptyOperations() {
    cout << "Testing empty heap operations..." << endl;
    MsgHeap heap(true);
    
    int value;
    assert(!heap.pop(value)); // Can't pop from empty
    assert(!heap.peek(value)); // Can't peek empty
    
    cout << " Empty operations tests passed!" << endl;
}

int main() {
    cout << "=== MsgHeap Unit Tests ===" << endl;
    
    try {
        testMinHeap();
        testMaxHeap();
        testEmptyOperations();
        
        cout << "\n ALL MSGHEAP TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
