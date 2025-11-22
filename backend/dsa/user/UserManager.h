#pragma once
#include <string>
#include "User.h"
#include "../containers/DynamicArray.h"
#include "../containers/Trie.h"
#include "../containers/HashMap.h"

class UserManager {
private:
    DynamicArray<User> users;
    
    Trie usernameTrie;            // for searching by name
    int getUserIndexById(int id);

public:
    UserManager();
    // Add/remove users
    void addUser(const std::string& name, const std::string& password);
    bool removeUserById(int id);
    // Get user
    User* getUserById(int id);
    // Search users by name prefix
    DynamicArray<std::string> searchUsersByPrefix(const std::string& prefix);
    User*login(const std::string& username, const std::string& password);
    // Connections
    void makeConnection(int userAId, int userBId);
    // Graph-based operations
    DynamicArray<User*> friendSuggestions(int userId);
    DynamicArray<User*> shortestPath(int userAId, int userBId);
};
