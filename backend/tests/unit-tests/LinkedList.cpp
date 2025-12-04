#include "../../dsa/containers/LinkedList.h"
#include <iostream>

int main() {
    LinkedList<int> list;
    
    std::cout << "Appending 1, 2, 3...\n";
    list.append(1);
    list.append(2);
    list.append(3);
    list.print(); // Expected: 1 -> 2 -> 3

    std::cout << "Prepending 0...\n";
    list.prepend(0);
    list.print(); // Expected: 0 -> 1 -> 2 -> 3

    std::cout << "Remove 2...\n";
    list.remove(2);
    list.print(); // Expected: 0 -> 1 -> 3

    std::cout << "Remove head: " << list.removeHead() << "\n";
    list.print(); // Expected: 1 -> 3

    std::cout << "Remove tail: " << list.removeTail() << "\n";
    list.print(); // Expected: 1

    return 0;
}
