#pragma once
#include "../../include/crow_all.h"  // ✅ FIXED: Correct relative path
#include "../../dsa/graph/Graph.h"

class GraphRoutes {
private:
    Graph& graph;

public:
    GraphRoutes(Graph& g);
    void registerRoutes(crow::SimpleApp& app);
};
