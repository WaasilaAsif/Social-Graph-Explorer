#include "MsgHeap.h"

MsgHeap::MsgHeap(bool isMinHeap) {
    if (isMinHeap)
        compare = [](int a, int b) { return a < b; };
    else
        compare = [](int a, int b) { return a > b; };
}

void MsgHeap::heapifyUp(int idx) {}
void MsgHeap::heapifyDown(int idx) {}

void MsgHeap::push(int value) {}

bool MsgHeap::pop(int& removed) {
    return false;
}

bool MsgHeap::peek(int& topValue) const {
    return false;
}

bool MsgHeap::isEmpty() const {
    return heap.empty();
}

int MsgHeap::size() const {
    return heap.size();
}
