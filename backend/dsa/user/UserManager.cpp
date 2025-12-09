#include "UserManager.h"
#include "../containers/Queue.h"
#include "../containers/HashMap.h"
#include "../../algorithms/BFS.h"
#include "../../algorithms/DFS.h"
#include "../../analytics/Graphstats.h"  
#include <iostream>
#include "../../libs/crow/nlohmann/json.hpp"
#include <fstream>
#include <direct.h>
using json = nlohmann::json;
UserManager::UserManager(const std::string& filePath) : dbFilePath(filePath) {
    loadFromFile();
}
// Load users from JSON file
void UserManager::loadFromFile() {
    std::ifstream file(dbFilePath);
    
    if (!file.is_open()) {
        std::cout << "No existing database found at " << dbFilePath << ". Starting fresh." << std::endl;
        return;
    }
    
    try {
        json data;
        file >> data;
        file.close();
        
        // Load users
        if (data.contains("users") && data["users"].is_array()) {
            for (const auto& userJson : data["users"]) {
                std::string username = userJson["username"];
                std::string password = userJson["password"];
                int id = userJson["id"];
                
                // Create user (will auto-assign ID, but we'll use the saved one)
                User user(username, password);
                users.push_back(user);
                usernameTrie.insert(username);
                socialGraph.addNode(id);
                
                // Load posts if they exist
                if (userJson.contains("posts") && userJson["posts"].is_array()) {
                    User* loadedUser = &users.get(users.size() - 1);
                    for (const auto& post : userJson["posts"]) {
                        loadedUser->createPost(post);
                    }
                }
            }
        }
        
        // Load connections/friendships
        if (data.contains("connections") && data["connections"].is_array()) {
            for (const auto& conn : data["connections"]) {
                int userA = conn["userA"];
                int userB = conn["userB"];
                if (socialGraph.hasNode(userA) && socialGraph.hasNode(userB)) {
                    socialGraph.addEdge(userA, userB, 1, true);
                }
            }
        }
        
        std::cout << "Loaded " << users.size() << " users from database." << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error loading database: " << e.what() << std::endl;
    }
}

// Save users to JSON file
void UserManager::saveToFile() {
    // Extract directory path from dbFilePath and create directories if they don't exist
    std::string path = dbFilePath;
    size_t lastSlash = path.find_last_of("/\\");
    if (lastSlash != std::string::npos) {
        std::string dirPath = path.substr(0, lastSlash);
        // Create parent directories recursively
        size_t pos = 0;
        while ((pos = dirPath.find_first_of("/\\", pos)) != std::string::npos) {
            std::string subDir = dirPath.substr(0, pos);
            _mkdir(subDir.c_str());
            pos++;
        }
        _mkdir(dirPath.c_str());
    }
    
    json data;
    json usersArray = json::array();
    json connectionsArray = json::array();
    
    // Save users
    for (int i = 0; i < users.size(); i++) {
        User& user = users.get(i);
        json userJson;
        
        userJson["id"] = user.getId();
        userJson["username"] = user.getName();
        userJson["password"] = user.getPassword();
        
        // Save posts
        json postsArray = json::array();
        DynamicArray<std::string>& posts = user.getPosts();
        for (int j = 0; j < posts.size(); j++) {
            postsArray.push_back(posts.get(j));
        }
        userJson["posts"] = postsArray;
        
        usersArray.push_back(userJson);
        
        // Save connections (only save once per edge)
        if (socialGraph.hasNode(user.getId())) {
            const LinkedList<Edge>& neighbors = socialGraph.getNeighbors(user.getId());
            for (int j = 0; j < neighbors.size(); j++) {
                int friendId = neighbors[j].to;
                // Only save if current user ID < friend ID (to avoid duplicates)
                if (user.getId() < friendId) {
                    json conn;
                    conn["userA"] = user.getId();
                    conn["userB"] = friendId;
                    connectionsArray.push_back(conn);
                }
            }
        }
    }
    
    data["users"] = usersArray;
    data["connections"] = connectionsArray;
    
    // Write to file
    std::ofstream file(dbFilePath);
    if (file.is_open()) {
        file << data.dump(4);  // Pretty print with 4 spaces
        file.close();
        std::cout << "Saved " << users.size() << " users to database." << std::endl;
    } else {
        std::cerr << "Error: Could not open file for writing: " << dbFilePath << std::endl;
    }
}

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
    saveToFile();
}

// Get all users (const access)
const DynamicArray<User>& UserManager::getAllUsers() const {
    return users;
}

// Construct and return the social graph (non-const version)
Graph& UserManager::constructGraph() {
    return socialGraph;
}

// Construct and return the social graph (const version)
const Graph& UserManager::constructGraph() const {
    return socialGraph;
}

bool UserManager::removeUserById(int id) {
    int idx = getUserIndexById(id);
    if (idx == -1) return false;
    // Get username BEFORE deleting user
    std::string username = users.get(idx).getName();
    // Remove from social graph
    if (socialGraph.hasNode(id)) {
        socialGraph.removeNode(id);
    }
    // REMOVE FROM TRIE
    usernameTrie.remove(username);
    // Remove from array (swap with last)
    users.get(idx) = users.get(users.size() - 1);
    users.pop_back();
    saveToFile();
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
    saveToFile();
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
    
    return DFS::existsPath(socialGraph, userAId, userBId);  //    Use YOUR DFS!
}

// Get degrees of separation (using YOUR BFS!)
int UserManager::degreesOfSeparation(int userAId, int userBId) {
    if (!socialGraph.hasNode(userAId) || !socialGraph.hasNode(userBId))
        return -1;
    
    return BFS::distance(socialGraph, userAId, userBId);  //    Use YOUR BFS!
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

bool UserManager::createPostForUser(int userId, const std::string& content) {
    User* user = getUserById(userId);
    if (!user) return false;
    
    user->createPost(content);
    saveToFile();
    return true;
}

bool UserManager::deletePostForUser(int userId, int postIndex) {
    User* user = getUserById(userId);
    if (!user) return false;
    
    bool success = user->deletePost(postIndex);
    if (success) {
        saveToFile();
    }
    return success;
}
