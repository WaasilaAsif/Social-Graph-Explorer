// server.cpp
#include "routes/graphRoutes.h"
#include "../dsa/graph/Graph.h"
#include <crow.h>  // vcpkg Crow 1.3.0
#include <iostream>

int main() {
    crow::SimpleApp app;

    // Graph instance
    Graph graph;

    // Register graph routes
    GraphRoutes graphRoutes(graph);
    graphRoutes.registerRoutes(app);

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

    // Root endpoint
    CROW_ROUTE(app, "/")
    ([]() {
        std::string html = R"(
<!DOCTYPE html>
<html>
<head>
    <title>Social Network Graph API</title>
    <style>
        body { font-family: Arial, sans-serif; max-width: 800px; margin: 50px auto; padding: 20px; }
        h1 { color: #333; }
        .endpoint { background: #f4f4f4; padding: 10px; margin: 10px 0; border-radius: 5px; }
        .method { color: #fff; padding: 3px 8px; border-radius: 3px; font-size: 12px; }
        .get { background: #61affe; }
        .post { background: #49cc90; }
        code { background: #f4f4f4; padding: 2px 6px; border-radius: 3px; }
    </style>
</head>
<body>
    <h1>🚀 Social Network Graph API</h1>
    <p>Server is running successfully!</p>
    
    <h2>📡 Available Endpoints:</h2>
    
    <div class="endpoint">
        <span class="method get">GET</span> <code>/health</code>
        <p>Check server health</p>
    </div>
    
    <div class="endpoint">
        <span class="method get">GET</span> <code>/graph/friends/:id</code>
        <p>Get friends list for a user</p>
    </div>
    
    <div class="endpoint">
        <span class="method post">POST</span> <code>/graph/addFriend</code>
        <p>Add friendship between two users<br>Body: <code>{"u":1, "v":2}</code></p>
    </div>
    
    <div class="endpoint">
        <span class="method post">POST</span> <code>/graph/removeFriend</code>
        <p>Remove friendship between two users<br>Body: <code>{"u":1, "v":2}</code></p>
    </div>
    
    <div class="endpoint">
        <span class="method get">GET</span> <code>/graph/stats</code>
        <p>Get graph statistics</p>
    </div>
    
    <div class="endpoint">
        <span class="method get">GET</span> <code>/graph/connected/:u/:v</code>
        <p>Check if two users are connected</p>
    </div>
    
    <div class="endpoint">
        <span class="method get">GET</span> <code>/graph/components</code>
        <p>Get number of connected components</p>
    </div>
    
    <h2>🧪 Quick Test:</h2>
    <p>Try: <a href="/health">/health</a></p>
</body>
</html>
        )";
        crow::response res(html);
        res.add_header("Content-Type", "text/html");
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
    std::cout << "🚀 Social Network Graph API Server" << std::endl;
    std::cout << "📡 Listening on: http://localhost:8080" << std::endl;
    std::cout << "📊 Graph routes registered" << std::endl;
    std::cout << "🔥 Server ready!" << std::endl;
    std::cout << "========================================" << std::endl;

    app.port(8080).multithreaded().run();

    return 0;
}
