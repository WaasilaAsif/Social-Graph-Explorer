#include "MsgRoutes.h"
#include <crow.h>

MsgRoutes::MsgRoutes(MsgAPI* api) : msgApi(api) {}

void MsgRoutes::registerRoutes(crow::SimpleApp& app) {
    
    // 1. Send Message
    CROW_ROUTE(app, "/msg/send").methods(crow::HTTPMethod::Post)
    ([this](const crow::request& req) {
        auto body = crow::json::load(req.body);
        if (!body) {
            return crow::response(400, "Invalid JSON");
        }

        std::unordered_map<std::string, std::string> params;
        params["senderId"] = std::to_string(body["senderId"].i());
        params["receiverId"] = std::to_string(body["receiverId"].i());
        params["text"] = body["text"].s();

        std::string result = msgApi->handleSendMessage(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 2. Search Word
    CROW_ROUTE(app, "/msg/search/<string>")
    ([this](const std::string& query) {
        std::unordered_map<std::string, std::string> params;
        params["query"] = query;

        std::string result = msgApi->handleSearchWord(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 3. Search Prefix
    CROW_ROUTE(app, "/msg/prefix/<string>")
    ([this](const std::string& query) {
        std::unordered_map<std::string, std::string> params;
        params["query"] = query;

        std::string result = msgApi->handleSearchPrefix(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 4. Top K Messages
    CROW_ROUTE(app, "/msg/topk/<int>/<int>")
    ([this](int userId, int k) {
        std::unordered_map<std::string, std::string> params;
        params["user"] = std::to_string(userId);
        params["k"] = std::to_string(k);

        std::string result = msgApi->handleTopK(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 5. Friend Suggestions
    CROW_ROUTE(app, "/msg/suggestions/<int>/<int>")
    ([this](int userId, int k) {
        std::unordered_map<std::string, std::string> params;
        params["user"] = std::to_string(userId);
        params["k"] = std::to_string(k);

        std::string result = msgApi->handleFriendSuggestion(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 6. Mutual Interactions
    CROW_ROUTE(app, "/msg/mutual/<int>")
    ([this](int userId) {
        std::unordered_map<std::string, std::string> params;
        params["user"] = std::to_string(userId);

        std::string result = msgApi->handleMutualInteractions(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 7. Popularity Ranking
    CROW_ROUTE(app, "/msg/rank/<int>")
    ([this](int top) {
        std::unordered_map<std::string, std::string> params;
        params["top"] = std::to_string(top);

        std::string result = msgApi->handleRank(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // 8. Shortest Path
    CROW_ROUTE(app, "/msg/path/<int>/<int>")
    ([this](int src, int dest) {
        std::unordered_map<std::string, std::string> params;
        params["src"] = std::to_string(src);
        params["dest"] = std::to_string(dest);

        std::string result = msgApi->handleShortestPath(params);
        
        crow::response res(result);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // CORS preflight handlers
    CROW_ROUTE(app, "/msg/send").methods(crow::HTTPMethod::Options)
    ([]() {
        crow::response res;
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        return res;
    });
}
