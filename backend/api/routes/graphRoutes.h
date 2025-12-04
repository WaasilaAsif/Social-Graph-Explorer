#pragma once
#include "../../libs/crow/crow_all.h"
#include "../../dsa/graph/Graph.h"

class GraphRoutes {
private:
    Graph& graph;

public:
    GraphRoutes(Graph& g);
    void registerRoutes(crow::SimpleApp& app);
};
