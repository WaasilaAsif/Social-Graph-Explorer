#define CROW_MAIN
#include <crow.h>
#include "libs/json.hpp"
#include "dsa/user/UserManager.h"
#include "api/routes/UserRouter.h"
#include <iostream>

int main() {
    crow::SimpleApp app;
    
    CROW_ROUTE(app, "/")
    ([](){
        return "Social Graph Explorer API - Crow Version";
    });
    
    UserManager userManager;
    UserRouter router(userManager);
    router.setupRoutes(app);
    
    std::cout << "========================================\n";
    std::cout << "Social Graph Explorer API (Crow)\n";
    std::cout << "========================================\n";
    std::cout << "Server: http://localhost:8080\n";
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
    
    app.port(8080).multithreaded().loglevel(crow::LogLevel::Warning).run();
    
    return 0;
}