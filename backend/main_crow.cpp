#define CROW_MAIN
#include "libs/crow/crow_all.h"
#include "libs/crow/nlohmann/json.hpp"
#include "dsa/user/UserManager.h"
#include "api/routes/UserRouter.h"
#include <iostream>

int main() {
    crow::App<CORS> app;
;
    
    CROW_ROUTE(app, "/")
    ([](){
        crow::response res("Social Graph Explorer API - Crow Version");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });
    
    UserManager userManager("storage/local_db/users.json");
    UserRouter router(userManager);
    router.setupRoutes(app);
    
    std::cout << "========================================\n";
    std::cout << "Social Graph Explorer API (Crow)\n";
    std::cout << "========================================\n";
    std::cout << "Server: http://localhost:8081\n";
    std::cout << "\nEndpoints:\n";
    std::cout << "  POST   /api/users/register\n";
    std::cout << "  POST   /api/users/login\n";
    std::cout << "  GET    /api/users/search?prefix=...\n";
    std::cout << "  GET    /api/users/:id\n";
    std::cout << "  DELETE /api/users/:id\n";
    std::cout << "  POST   /api/users/:id/posts\n";
    std::cout << "  GET    /api/users/:id/posts\n";
    std::cout << "  DELETE /api/users/:id/posts/:index\n";
    std::cout << "========================================\n\n";
    
    app.port(8081).multithreaded().loglevel(crow::LogLevel::Warning).run();
    
    return 0;
}