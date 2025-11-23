// graphRoutes.cpp
#include "graphRoutes.h"
#include "../../dsa/graph/Graph.h"
#include "../../dsa/graph/Edge.h"
#include "../../dsa/containers/LinkedList.h"
#include "../../algorithms/BFS.h"
#include "../../algorithms/DFS.h"
#include "../../algorithms/Graphstats.h"
#include <iostream>
#include <vector>
#include <crow.h>  // ✅ Crow 1.x

GraphRoutes::GraphRoutes(Graph& g) : graph(g) {}

void GraphRoutes::registerRoutes(crow::SimpleApp& app) {

    // GET /graph/friends/:id
    CROW_ROUTE(app, "/graph/friends/<int>")
    ([this](int id) {
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
        return res;
    });

    // POST /graph/addFriend
    CROW_ROUTE(app, "/graph/addFriend").methods(crow::HTTPMethod::Post)
    ([this](const crow::request& req) {
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

            if (!graph.hasNode(u)) graph.addNode(u);
            if (!graph.hasNode(v)) graph.addNode(v);

            if (!graph.hasEdge(u, v)) {
                graph.addEdge(u, v, 1, true);
                response["success"] = true;
                response["message"] = "Friendship created";
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
        return res;
    });

    // POST /graph/removeFriend
    CROW_ROUTE(app, "/graph/removeFriend").methods(crow::HTTPMethod::Post)
    ([this](const crow::request& req) {
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
            }
        }
        catch (const std::exception& e) {
            response["success"] = false;
            response["error"] = std::string(e.what());
        }

        crow::response res(response);
        res.add_header("Content-Type", "application/json");
        res.add_header("Access-Control-Allow-Origin", "*");
        return res;
    });

    // GET /graph/stats
    CROW_ROUTE(app, "/graph/stats")
    ([this]() {
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
        return res;
    });

    // GET /graph/connected/:u/:v
    CROW_ROUTE(app, "/graph/connected/<int>/<int>")
    ([this](int u, int v) {
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
        return res;
    });

    // GET /graph/components
    CROW_ROUTE(app, "/graph/components")
    ([this]() {
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
        return res;
    });
}
