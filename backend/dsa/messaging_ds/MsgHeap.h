#ifndef MSGHEAP_H
#define MSGHEAP_H

#include <vector>
#include <functional>
using namespace std;
class MsgHeap {
private:
    vector<int> heap;  
    function<bool(int, int)> compare; 

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
