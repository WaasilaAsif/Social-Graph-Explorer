#pragma once
#include <string>
#include "User.h"
#include "../containers/DynamicArray.h"
#include "../containers/Trie.h"
#include "../containers/HashMap.h"
#include "../graph/Graph.h"

class UserManager {
private:
    DynamicArray<User> users;
    Trie usernameTrie;
    Graph socialGraph;

    std::string dbFilePath;   // <-- YOU FORGOT THIS IN .h

    int getUserIndexById(int id);

public:

    // Constructor with file path
    UserManager(const std::string& filePath);

    // Load/save
    void loadFromFile();
    void saveToFile();

    // User management

    void addUser(const std::string& name, const std::string& password);
    bool removeUserById(int id);
    User* getUserById(int id);
    User* login(const std::string& username, const std::string& password);

    // Posts
    bool createPostForUser(int userId, const std::string& content);
    bool deletePostForUser(int userId, int postIndex);

    // Searching
    DynamicArray<std::string> searchUsersByPrefix(const std::string& prefix);

    // Social graph
    void makeConnection(int userAId, int userBId);
    DynamicArray<User*> friendSuggestions(int userId);
    DynamicArray<User*> shortestPath(int userAId, int userBId);
    DynamicArray<User*> getFriends(int userId);
    DynamicArray<User*> getMutualFriends(int userAId, int userBId);
    bool areConnected(int userAId, int userBId);
    int degreesOfSeparation(int userAId, int userBId);
    int getFriendCount(int userId);

    // Analytics
    void printNetworkStats();
    User* getMostPopularUser();
};
