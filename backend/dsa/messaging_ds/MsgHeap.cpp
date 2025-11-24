#include "MsgHeap.h"

MsgHeap::MsgHeap(bool minHeap) : isMinHeap(minHeap) {}

void MsgHeap::heapifyUp(int idx) {
    if (idx == 0) return;
    
    int parent = (idx - 1) / 2;
    
    // For min-heap: parent should be smaller, for max-heap: parent should be larger
    bool shouldSwap = isMinHeap ? (heap.get(idx) < heap.get(parent)) 
                                : (heap.get(idx) > heap.get(parent));
    
    if (shouldSwap) {
        // Swap with parent
        int temp = heap.get(idx);
        heap.get(idx) = heap.get(parent);
        heap.get(parent) = temp;
        heapifyUp(parent);
    }
}

void MsgHeap::heapifyDown(int idx) {
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    int target = idx;
    
    // Find which child to swap with (if any)
    if (left < heap.size()) {
        bool leftBetter = isMinHeap ? (heap.get(left) < heap.get(target))
                                    : (heap.get(left) > heap.get(target));
        if (leftBetter) {
            target = left;
        }
    }
    
    if (right < heap.size()) {
        bool rightBetter = isMinHeap ? (heap.get(right) < heap.get(target))
                                     : (heap.get(right) > heap.get(target));
        if (rightBetter) {
            target = right;
        }
    }
    
    // Swap if needed and continue heapifying down
    if (target != idx) {
        int temp = heap.get(idx);
        heap.get(idx) = heap.get(target);
        heap.get(target) = temp;
        heapifyDown(target);
    }
}

void MsgHeap::push(int value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

bool MsgHeap::pop(int& removed) {
    if (isEmpty()) {
        return false;
    }
    
    removed = heap.get(0);
    
    // Move last element to root and heapify down
    heap.get(0) = heap.get(heap.size() - 1);
    heap.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return true;
}

bool MsgHeap::peek(int& topValue) const {
    if (isEmpty()) {
        return false;
    }
    topValue = heap.get(0);
    return true;
}

bool MsgHeap::isEmpty() const {
    return heap.size() == 0;
}

int MsgHeap::size() const {
    return heap.size();
}
