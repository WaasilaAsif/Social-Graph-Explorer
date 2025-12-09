#pragma once
#include "../../libs/crow/crow_all.h"
#include "../../libs/crow/nlohmann/json.hpp"
#include "../../dsa/user/UserManager.h"

using json = nlohmann::json;

class UserRouter {
private:
    UserManager& userManager;
    
    // Helper function to add CORS headers
    void addCorsHeaders(crow::response& res) {
        res.add_header("Access-Control-Allow-Origin", "*");
        res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
        res.add_header("Access-Control-Allow-Headers", "Content-Type");
        res.add_header("Content-Type", "application/json");
    }

public:
    UserRouter(UserManager& um) : userManager(um) {}

    void setupRoutes(crow::SimpleApp& app) {
        CROW_ROUTE(app, "/api/users/register")
            .methods(crow::HTTPMethod::Post)
            ([this](const crow::request& req) {
                crow::response res;
                addCorsHeaders(res);
                
                try {
                    auto body = json::parse(req.body);
                    std::string username = body["username"];
                    std::string password = body["password"];
                    
                    if (username.empty() || password.empty()) {
                        res.code = 400;
                        res.body = json{
                            {"success", false},
                            {"error", "Username and password required"}
                        }.dump();
                        return res;
                    }
                    
                    userManager.addUser(username, password);
                    userManager.saveToFile();
                    
                    // Get the newly created user to return their ID
                    User* newUser = userManager.login(username, password);
                    
                    res.code = 201;
                    res.body = json{
                        {"success", true},
                        {"message", "User registered successfully"},
                        {"userId", newUser ? newUser->getId() : -1},
                        {"username", username}
                    }.dump();
                    return res;
                    
                } catch (const std::exception& e) {
                    res.code = 400;
                    res.body = json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump();
                    return res;
                }
            });

        // ==================== LOGIN ====================
        CROW_ROUTE(app, "/api/users/login")
            .methods(crow::HTTPMethod::Post)
            ([this](const crow::request& req) {
                crow::response res;
                addCorsHeaders(res);
                
                try {
                    auto body = json::parse(req.body);
                    std::string username = body["username"];
                    std::string password = body["password"];
                    
                    User* user = userManager.login(username, password);
                    
                    if (user) {
                        res.code = 200;
                        res.body = json{
                            {"success", true},
                            {"message", "Login successful"},
                            {"userId", user->getId()},
                            {"username", user->getName()}
                        }.dump();
                        return res;
                    } else {
                        res.code = 401;
                        res.body = json{
                            {"success", false},
                            {"error", "Invalid username or password"}
                        }.dump();
                        return res;
                    }
                    
                } catch (const std::exception& e) {
                    res.code = 400;
                    res.body = json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump();
                    return res;
                }
            });

        // ==================== SEARCH USERS ====================
        CROW_ROUTE(app, "/api/users/search")
            .methods(crow::HTTPMethod::Get)
            ([this](const crow::request& req) {
                try {
                    std::string prefix = req.url_params.get("prefix") 
                        ? req.url_params.get("prefix") : "";
                    
                    DynamicArray<std::string> results = 
                        userManager.searchUsersByPrefix(prefix);
                    
                    json usersArray = json::array();
                    for (int i = 0; i < results.size(); i++) {
                        usersArray.push_back(results.get(i));
                    }
                    
                    return crow::response(200, json{
                        {"success", true},
                        {"users", usersArray},
                        {"count", results.size()}
                    }.dump());
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== GET USER BY ID ====================
        CROW_ROUTE(app, "/api/users/<int>")
            .methods(crow::HTTPMethod::Get)
            ([this](int userId) {
                try {
                    User* user = userManager.getUserById(userId);
                    
                    if (user) {
                        DynamicArray<std::string>& posts = user->getPosts();
                        json postsArray = json::array();
                        for (int i = 0; i < posts.size(); i++) {
                            postsArray.push_back({
                                {"index", i},
                                {"content", posts.get(i)}
                            });
                        }
                        
                        return crow::response(200, json{
                            {"success", true},
                            {"user", {
                                {"id", user->getId()},
                                {"username", user->getName()},
                                {"posts", postsArray},
                                {"postCount", posts.size()}
                            }}
                        }.dump());
                    } else {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "User not found"}
                        }.dump());
                    }
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== DELETE USER ====================
        CROW_ROUTE(app, "/api/users/<int>")
            .methods(crow::HTTPMethod::Delete)
            ([this](int userId) {
                try {
                    bool success = userManager.removeUserById(userId);
                    
                    if (success) {
                        userManager.saveToFile();
                        return crow::response(200, json{
                            {"success", true},
                            {"message", "User deleted successfully"}
                        }.dump());
                    } else {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "User not found"}
                        }.dump());
                    }
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== CREATE POST ====================
        CROW_ROUTE(app, "/api/users/<int>/posts")
            .methods(crow::HTTPMethod::Post)
            ([this](const crow::request& req, int userId) {
                try {
                    User* user = userManager.getUserById(userId);
                    
                    if (!user) {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "User not found"}
                        }.dump());
                    }
                    
                    auto body = json::parse(req.body);
                    std::string content = body["content"];
                    
                    if (content.empty()) {
                        return crow::response(400, json{
                            {"success", false},
                            {"error", "Post content cannot be empty"}
                        }.dump());
                    }
                    
                    user->createPost(content);
                    userManager.saveToFile();
                    
                    return crow::response(201, json{
                        {"success", true},
                        {"message", "Post created successfully"}
                    }.dump());
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== GET USER POSTS ====================
        CROW_ROUTE(app, "/api/users/<int>/posts")
            .methods(crow::HTTPMethod::Get)
            ([this](int userId) {
                try {
                    User* user = userManager.getUserById(userId);
                    
                    if (!user) {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "User not found"}
                        }.dump());
                    }
                    
                    DynamicArray<std::string>& posts = user->getPosts();
                    json postsArray = json::array();
                    
                    for (int i = 0; i < posts.size(); i++) {
                        postsArray.push_back({
                            {"index", i},
                            {"content", posts.get(i)}
                        });
                    }
                    
                    return crow::response(200, json{
                        {"success", true},
                        {"posts", postsArray},
                        {"count", posts.size()}
                    }.dump());
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== DELETE POST ====================
        CROW_ROUTE(app, "/api/users/<int>/posts/<int>")
            .methods(crow::HTTPMethod::Delete)
            ([this](int userId, int postIndex) {
                try {
                    User* user = userManager.getUserById(userId);
                    
                    if (!user) {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "User not found"}
                        }.dump());
                    }
                    
                    bool success = user->deletePost(postIndex);
                    
                    if (success) {
                        userManager.saveToFile();
                        return crow::response(200, json{
                            {"success", true},
                            {"message", "Post deleted successfully"}
                        }.dump());
                    } else {
                        return crow::response(404, json{
                            {"success", false},
                            {"error", "Invalid post index"}
                        }.dump());
                    }
                    
                } catch (const std::exception& e) {
                    return crow::response(500, json{
                        {"success", false},
                        {"error", std::string(e.what())}
                    }.dump());
                }
            });

        // ==================== CORS ====================
        CROW_ROUTE(app, "/api/<path>")
            .methods(crow::HTTPMethod::Options)
            ([](const crow::request&, std::string) {
                crow::response res(200);
                res.add_header("Access-Control-Allow-Origin", "*");
                res.add_header("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
                res.add_header("Access-Control-Allow-Headers", "Content-Type");
                return res;
            });
    }
};