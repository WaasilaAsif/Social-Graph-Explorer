#include <fstream>
#include <iostream>
#include "../libs/crow/nlohmann/json.hpp"
#include "../dsa/user/UserManager.h"
#include "../dsa/graph/Graph.h"
#include "../messaging/MessageStore.h"
#include "../dsa/messaging_ds/MsgTrie.h"
#include "../dsa/messaging_ds/ConversationGraph.h"

using json = nlohmann::json;

void loadUsersFromJSON(UserManager& userManager, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filepath << std::endl;
        return;
    }

    try {
        json data = json::parse(file);
        
        if (!data.contains("users") || !data["users"].is_array()) {
            std::cerr << "Warning: Invalid users.json format" << std::endl;
            return;
        }

        for (const auto& userObj : data["users"]) {
            std::string username = userObj["username"];
            std::string password = userObj["password"];
            
            userManager.addUser(username, password);
            
            // Add posts if they exist
            if (userObj.contains("posts") && userObj["posts"].is_array()) {
                User* user = userManager.getUserById(userObj["id"]);
                if (user) {
                    for (const auto& post : userObj["posts"]) {
                        user->createPost(post.get<std::string>());
                    }
                }
            }
        }
        
        std::cout << "  Loaded " << data["users"].size() << " users from " << filepath << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error parsing users.json: " << e.what() << std::endl;
    }
    
    file.close();
}

void loadFriendshipsFromJSON(Graph& graph, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filepath << std::endl;
        return;
    }

    try {
        json data = json::parse(file);
        
        if (!data.contains("friendships") || !data["friendships"].is_array()) {
            std::cerr << "Warning: Invalid friendships.json format" << std::endl;
            return;
        }

        int count = 0;
        for (const auto& friendship : data["friendships"]) {
            int user1 = friendship["user1"];
            int user2 = friendship["user2"];
            
            // Add nodes if they don't exist
            if (!graph.hasNode(user1)) {
                graph.addNode(user1);
            }
            if (!graph.hasNode(user2)) {
                graph.addNode(user2);
            }
            
            // Add edge (friendship)
            if (!graph.hasEdge(user1, user2)) {
                graph.addEdge(user1, user2);
                count++;
            }
        }
        
        std::cout << "  Loaded " << count << " friendships from " << filepath << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error parsing friendships.json: " << e.what() << std::endl;
    }
    
    file.close();
}

void loadMessagesFromJSON(MessageStore& msgStore, MsgTrie& msgTrie, ConversationGraph& convGraph, const std::string& filepath) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open " << filepath << std::endl;
        return;
    }

    try {
        json data = json::parse(file);
        
        if (!data.contains("messages") || !data["messages"].is_array()) {
            std::cerr << "Warning: Invalid messages.json format" << std::endl;
            return;
        }

        for (const auto& msgObj : data["messages"]) {
            int senderId = msgObj["senderId"];
            int receiverId = msgObj["receiverId"];
            std::string text = msgObj["text"];
            
            // Add to message store
            int msgId = msgStore.addMessage(senderId, receiverId, text);
            
            // Extract words and add to trie
            auto words = msgStore.extractWords(text);
            for (int i = 0; i < words.size(); i++) {
                msgTrie.insert(words.get(i), msgId);
            }
            
            // Add interaction to conversation graph
            convGraph.addInteraction(senderId, receiverId);
        }
        
        std::cout << "  Loaded " << data["messages"].size() << " messages from " << filepath << std::endl;
        
    } catch (const std::exception& e) {
        std::cerr << "Error parsing messages.json: " << e.what() << std::endl;
    }
    
    file.close();
}