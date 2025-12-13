#include "graphRoutes.h"
#include "../../dsa/graph/Graph.h"
#include "../../dsa/graph/Edge.h"
#include "../../dsa/containers/LinkedList.h"
#include "../../libs/project_headers/BFS.h"
#include "../../libs/project_headers/DFS.h"
#include "../../analytics/Graphstats.h"
#include "../../storage/JSONWriter.h"
#include <iostream>
#include <vector>

GraphRoutes::GraphRoutes(Graph &g, UserManager &um) : graph(g), userManager(um) {}
void GraphRoutes::registerRoutes(crow::SimpleApp &app)
{

    // GET /graph/friends/:id
    CROW_ROUTE(app, "/graph/friends/<int>")
    ([this](int id)
     {
        crow::json::wvalue response;

        try {
            const LinkedList<Edge>& neighbors = graph.getNeighbors(id);

            response["success"] = true;
            response["userId"] = id;

            std::vector<crow::json::wvalue> list;
            for (int i = 0; i < neighbors.size(); i++) {
                crow::json::wvalue friendObj;
                friendObj["id"] = neighbors[i].to;
                list.push_back(friendObj);
            }

            response["friends"] = std::move(list);
            response["count"] = neighbors.size();
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*"); // CORS
        return res; });

    // POST /graph/addFriend
    CROW_ROUTE(app, "/graph/addFriend").methods(crow::HTTPMethod::Post)([this](const crow::request &req)
                                                                        {
        crow::json::wvalue response;
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("u") || !body.has("v")) {
                response["success"] = false;
                response["error"] = "Missing fields u or v";
                crow::response res(400, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }
            int u = body["u"].i();
int v = body["v"].i();

// Check if users exist in UserManager
User* userA = userManager.getUserById(u);
User* userB = userManager.getUserById(v);

if (!userA || !userB) {
    response["success"] = false;
    response["error"] = "One or both users do not exist";
    crow::response res(404, response);
    res.add_header("Content-Type", "application/json");
    res.add_header("Access-Control-Allow-Origin", "*");
    return res;
}

// Users exist, now create friendship
if (!graph.hasNode(u)) graph.addNode(u);
if (!graph.hasNode(v)) graph.addNode(v);
            if (!graph.hasEdge(u, v)) {
                graph.addEdge(u, v, 1, true);
                // Debug output: print neighbors of u
                std::cout << "Neighbors of " << u << ": ";
                const LinkedList<Edge>& neighbors = graph.getNeighbors(u);
                for (int i = 0; i < neighbors.size(); ++i) {
                    std::cout << neighbors[i].to << " ";
                }
                std::cout << std::endl;
                response["success"] = true;
                response["message"] = "Friendship created";
                saveFriendshipsToJSON(graph, "../storage/local_db/friendships.json");
            } else {
                response["success"] = true;
                response["message"] = "Friendship already exists";
            }
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }
        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // POST /graph/removeFriend
    CROW_ROUTE(app, "/graph/removeFriend").methods(crow::HTTPMethod::Post)([this](const crow::request &req)
                                                                           {
        crow::json::wvalue response;
        try {
            auto body = crow::json::load(req.body);
            if (!body || !body.has("u") || !body.has("v")) {
                response["success"] = false;
                response["error"] = "Missing fields u or v";
                crow::response res(400, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }
            int u = body["u"].i();
            int v = body["v"].i();
            if (!graph.hasEdge(u, v)) {
                response["success"] = false;
                response["error"] = "Friendship does not exist";
            } else {
                graph.removeEdge(u, v, true);
                response["success"] = true;
                response["message"] = "Friendship removed";
                saveFriendshipsToJSON(graph, "../storage/local_db/friendships.json");
            }
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }
        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/stats
    CROW_ROUTE(app, "/graph/stats")
    ([this]()
     {
        crow::json::wvalue response;

        try {
            response["success"] = true;
            response["nodeCount"] = graph.nodeCount();
            response["edgeCount"] = GraphStats::countEdges(graph, true);
            response["components"] = GraphStats::countComponents(graph);
            response["isConnected"] = GraphStats::isConnected(graph);
            response["density"] = GraphStats::getDensity(graph);
            response["averageDegree"] = GraphStats::getAverageDegree(graph);
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/connected/:u/:v
    CROW_ROUTE(app, "/graph/connected/<int>/<int>")
    ([this](int u, int v)
     {
        crow::json::wvalue response;

        try {
            bool ok = BFS::existsPath(graph, u, v);
            response["success"] = true;
            response["u"] = u;
            response["v"] = v;
            response["connected"] = ok;
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/components
    CROW_ROUTE(app, "/graph/components")
    ([this]()
     {
        crow::json::wvalue response;

        try {
            int count = GraphStats::countComponents(graph);
            response["success"] = true;
            response["components"] = count;
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/bfs/:start - BFS traversal
    CROW_ROUTE(app, "/graph/bfs/<int>")
    ([this](int start)
     {
        crow::json::wvalue response;

        try {
            if (!graph.hasNode(start)) {
                response["success"] = false;
                response["error"] = "Start node does not exist";
                crow::response res(404, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }

            LinkedList<int> traversal = BFS::traverse(graph, start);
            
            response["success"] = true;
            response["start"] = start;
            std::vector<crow::json::wvalue> traversalArray;
            for (int i = 0; i < traversal.size(); i++) {
                traversalArray.push_back(traversal[i]);
            }
            response["traversal"] = std::move(traversalArray);
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/dfs/:start - DFS traversal
    CROW_ROUTE(app, "/graph/dfs/<int>")
    ([this](int start)
     {
        crow::json::wvalue response;

        try {
            if (!graph.hasNode(start)) {
                response["success"] = false;
                response["error"] = "Start node does not exist";
                crow::response res(404, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }

            LinkedList<int> traversal = DFS::traverse(graph, start);
            
            response["success"] = true;
            response["start"] = start;
            std::vector<crow::json::wvalue> traversalArray;
            for (int i = 0; i < traversal.size(); i++) {
                traversalArray.push_back(traversal[i]);
            }
            response["traversal"] = std::move(traversalArray);
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });

    // GET /graph/shortest-path/:src/:dest - Find shortest path
    CROW_ROUTE(app, "/graph/shortest-path/<int>/<int>")
    ([this](int src, int dest)
     {
        crow::json::wvalue response;

        try {
            if (!graph.hasNode(src)) {
                response["success"] = false;
                response["error"] = "Source node does not exist";
                crow::response res(404, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }

            if (!graph.hasNode(dest)) {
                response["success"] = false;
                response["error"] = "Destination node does not exist";
                crow::response res(404, response);
                res.add_header("Content-Type", "application/json");
                res.add_header("Access-Control-Allow-Origin", "*");
                return res;
            }

            LinkedList<int> path = BFS::shortestPath(graph, src, dest);
            
            response["success"] = true;
            response["src"] = src;
            response["dest"] = dest;
            std::vector<crow::json::wvalue> pathArray;
            for (int i = 0; i < path.size(); i++) {
                pathArray.push_back(path[i]);
            }
            response["path"] = std::move(pathArray);
            response["length"] = path.size() > 0 ? path.size() - 1 : 0;
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res; });
}
