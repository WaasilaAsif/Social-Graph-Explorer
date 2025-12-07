#pragma once
#include "../../libs/crow/crow_all.h"
#include "../../dsa/graph/Graph.h"
#include"../../dsa/user/UserManager.h"

class GraphRoutes {
    public:
    Graph& graph;
    UserManager &userManager;
    GraphRoutes(Graph &g, UserManager &um);
    
    void registerRoutes(crow::SimpleApp& app);
};
