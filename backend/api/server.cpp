// server.cpp
#include "routes/graphRoutes.h"
#include "routes/MsgRoutes.h"
#include "routes/MsgAPI.h"
#include "routes/UserRouter.h"
#include "../dsa/graph/Graph.h"
#include "../dsa/user/UserManager.h"
#include "../messaging/MessageStore.h"
#include "../dsa/messaging_ds/MsgTrie.h"
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../storage/JSONLoader.h"
#include "../libs/crow/crow_all.h"
#include <iostream>

int main() {
    crow::SimpleApp app;

    // Graph instance
    Graph graph;

    // Messaging instances
    UserManager userManager;
    MessageStore msgStore;
    MsgTrie msgTrie;
    ConversationGraph convGraph;
    
    // Load data from JSON files
    std::cout << "Loading data from JSON files..." << std::endl;
    loadUsersFromJSON(userManager, "storage/local_db/users.json");
    loadFriendshipsFromJSON(graph, "storage/local_db/friendships.json");
    loadMessagesFromJSON(msgStore, msgTrie, convGraph, "storage/local_db/messages.json");
    std::cout << "Data loaded successfully!" << std::endl << std::endl;
    
    // Create API instances
    MsgAPI msgApi(&userManager, &msgStore, &msgTrie, &convGraph);

    // Register graph routes
    GraphRoutes graphRoutes(graph);
    graphRoutes.registerRoutes(app);
    
    // Register messaging routes
    MsgRoutes msgRoutes(&msgApi);
    msgRoutes.registerRoutes(app);
    
    // Register user routes
    UserRouter userRouter(userManager);
    userRouter.setupRoutes(app);

    // Root - API Menu
    CROW_ROUTE(app, "/")
    ([]() {
        crow::json::wvalue menu;
        menu["server"] = "Social Network Graph API";
        menu["port"] = 8081;
        menu["status"] = "running";
        
        // Graph endpoints
        menu["endpoints"]["graph"]["friends"] = "GET /graph/friends/:id";
        menu["endpoints"]["graph"]["addFriend"] = "POST /graph/addFriend - Body: {u, v}";
        menu["endpoints"]["graph"]["removeFriend"] = "POST /graph/removeFriend - Body: {u, v}";
        menu["endpoints"]["graph"]["stats"] = "GET /graph/stats";
        menu["endpoints"]["graph"]["connected"] = "GET /graph/connected/:u/:v";
        menu["endpoints"]["graph"]["components"] = "GET /graph/components";
        
        // Messaging endpoints
        menu["endpoints"]["messaging"]["send"] = "POST /msg/send - Body: {senderId, receiverId, text}";
        menu["endpoints"]["messaging"]["search"] = "GET /msg/search/:word";
        menu["endpoints"]["messaging"]["prefix"] = "GET /msg/prefix/:prefix";
        menu["endpoints"]["messaging"]["topk"] = "GET /msg/topk/:userId/:k";
        menu["endpoints"]["messaging"]["suggestions"] = "GET /msg/suggestions/:userId/:k";
        menu["endpoints"]["messaging"]["mutual"] = "GET /msg/mutual/:userId";
        menu["endpoints"]["messaging"]["rank"] = "GET /msg/rank/:topN";
        menu["endpoints"]["messaging"]["path"] = "GET /msg/path/:src/:dest";
        
        // User endpoints
        menu["endpoints"]["users"]["register"] = "POST /api/users/register - Body: {username, password}";
        menu["endpoints"]["users"]["login"] = "POST /api/users/login - Body: {username, password}";
        menu["endpoints"]["users"]["search"] = "GET /api/users/search?prefix=...";
        menu["endpoints"]["users"]["getUser"] = "GET /api/users/:id";
        menu["endpoints"]["users"]["deleteUser"] = "DELETE /api/users/:id";
        menu["endpoints"]["users"]["createPost"] = "POST /api/users/:id/posts - Body: {content}";
        menu["endpoints"]["users"]["getPosts"] = "GET /api/users/:id/posts";
        menu["endpoints"]["users"]["deletePost"] = "DELETE /api/users/:id/posts/:postIndex";
        
        // Health
        menu["endpoints"]["health"] = "GET /health";
        
        crow::response res(menu);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // Health check
    CROW_ROUTE(app, "/health")
    ([]() {
        crow::json::wvalue response;
        response["status"] = "ok";
        response["message"] = "Server is running";
        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // CORS preflight for specific endpoints
    CROW_ROUTE(app, "/graph/addFriend").methods(crow::HTTPMethod::Options)
    ([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    CROW_ROUTE(app, "/graph/removeFriend").methods(crow::HTTPMethod::Options)
    ([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });

    // Logging
    app.loglevel(crow::LogLevel::Warning);

    // Start server
    std::cout << "========================================" << std::endl;
    std::cout << " Social Network Graph API Server" << std::endl;
    std::cout << "Listening on: http://localhost:8081" << std::endl;
    std::cout << "Graph routes registered" << std::endl;
    std::cout << "Messaging routes registered" << std::endl;
    std::cout << "User routes registered" << std::endl;
    std::cout << "Server ready!" << std::endl;
    std::cout << "========================================" << std::endl;

    app.port(8081).multithreaded().run();

    return 0;
}
