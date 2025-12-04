#include "../../dsa/containers/Queue.h"
#include <iostream>

int main() {
    Queue<int> q;

    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);

    std::cout << "Front: " << q.front() << "\n"; // 10
    std::cout << "Back: " << q.back() << "\n";   // 30

    std::cout << "Dequeue: " << q.dequeue() << "\n"; // 10
    std::cout << "Dequeue: " << q.dequeue() << "\n"; // 20

    q.print(); // Front -> 30

    return 0;
}
