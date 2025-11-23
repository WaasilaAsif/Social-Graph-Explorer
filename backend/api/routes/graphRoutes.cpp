// graphRoutes.cpp
// API routes for graph operations
// Member 2: Graph Engineer

#include "../../dsa/graph/Graph.h"
#include "../../algorithms/BFS.h"
#include "../../algorithms/DFS.h"
#include "../../algorithms/GraphStats.h"
#include "../../algorithms/GraphLayout.h"
#include <iostream>
#include <string>

// Note: This is a template. Adapt to your chosen web framework
// (crow, cpp-httplib, pistache, etc.)

/*
 * EXAMPLE ROUTES TO IMPLEMENT:
 * 
 * Graph Management:
 * - POST   /api/graph/nodes                 - Add a node
 * - DELETE /api/graph/nodes/:id             - Remove a node
 * - POST   /api/graph/edges                 - Add an edge/friendship
 * - DELETE /api/graph/edges                 - Remove an edge/friendship
 * - GET    /api/graph/nodes/:id             - Get node details
 * - GET    /api/graph/nodes                 - Get all nodes
 * 
 * Graph Algorithms:
 * - GET    /api/graph/bfs/:startId          - BFS traversal
 * - GET    /api/graph/dfs/:startId          - DFS traversal
 * - GET    /api/graph/path/:from/:to        - Find shortest path
 * - GET    /api/graph/connected/:id1/:id2   - Check if connected
 * 
 * Graph Statistics:
 * - GET    /api/graph/stats                 - Get graph statistics
 * - GET    /api/graph/degree/:id            - Get node degree
 * - GET    /api/graph/components            - Count components
 * - GET    /api/graph/layout/:type          - Get node positions for visualization
 */

// ========== Example Implementation (pseudo-code) ==========

// Assuming you're using crow or similar framework:

