#include "UserManager.h"
#include "../containers/Queue.h"
#include "../containers/Queue.cpp"
#include "../containers/HashMap.h"
#include "../containers/HashMap.cpp"
#include <algorithm>
#include <iostream>
#include "../containers/HashMap.h"
UserManager::UserManager() {}

// Helper: get index of user in DynamicArray
int UserManager::getUserIndexById(int id) {
    for (int i = 0; i < users.size(); i++)
        if (users.get(i).getId() == id)
            return i;
    return -1; // not found
}

// Add a new user
void UserManager::addUser(const std::string& name, const std::string& password) {
    users.push_back(User(name, password));
    usernameTrie.insert(name);
}

// Remove user by ID
bool UserManager::removeUserById(int id) {
    int idx = getUserIndexById(id);
    if (idx == -1) return false;
    users.get(idx) = users.get(users.size() - 1); // swap with last
    users.pop_back();
    return true;
}

// Get user pointer by ID
User* UserManager::getUserById(int id) {
    int idx = getUserIndexById(id);
    if (idx == -1) return nullptr;
    return &users.get(idx);
}

// Search users by prefix
DynamicArray<std::string> UserManager::searchUsersByPrefix(const std::string& prefix) {
    return usernameTrie.startsWith(prefix);
}
User* UserManager::login(const std::string& username, const std::string& password) {
    std::string uname = toLower(username);
    // Linear search over DynamicArray<User>
    for (int i = 0; i < users.size(); i++) {
        if (toLower(users.get(i).getName()) == uname &&
            users.get(i).getPassword() == password) {
            return &users.get(i); // login success
        }
    }
    return nullptr; // not found or password wrong
}



//ADD MISSING FUNCTIONS HERE




