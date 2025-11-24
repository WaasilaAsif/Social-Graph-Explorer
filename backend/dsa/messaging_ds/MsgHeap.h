#ifndef MSGHEAP_H
#define MSGHEAP_H

#include "../containers/DynamicArray.h"

class MsgHeap {
private:
    DynamicArray<int> heap;  
    bool isMinHeap; 

    void heapifyUp(int idx);
    void heapifyDown(int idx);

public:
    MsgHeap(bool isMinHeap = false);

    void push(int value);
    bool pop(int& removed);
    bool peek(int& topValue) const;
    bool isEmpty() const;
    int size() const;
};

#endif