/*
#include <crow.h>

class GraphRoutes {
private:
    Graph& graph;  // Reference to main graph instance
    
public:
    GraphRoutes(Graph& g) : graph(g) {}
    
    void setupRoutes(crow::SimpleApp& app) {
        
        // ==================== ADD NODE ====================
        CROW_ROUTE(app, "/api/graph/nodes")
            .methods("POST"_method)
            ([this](const crow::request& req) {
                try {
                    auto body = crow::json::load(req.body);
                    if (!body)
                        return crow::response(400, "Invalid JSON");
                    
                    int nodeId = body["id"].i();
                    
                    graph.addNode(nodeId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["message"] = "Node added successfully";
                    response["nodeId"] = nodeId;
                    
                    return crow::response(201, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== REMOVE NODE ====================
        CROW_ROUTE(app, "/api/graph/nodes/<int>")
            .methods("DELETE"_method)
            ([this](int nodeId) {
                try {
                    graph.removeNode(nodeId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["message"] = "Node removed successfully";
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== ADD EDGE ====================
        CROW_ROUTE(app, "/api/graph/edges")
            .methods("POST"_method)
            ([this](const crow::request& req) {
                try {
                    auto body = crow::json::load(req.body);
                    if (!body)
                        return crow::response(400, "Invalid JSON");
                    
                    int from = body["from"].i();
                    int to = body["to"].i();
                    int weight = body.has("weight") ? body["weight"].i() : 1;
                    
                    graph.addEdge(from, to, weight, true);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["message"] = "Edge added successfully";
                    
                    return crow::response(201, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== GET NODE NEIGHBORS ====================
        CROW_ROUTE(app, "/api/graph/nodes/<int>/neighbors")
            .methods("GET"_method)
            ([this](int nodeId) {
                try {
                    const LinkedList<Edge>& neighbors = graph.getNeighbors(nodeId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["nodeId"] = nodeId;
                    
                    // Build neighbors array
                    std::vector<crow::json::wvalue> neighborList;
                    for (int i = 0; i < neighbors.size(); ++i) {
                        crow::json::wvalue neighbor;
                        neighbor["id"] = neighbors[i].to;
                        neighbor["weight"] = neighbors[i].weight;
                        neighborList.push_back(std::move(neighbor));
                    }
                    response["neighbors"] = std::move(neighborList);
                    response["degree"] = neighbors.size();
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== BFS TRAVERSAL ====================
        CROW_ROUTE(app, "/api/graph/bfs/<int>")
            .methods("GET"_method)
            ([this](int startId) {
                try {
                    LinkedList<int> traversal = BFS::traverse(graph, startId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["algorithm"] = "BFS";
                    response["startNode"] = startId;
                    
                    std::vector<int> nodeOrder;
                    for (int i = 0; i < traversal.size(); ++i) {
                        nodeOrder.push_back(traversal[i]);
                    }
                    response["traversalOrder"] = std::move(nodeOrder);
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== DFS TRAVERSAL ====================
        CROW_ROUTE(app, "/api/graph/dfs/<int>")
            .methods("GET"_method)
            ([this](int startId) {
                try {
                    LinkedList<int> traversal = DFS::traverse(graph, startId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["algorithm"] = "DFS";
                    response["startNode"] = startId;
                    
                    std::vector<int> nodeOrder;
                    for (int i = 0; i < traversal.size(); ++i) {
                        nodeOrder.push_back(traversal[i]);
                    }
                    response["traversalOrder"] = std::move(nodeOrder);
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== SHORTEST PATH ====================
        CROW_ROUTE(app, "/api/graph/path/<int>/<int>")
            .methods("GET"_method)
            ([this](int fromId, int toId) {
                try {
                    LinkedList<int> path = BFS::shortestPath(graph, fromId, toId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["from"] = fromId;
                    response["to"] = toId;
                    
                    if (path.isEmpty()) {
                        response["pathExists"] = false;
                        response["distance"] = -1;
                    } else {
                        response["pathExists"] = true;
                        response["distance"] = path.size() - 1;
                        
                        std::vector<int> pathNodes;
                        for (int i = 0; i < path.size(); ++i) {
                            pathNodes.push_back(path[i]);
                        }
                        response["path"] = std::move(pathNodes);
                    }
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== GRAPH STATISTICS ====================
        CROW_ROUTE(app, "/api/graph/stats")
            .methods("GET"_method)
            ([this]() {
                try {
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["nodeCount"] = graph.nodeCount();
                    response["edgeCount"] = GraphStats::countEdges(graph, true);
                    response["averageDegree"] = GraphStats::getAverageDegree(graph);
                    response["density"] = GraphStats::getDensity(graph);
                    response["isConnected"] = GraphStats::isConnected(graph);
                    response["components"] = GraphStats::countComponents(graph);
                    response["averageClustering"] = GraphStats::getAverageClusteringCoefficient(graph);
                    
                    if (GraphStats::isConnected(graph)) {
                        response["diameter"] = GraphStats::getDiameter(graph);
                    }
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== NODE DEGREE ====================
        CROW_ROUTE(app, "/api/graph/degree/<int>")
            .methods("GET"_method)
            ([this](int nodeId) {
                try {
                    int degree = GraphStats::getDegree(graph, nodeId);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["nodeId"] = nodeId;
                    response["degree"] = degree;
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== GRAPH LAYOUT ====================
        CROW_ROUTE(app, "/api/graph/layout/<string>")
            .methods("GET"_method)
            ([this](std::string layoutType) {
                try {
                    HashMap<int, Vector2> positions(100);
                    
                    if (layoutType == "layer" || layoutType == "hierarchical") {
                        positions = GraphLayout::generateLayout(graph);
                    }
                    else if (layoutType == "circular") {
                        positions = GraphLayout::generateCircularLayout(graph);
                    }
                    else if (layoutType == "force") {
                        positions = GraphLayout::generateForceDirectedLayout(graph);
                    }
                    else {
                        crow::json::wvalue response;
                        response["success"] = false;
                        response["error"] = "Unknown layout type. Use: layer, circular, or force";
                        return crow::response(400, response);
                    }
                    
                    // Center the layout
                    GraphLayout::centerLayout(positions);
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["layoutType"] = layoutType;
                    
                    // Build positions object
                    DynamicArray<int> nodeIds = positions.keys();
                    crow::json::wvalue nodePositions;
                    
                    for (int i = 0; i < nodeIds.size(); ++i) {
                        int nodeId = nodeIds[i];
                        Vector2 pos = positions.get(nodeId);
                        
                        crow::json::wvalue posData;
                        posData["x"] = pos.x;
                        posData["y"] = pos.y;
                        
                        nodePositions[std::to_string(nodeId)] = std::move(posData);
                    }
                    
                    response["positions"] = std::move(nodePositions);
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(400, response);
                }
            });
        
        // ==================== GET ALL NODES ====================
        CROW_ROUTE(app, "/api/graph/nodes")
            .methods("GET"_method)
            ([this]() {
                try {
                    LinkedList<int> allNodes = graph.getAllNodeIDs();
                    
                    crow::json::wvalue response;
                    response["success"] = true;
                    response["nodeCount"] = allNodes.size();
                    
                    std::vector<int> nodeList;
                    for (int i = 0; i < allNodes.size(); ++i) {
                        nodeList.push_back(allNodes[i]);
                    }
                    response["nodes"] = std::move(nodeList);
                    
                    return crow::response(200, response);
                }
                catch (const std::exception& e) {
                    crow::json::wvalue response;
                    response["success"] = false;
                    response["error"] = e.what();
                    return crow::response(500, response);
                }
            });
    }
};
*/

