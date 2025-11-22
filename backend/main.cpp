#include <iostream>
#include "dsa/user/User.h"
#include"dsa/user/user.cpp"

int main() {
    User u1("Anum", "pass123");
    User u2("Ali", "hello");
    User u3("Sara", "xyz");

    std::cout << "User 1 -> ID: " << u1.getId() << ", Name: " << u1.getName() << "\n";
    std::cout << "User 2 -> ID: " << u2.getId() << ", Name: " << u2.getName() << "\n";
    std::cout << "User 3 -> ID: " << u3.getId() << ", Name: " << u3.getName() << "\n";

    return 0;
}
