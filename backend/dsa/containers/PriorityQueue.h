#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <stdexcept>
#include <vector>

template <typename T>
class PriorityQueue {
private:
    std::vector<T> heap;
    
    int parent(int i) { return (i - 1) / 2; }
    int leftChild(int i) { return 2 * i + 1; }
    int rightChild(int i) { return 2 * i + 2; }
    
    void heapifyUp(int index);
    void heapifyDown(int index);
    void swap(int i, int j);

public:
    PriorityQueue();
    
    void insert(const T& value);
    T extractMax();
    T peek() const;
    
    bool isEmpty() const;
    int size() const;
    void clear();
    void buildHeap(const std::vector<T>& data);
};

template <typename T>
PriorityQueue<T>::PriorityQueue() {}

template <typename T>
void PriorityQueue<T>::swap(int i, int j) {
    T temp = heap[i];
    heap[i] = heap[j];
    heap[j] = temp;
}

template <typename T>
void PriorityQueue<T>::heapifyUp(int index) {
    if (index == 0) return;
    
    int parentIdx = parent(index);
    if (heap[index] > heap[parentIdx]) {
        swap(index, parentIdx);
        heapifyUp(parentIdx);
    }
}

template <typename T>
void PriorityQueue<T>::heapifyDown(int index) {
    int largest = index;
    int left = leftChild(index);
    int right = rightChild(index);
    
    if (left < heap.size() && heap[left] > heap[largest]) {
        largest = left;
    }
    
    if (right < heap.size() && heap[right] > heap[largest]) {
        largest = right;
    }
    
    if (largest != index) {
        swap(index, largest);
        heapifyDown(largest);
    }
}

template <typename T>
void PriorityQueue<T>::insert(const T& value) {
    heap.push_back(value);
    heapifyUp(heap.size() - 1);
}

template <typename T>
T PriorityQueue<T>::extractMax() {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }
    
    T maxValue = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    
    if (!isEmpty()) {
        heapifyDown(0);
    }
    
    return maxValue;
}

template <typename T>
T PriorityQueue<T>::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("PriorityQueue is empty");
    }
    return heap[0];
}

template <typename T>
bool PriorityQueue<T>::isEmpty() const {
    return heap.empty();
}

template <typename T>
int PriorityQueue<T>::size() const {
    return heap.size();
}

template <typename T>
void PriorityQueue<T>::clear() {
    heap.clear();
}

template <typename T>
void PriorityQueue<T>::buildHeap(const std::vector<T>& data) {
    heap = data;
    for (int i = heap.size() / 2 - 1; i >= 0; i--) {
        heapifyDown(i);
    }
}

#endif