// ========== Plain C++ Test Functions (No Web Framework) ==========

// You can use these for testing without a web server

void testGraphOperations(Graph& graph) {
    std::cout << "\n=== Testing Graph Operations ===\n";
    
    // Add nodes
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    
    // Add edges
    graph.addEdge(1, 2);
    graph.addEdge(2, 3);
    graph.addEdge(3, 4);
    graph.addEdge(4, 1);
    
    std::cout << "Graph created with 4 nodes and 4 edges\n";
    graph.print();
}

void testBFSOperations(Graph& graph) {
    std::cout << "\n=== Testing BFS Operations ===\n";
    
    BFS::printTraversal(graph, 1);
    
    LinkedList<int> path = BFS::shortestPath(graph, 1, 4);
    std::cout << "Shortest path from 1 to 4: ";
    for (int i = 0; i < path.size(); ++i) {
        std::cout << path[i];
        if (i < path.size() - 1) std::cout << " -> ";
    }
    std::cout << "\n";
}

void testDFSOperations(Graph& graph) {
    std::cout << "\n=== Testing DFS Operations ===\n";
    
    DFS::printTraversal(graph, 1);
    
    bool connected = DFS::isConnected(graph);
    std::cout << "Graph is " << (connected ? "connected" : "not connected") << "\n";
}

void testGraphStats(Graph& graph) {
    std::cout << "\n=== Testing Graph Statistics ===\n";
    
    GraphStats::printStats(graph);
}

void testGraphLayout(Graph& graph) {
    std::cout << "\n=== Testing Graph Layout ===\n";
    
    HashMap<int, Vector2> positions = GraphLayout::generateLayout(graph);
    GraphLayout::centerLayout(positions);
    
    LinkedList<int> allNodes = graph.getAllNodeIDs();
    std::cout << "Node positions:\n";
    for (int i = 0; i < allNodes.size(); ++i) {
        int nodeId = allNodes[i];
        Vector2 pos = positions.get(nodeId);
        std::cout << "  Node " << nodeId << ": (" << pos.x << ", " << pos.y << ")\n";
    }
}

// Main test function
int main() {
    Graph graph;
    
    testGraphOperations(graph);
    testBFSOperations(graph);
    testDFSOperations(graph);
    testGraphStats(graph);
    testGraphLayout(graph);
    
    return 0;
}