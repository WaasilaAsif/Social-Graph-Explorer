#include <fstream>
#include <iostream>
#include "../libs/crow/nlohmann/json.hpp"
#include "../dsa/user/UserManager.h"
#include "../dsa/graph/Graph.h"

using json = nlohmann::json;

void saveUsersToJSON(const UserManager& userManager, const std::string& filepath) {
    json data;
    data["users"] = json::array();
    // Save all users
    const DynamicArray<User>& users = userManager.getUsers();
    for (int i = 0; i < users.size(); ++i) {
        const User& user = users.get(i);
        json userObj;
        userObj["id"] = user.getId();
        userObj["username"] = user.getName();
        userObj["password"] = user.getPassword();
        // Save posts
        userObj["posts"] = json::array();
        const DynamicArray<std::string>& posts = user.getPosts();
        for (int j = 0; j < posts.size(); ++j) {
            userObj["posts"].push_back(posts.get(j));
        }
        data["users"].push_back(userObj);
    }
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filepath << " for writing." << std::endl;
        return;
    }
    file << data.dump(4);
    file.close();
    std::cout << "✓ Saved users to " << filepath << std::endl;
}

void saveFriendshipsToJSON(const Graph& graph, const std::string& filepath) {
    json data;
    data["friendships"] = json::array();
    LinkedList<int> allIds = graph.getAllNodeIDs();
    for (int i = 0; i < allIds.size(); ++i) {
        int from = allIds.at(i);
        const LinkedList<Edge>& edges = graph.getNeighbors(from);
        for (int j = 0; j < edges.size(); ++j) {
            int to = edges.at(j).to;
            if (from < to) { // Avoid duplicate undirected edges
                json edgeObj;
                edgeObj["user1"] = from;
                edgeObj["user2"] = to;
                data["friendships"].push_back(edgeObj);
            }
        }
    }
    std::ofstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filepath << " for writing." << std::endl;
        return;
    }
    file << data.dump(4);
    file.close();
    std::cout << "✓ Saved friendships to " << filepath << std::endl;
}
