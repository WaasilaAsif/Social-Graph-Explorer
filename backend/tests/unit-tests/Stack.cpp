#include "../../dsa/containers/Stack.h"
#include <iostream>

int main() {
    Stack<int> s;

    s.push(10);
    s.push(20);
    s.push(30);

    std::cout << "Top: " << s.top() << "\n"; // 30

    std::cout << "Pop: " << s.pop() << "\n"; // 30
    std::cout << "Pop: " << s.pop() << "\n"; // 20

    s.print(); // Top -> 10

    std::cout << "Size: " << s.size() << "\n"; // 1
    std::cout << "Is empty: " << (s.isEmpty() ? "Yes" : "No") << "\n"; // No

    return 0;
}