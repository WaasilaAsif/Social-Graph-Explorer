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

// Algorithm modules
#include "../algorithms/MutualFriends.h"
#include "../algorithms/ShortestPath.h"
#include "../analytics/GraphStats.h"
#include "../analytics/PopularityRanker.h"
#include "../algorithms/FriendSuggestion.h"

// Forward declaration
void setupAlgoRoutes(crow::SimpleApp& app, Graph* graph, 
                     MutualFriends* mutualFriends,
                     ShortestPath* shortestPath,
                     GraphStats* graphStats,
                     PopularityRanker* popularityRanker,
                     FriendSuggestion* friendSuggestion);

int main() {
    crow::SimpleApp app;

    // Messaging instances
    UserManager userManager("../storage/local_db/users.json");
    MessageStore msgStore;
    MsgTrie msgTrie;
    ConversationGraph convGraph;
    
    // Load data from JSON files
    std::cout << "Loading data from JSON files..." << std::endl;
    loadFriendshipsFromJSON(userManager.constructGraph(), "../storage/local_db/friendships.json");
    // UserManager already loads users in its constructor, so no need to load again
    loadMessagesFromJSON(msgStore, msgTrie, convGraph, "../storage/local_db/messages.json");
    std::cout << "Data loaded successfully!" << std::endl << std::endl;
    
    // Create API instances
    MsgAPI msgApi(&userManager, &msgStore, &msgTrie, &convGraph);

    // Initialize algorithm modules
    MutualFriends mutualFriends(&userManager.constructGraph());
    ShortestPath shortestPath(&userManager.constructGraph());
    GraphStats graphStats;
    PopularityRanker popularityRanker(&userManager.constructGraph());
    FriendSuggestion friendSuggestion(&userManager.constructGraph(), &mutualFriends);

    // CORS preflight handlers MUST be registered BEFORE the actual routes
    CROW_ROUTE(app, "/api/users/register").methods(crow::HTTPMethod::Options)
    ([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 204;
        return res;
    });

    CROW_ROUTE(app, "/api/users/login").methods(crow::HTTPMethod::Options)
    ([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.code = 204;
        return res;
    });

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

    // Register graph routes
    GraphRoutes graphRoutes(userManager.constructGraph(), userManager);
    graphRoutes.registerRoutes(app);
    
    // Register messaging routes
    MsgRoutes msgRoutes(&msgApi);
    msgRoutes.registerRoutes(app);
    
    // Register user routes
    UserRouter userRouter(userManager);
    userRouter.setupRoutes(app);
    
    // Register algorithm routes
    setupAlgoRoutes(app, &userManager.constructGraph(), &mutualFriends, &shortestPath, 
                    &graphStats, &popularityRanker, &friendSuggestion);

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
        menu["endpoints"]["graph"]["bfs"] = "GET /graph/bfs/:start - BFS traversal";
        menu["endpoints"]["graph"]["dfs"] = "GET /graph/dfs/:start - DFS traversal";
        menu["endpoints"]["graph"]["shortestPath"] = "GET /graph/shortest-path/:src/:dest - Shortest path";
        
        // Messaging endpoints
        menu["endpoints"]["messaging"]["send"] = "POST /msg/send - Body: {senderId, receiverId, text}";
        menu["endpoints"]["messaging"]["search"] = "GET /msg/search/:word - Search messages by word";
        menu["endpoints"]["messaging"]["prefix"] = "GET /msg/prefix/:prefix - Search by prefix";
        menu["endpoints"]["messaging"]["topk"] = "GET /msg/topk/:userId/:k - Top K conversations";
        menu["endpoints"]["messaging"]["suggestions"] = "GET /msg/suggestions/:userId/:k - Friend suggestions";
        menu["endpoints"]["messaging"]["mutual"] = "GET /msg/mutual/:userId - Mutual interactions";
        menu["endpoints"]["messaging"]["rank"] = "GET /msg/rank/:topN - Top N active users";
        menu["endpoints"]["messaging"]["path"] = "GET /msg/path/:src/:dest - Messaging path";
        
        // User endpoints
        menu["endpoints"]["users"]["register"] = "POST /api/users/register - Body: {username, password}";
        menu["endpoints"]["users"]["login"] = "POST /api/users/login - Body: {username, password}";
        menu["endpoints"]["users"]["search"] = "GET /api/users/search?prefix=...";
        menu["endpoints"]["users"]["getUser"] = "GET /api/users/:id";
        menu["endpoints"]["users"]["deleteUser"] = "DELETE /api/users/:id";
        menu["endpoints"]["users"]["createPost"] = "POST /api/users/:id/posts - Body: {content}";
        menu["endpoints"]["users"]["getPosts"] = "GET /api/users/:id/posts";
        menu["endpoints"]["users"]["deletePost"] = "DELETE /api/users/:id/posts/:postIndex";
        
        // Algorithm endpoints
        menu["endpoints"]["algorithms"]["mutualFriends"] = "GET /api/algo/mutual-friends?user1=X&user2=Y - Find common friends";
        menu["endpoints"]["algorithms"]["shortestPath"] = "GET /api/algo/shortest-path?start=X&end=Y - Find shortest connection path";
        menu["endpoints"]["algorithms"]["usersWithinDistance"] = "GET /api/algo/users-within-distance?userId=X&distance=N - Find users N hops away";
        menu["endpoints"]["algorithms"]["userDegree"] = "GET /api/algo/user-degree?userId=X - Get friend count";
        menu["endpoints"]["algorithms"]["graphStats"] = "GET /api/algo/graph-stats - Network statistics & metrics";
        menu["endpoints"]["algorithms"]["topPopular"] = "GET /api/algo/top-popular?n=10 - Most connected users";
        menu["endpoints"]["algorithms"]["userRank"] = "GET /api/algo/user-rank?userId=X - User popularity ranking";
        menu["endpoints"]["algorithms"]["friendSuggestions"] = "GET /api/algo/friend-suggestions?userId=X&limit=10 - AI friend recommendations";
        menu["endpoints"]["algorithms"]["twoHopFriends"] = "GET /api/algo/two-hop-friends?userId=X - Friends of friends";
        menu["endpoints"]["algorithms"]["unitTests"] = "GET /api/algo/unit-tests - Run algorithm test suite";
        
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

    // Logging
    app.loglevel(crow::LogLevel::Warning);

    // Start server
    std::cout << "========================================" << std::endl;
    std::cout << " Social Network Graph API Server" << std::endl;
    std::cout << "Listening on: http://localhost:8081" << std::endl;
    std::cout << "Graph routes registered" << std::endl;
    std::cout << "Messaging routes registered" << std::endl;
    std::cout << "User routes registered" << std::endl;
    std::cout << "Algorithm routes registered" << std::endl;
    std::cout << "Server ready!" << std::endl;
    std::cout << "========================================" << std::endl;

    app.port(8081).multithreaded().run();

    return 0;
}
