#include <iostream>
#include "../backend/dsa/user/UserManager.h"
#include "../backend/dsa/user/User.h"
#include "../backend/dsa/user/user.cpp"
#include "../backend/dsa/user/UserManager.cpp"

int main() {
    UserManager um;

    // Add users
    um.addUser("Alice", "pass1");
    um.addUser("Bob", "pass2");
    um.addUser("Anna", "pass3");

    // Test getUserById
    User* u1 = um.getUserById(1);
    User* u2 = um.getUserById(2);
    User* u3 = um.getUserById(3);

    if (u1) std::cout << "User 1: " << u1->getName() << "\n";
    if (u2) std::cout << "User 2: " << u2->getName() << "\n";
    if (u3) std::cout << "User 3: " << u3->getName() << "\n";

    // Test login
    User* loggedIn = um.login("alice", "pass1");
    if (loggedIn)
        std::cout << "Login success: " << loggedIn->getName() << "\n";
    else
        std::cout << "Login failed\n";

    loggedIn = um.login("bob", "wrongpass");
    if (loggedIn)
        std::cout << "Login success: " << loggedIn->getName() << "\n";
    else
        std::cout << "Login failed\n";

    // Test prefix search
    DynamicArray<std::string> matches = um.searchUsersByPrefix("A");
    std::cout << "Users starting with 'A':\n";
    for (int i = 0; i < matches.size(); i++)
        std::cout << matches.get(i) << "\n";

    // Test posts
    u1->createPost("Hello world!");
    u1->createPost("My second post");
    std::cout << u1->getName() << "'s posts:\n";
    for (int i = 0; i < u1->getPosts().size(); i++)
        std::cout << "- " << u1->getPosts().get(i) << "\n";

    // Delete post
    u1->deletePost(0);
    std::cout << "After deleting first post:\n";
    for (int i = 0; i < u1->getPosts().size(); i++)
        std::cout << "- " << u1->getPosts().get(i) << "\n";

    return 0;
}
