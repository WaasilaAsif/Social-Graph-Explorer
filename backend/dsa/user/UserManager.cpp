<<<<<<< HEAD
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




=======
#include "UserManager.h"
#include "../containers/Queue.h"
#include "../containers/HashMap.h"
#include "../../algorithms/BFS.h"
#include "../../algorithms/DFS.h"
#include "../../algorithms/GraphStats.h"
#include <iostream>

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
    User newUser(name, password);
    users.push_back(newUser);
    usernameTrie.insert(name);
    
    // *** ADD: Add user to social graph ***
    socialGraph.addNode(newUser.getId());
}

// Remove user by ID
bool UserManager::removeUserById(int id) {
    int idx = getUserIndexById(id);
    if (idx == -1) return false;
    
    // *** ADD: Remove from social graph ***
    if (socialGraph.hasNode(id)) {
        socialGraph.removeNode(id);
    }
    
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
    // Linear search over DynamicArray<User>
    for (int i = 0; i < users.size(); i++) {
        if (users.get(i).getName() == username &&
            users.get(i).getPassword() == password) {
            return &users.get(i); // login success
        }
    }
    return nullptr; // not found or password wrong
}

// *** IMPLEMENTATION: Make a connection between two users ***
void UserManager::makeConnection(int userAId, int userBId) {
    User* userA = getUserById(userAId);
    User* userB = getUserById(userBId);
    
    if (!userA || !userB) {
        throw std::runtime_error("One or both users do not exist");
    }
    
    // Add nodes if they don't exist
    if (!socialGraph.hasNode(userAId)) {
        socialGraph.addNode(userAId);
    }
    if (!socialGraph.hasNode(userBId)) {
        socialGraph.addNode(userBId);
    }
    
    // Add undirected edge (friendship is mutual)
    if (!socialGraph.hasEdge(userAId, userBId)) {
        socialGraph.addEdge(userAId, userBId, 1, true);
    }
}

// *** IMPLEMENTATION: Friend suggestions - users who are friends of friends but not direct friends ***
DynamicArray<User*> UserManager::friendSuggestions(int userId) {
    DynamicArray<User*> suggestions;
    
    User* user = getUserById(userId);
    if (!user) return suggestions;
    
    if (!socialGraph.hasNode(userId)) return suggestions;
    
    // Get direct friends
    HashMap<int, bool> directFriends(50);
    directFriends.put(userId, true);  // Mark self
    
    const LinkedList<Edge>& friends = socialGraph.getNeighbors(userId);
    for (int i = 0; i < friends.size(); i++) {
        int friendId = friends[i].to;
        directFriends.put(friendId, true);
    }
    
    // Check friends of friends
    HashMap<int, bool> suggested(50);
    for (int i = 0; i < friends.size(); i++) {
        int friendId = friends[i].to;
        const LinkedList<Edge>& friendsOfFriend = socialGraph.getNeighbors(friendId);
        
        for (int j = 0; j < friendsOfFriend.size(); j++) {
            int fofId = friendsOfFriend[j].to;
            
            // If not a direct friend and not already suggested
            if (!directFriends.contains(fofId) && !suggested.contains(fofId)) {
                User* suggestedUser = getUserById(fofId);
                if (suggestedUser) {
                    suggestions.push_back(suggestedUser);
                    suggested.put(fofId, true);
                }
            }
        }
    }
    
    return suggestions;
}

DynamicArray<User*> UserManager::shortestPath(int userAId, int userBId) {
    DynamicArray<User*> path;
    
    // Call YOUR BFS algorithm!
    LinkedList<int> pathIds = BFS::shortestPath(socialGraph, userAId, userBId);
    
    // Convert IDs to User pointers
    for (int i = 0; i < pathIds.size(); i++) {
        User* user = getUserById(pathIds[i]);
        if (user) path.push_back(user);
    }
    
    return path;
}
// *** SUGGESTION: Add these to UserManager ***

// Get all friends (direct connections)
DynamicArray<User*> UserManager::getFriends(int userId) {
    DynamicArray<User*> friends;
    
    if (!socialGraph.hasNode(userId)) return friends;
    
    const LinkedList<Edge>& edges = socialGraph.getNeighbors(userId);
    for (int i = 0; i < edges.size(); i++) {
        User* user = getUserById(edges[i].to);
        if (user) friends.push_back(user);
    }
    
    return friends;
}

// Get mutual friends between two users
DynamicArray<User*> UserManager::getMutualFriends(int userAId, int userBId) {
    DynamicArray<User*> mutual;
    
    if (!socialGraph.hasNode(userAId) || !socialGraph.hasNode(userBId))
        return mutual;
    
    // Get friends of both users
    const LinkedList<Edge>& friendsA = socialGraph.getNeighbors(userAId);
    const LinkedList<Edge>& friendsB = socialGraph.getNeighbors(userBId);
    
    // Find intersection
    HashMap<int, bool> friendsAMap(50);
    for (int i = 0; i < friendsA.size(); i++) {
        friendsAMap.put(friendsA[i].to, true);
    }
    
    for (int i = 0; i < friendsB.size(); i++) {
        int friendId = friendsB[i].to;
        if (friendsAMap.contains(friendId)) {
            User* user = getUserById(friendId);
            if (user) mutual.push_back(user);
        }
    }
    
    return mutual;
}

// Check if two users are connected (using YOUR DFS!)
bool UserManager::areConnected(int userAId, int userBId) {
    if (!socialGraph.hasNode(userAId) || !socialGraph.hasNode(userBId))
        return false;
    
    return DFS::existsPath(socialGraph, userAId, userBId);  // ✅ Use YOUR DFS!
}

// Get degrees of separation (using YOUR BFS!)
int UserManager::degreesOfSeparation(int userAId, int userBId) {
    if (!socialGraph.hasNode(userAId) || !socialGraph.hasNode(userBId))
        return -1;
    
    return BFS::distance(socialGraph, userAId, userBId);  // ✅ Use YOUR BFS!
}

// Get friend count
int UserManager::getFriendCount(int userId) {
    if (!socialGraph.hasNode(userId)) return 0;
    return socialGraph.getNeighbors(userId).size();
}
// Get network statistics
void UserManager::printNetworkStats() {
    std::cout << "=== Social Network Statistics ===\n";
    std::cout << "Total users: " << users.size() << "\n";
    std::cout << "Total friendships: " << GraphStats::countEdges(socialGraph, true) << "\n";
    std::cout << "Average friends per user: " << GraphStats::getAverageDegree(socialGraph) << "\n";
    std::cout << "Network density: " << GraphStats::getDensity(socialGraph) << "\n";
    std::cout << "Is connected: " << (GraphStats::isConnected(socialGraph) ? "Yes" : "No") << "\n";
}

// Find most popular user
User* UserManager::getMostPopularUser() {
    if (socialGraph.nodeCount() == 0) return nullptr;
    
    int mostPopularId = GraphStats::findMostConnectedNode(socialGraph);
    return getUserById(mostPopularId);
}
>>>>>>> origin/aman-branch
