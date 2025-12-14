#include "crow.h"
#include <string>

int main()
{
    crow::App<CORS> app;
;

    // Root route
    CROW_ROUTE(app, "/")([](){
        return "SocialGraphExplorer Backend is running!";
    });

    // Dummy user route
    CROW_ROUTE(app, "/user/<int>")([](int user_id){
        return "Fetching user with ID: " + std::to_string(user_id);
    });

    // Dummy message route
    CROW_ROUTE(app, "/message/<int>/<int>")([](int from, int to){
        return "Sending message from " + std::to_string(from) +
               " to " + std::to_string(to);
    });

    app.port(18080).multithreaded().run();
}
