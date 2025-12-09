#define CROW_MAIN
#include "libs/crow/crow_all.h"
#include <iostream>

int main() {
    crow::App<CORS> app;
;
    
    CROW_ROUTE(app, "/")
    ([](){
        return "Social Graph Explorer API - Running!";
    });
    
    std::cout << "========================================\n";
    std::cout << "Social Graph Explorer API\n";
    std::cout << "========================================\n";
    std::cout << "Server: http://localhost:8080\n";
    std::cout << "========================================\n\n";
    
    app.port(8080).multithreaded().run();
    
    return 0;
}
