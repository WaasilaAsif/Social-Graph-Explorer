#include "../../libs/crow/crow_all.h"
#include "../../libs/crow/nlohmann/json.hpp"
#include <ctime>
#include "../../algorithms/MutualFriends.h"
#include "../../algorithms/ShortestPath.h"
#include "../../analytics/GraphStats.h"
#include "../../analytics/PopularityRanker.h"
#include "../../algorithms/FriendSuggestion.h"
#include "../../dsa/containers/PriorityQueue.h"
#include "../../dsa/graph/Graph.h"
#include <ctime>

using json = nlohmann::json;

void setupAlgoRoutes(crow::SimpleApp& app, Graph* graph, 
                     MutualFriends* mutualFriends,
                     ShortestPath* shortestPath,
                     GraphStats* graphStats,
                     PopularityRanker* popularityRanker,
                     FriendSuggestion* friendSuggestion) {
    
    // ============================================
    // MUTUAL FRIENDS ROUTES
    // ============================================
    
    // GET /api/algo/mutual-friends?user1={id}&user2={id}
    CROW_ROUTE(app, "/api/algo/mutual-friends")
    .methods("GET"_method)
    ([mutualFriends](const crow::request& req) {
        auto user1Str = req.url_params.get("user1");
        auto user2Str = req.url_params.get("user2");
        
        if (!user1Str || !user2Str) {
            return crow::response(400, "Missing user1 or user2 parameter");
        }
        
        try {
            int user1 = std::stoi(user1Str);
            int user2 = std::stoi(user2Str);
            
            LinkedList<int> mutuals = mutualFriends->getMutualFriends(user1, user2);
            
            json response;
            response["user1"] = user1;
            response["user2"] = user2;
            
            json mutualsArray = json::array();
            for (int i = 0; i < mutuals.size(); i++) {
                mutualsArray.push_back(mutuals[i]);
            }
            
            response["mutualFriends"] = mutualsArray;
            response["count"] = mutuals.size();
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // ============================================
    // SHORTEST PATH ROUTES
    // ============================================
    
    // GET /api/algo/shortest-path?start={id}&end={id}
    CROW_ROUTE(app, "/api/algo/shortest-path")
    .methods("GET"_method)
    ([shortestPath](const crow::request& req) {
        auto startStr = req.url_params.get("start");
        auto endStr = req.url_params.get("end");
        
        if (!startStr || !endStr) {
            return crow::response(400, "Missing start or end parameter");
        }
        
        try {
            int start = std::stoi(startStr);
            int end = std::stoi(endStr);
            
            LinkedList<int> path = shortestPath->findPath(start, end);
            int distance = shortestPath->getDistance(start, end);
            
            json response;
            response["start"] = start;
            response["end"] = end;
            
            json pathArray = json::array();
            for (int i = 0; i < path.size(); i++) {
                pathArray.push_back(path[i]);
            }
            
            response["path"] = pathArray;
            response["distance"] = distance;
            response["exists"] = (distance != -1);
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // GET /api/algo/users-within-distance?userId={id}&distance={n}
    CROW_ROUTE(app, "/api/algo/users-within-distance")
    .methods("GET"_method)
    ([shortestPath](const crow::request& req) {
        auto userIdStr = req.url_params.get("userId");
        auto distanceStr = req.url_params.get("distance");
        
        if (!userIdStr || !distanceStr) {
            return crow::response(400, "Missing userId or distance parameter");
        }
        
        try {
            int userId = std::stoi(userIdStr);
            int distance = std::stoi(distanceStr);
            
            LinkedList<int> users = shortestPath->getUsersWithinDistance(userId, distance);
            
            json response;
            response["userId"] = userId;
            response["maxDistance"] = distance;
            
            json usersArray = json::array();
            for (int i = 0; i < users.size(); i++) {
                usersArray.push_back(users[i]);
            }
            
            response["users"] = usersArray;
            response["count"] = users.size();
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // GRAPH STATISTICS ROUTES
    
    // GET /api/algo/user-degree?userId={id}
    CROW_ROUTE(app, "/api/algo/user-degree")
    .methods("GET"_method)
    ([graph](const crow::request& req) {
        auto userIdStr = req.url_params.get("userId");
        
        if (!userIdStr) {
            return crow::response(400, "Missing userId parameter");
        }
        
        try {
            int userId = std::stoi(userIdStr);
            int degree = GraphStats::getDegree(*graph, userId);
            
            json response;
            response["userId"] = userId;
            response["degree"] = degree;
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
        // GET /api/algo/graph-stats
        CROW_ROUTE(app, "/api/algo/graph-stats")
        .methods("GET"_method)
        ([graph](const crow::request& req) {
            try {
                int nodeCount = graph->nodeCount();
                int edgeCount = GraphStats::countEdges(*graph, true);
                float avgDegree = GraphStats::getAverageDegree(*graph);
                float density = GraphStats::getDensity(*graph);
                bool connected = GraphStats::isConnected(*graph);
                int components = GraphStats::countComponents(*graph);
                int diameter = GraphStats::getDiameter(*graph);
                float avgClustering = GraphStats::getAverageClusteringCoefficient(*graph);
                int mostConnected = GraphStats::findMostConnectedNode(*graph);
            
                json response;
                response["nodeCount"] = nodeCount;
                response["edgeCount"] = edgeCount;
                response["averageDegree"] = avgDegree;
                response["density"] = density;
                response["connected"] = connected;
                response["components"] = components;
                response["diameter"] = diameter;
                response["averageClusteringCoefficient"] = avgClustering;
                response["mostConnectedNode"] = mostConnected;
            
                return crow::response(200, response.dump());
            } catch (const std::exception& e) {
                json error;
                error["error"] = e.what();
                return crow::response(500, error.dump());
            }
        });
    
    // ============================================
    // POPULARITY RANKING ROUTES
    // ============================================
    
    // GET /api/algo/top-popular?n={count}
    CROW_ROUTE(app, "/api/algo/top-popular")
    .methods("GET"_method)
    ([popularityRanker](const crow::request& req) {
        auto nStr = req.url_params.get("n");
        int n = nStr ? std::stoi(nStr) : 10;
        
        try {
            LinkedList<UserScore> topUsers = popularityRanker->getTopNPopularUsers(n);
            
            json response;
            json usersArray = json::array();
            
            for (int i = 0; i < topUsers.size(); i++) {
                json userObj;
                userObj["userId"] = topUsers[i].userId;
                userObj["score"] = topUsers[i].score;
                usersArray.push_back(userObj);
            }
            
            response["topUsers"] = usersArray;
            response["count"] = topUsers.size();
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // GET /api/algo/user-rank?userId={id}
    CROW_ROUTE(app, "/api/algo/user-rank")
    .methods("GET"_method)
    ([popularityRanker](const crow::request& req) {
        auto userIdStr = req.url_params.get("userId");
        
        if (!userIdStr) {
            return crow::response(400, "Missing userId parameter");
        }
        
        try {
            int userId = std::stoi(userIdStr);
            int rank = popularityRanker->getUserRank(userId);
            int score = popularityRanker->getPopularityScore(userId);
            double percentile = popularityRanker->getPercentileRank(userId);
            
            json response;
            response["userId"] = userId;
            response["rank"] = rank;
            response["score"] = score;
            response["percentile"] = percentile;
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // ============================================
    // FRIEND SUGGESTION ROUTES
    // ============================================
    
    // GET /api/algo/friend-suggestions?userId={id}&limit={n}
    CROW_ROUTE(app, "/api/algo/friend-suggestions")
    .methods("GET"_method)
    ([friendSuggestion](const crow::request& req) {
        auto userIdStr = req.url_params.get("userId");
        auto limitStr = req.url_params.get("limit");
        int limit = limitStr ? std::stoi(limitStr) : 10;
        
        if (!userIdStr) {
            return crow::response(400, "Missing userId parameter");
        }
        
        try {
            int userId = std::stoi(userIdStr);
            LinkedList<Suggestion> suggestions = friendSuggestion->getSuggestions(userId, limit);
            
            json response;
            json suggestionsArray = json::array();
            
            for (int i = 0; i < suggestions.size(); i++) {
                json suggestionObj;
                suggestionObj["userId"] = suggestions[i].userId;
                suggestionObj["mutualFriends"] = suggestions[i].mutualFriendsCount;
                suggestionObj["frequencyScore"] = suggestions[i].frequencyScore;
                suggestionsArray.push_back(suggestionObj);
            }
            
            response["userId"] = userId;
            response["suggestions"] = suggestionsArray;
            response["count"] = suggestions.size();
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    // GET /api/algo/two-hop-friends?userId={id}
    CROW_ROUTE(app, "/api/algo/two-hop-friends")
    .methods("GET"_method)
    ([friendSuggestion](const crow::request& req) {
        auto userIdStr = req.url_params.get("userId");
        
        if (!userIdStr) {
            return crow::response(400, "Missing userId parameter");
        }
        
        try {
            int userId = std::stoi(userIdStr);
            LinkedList<int> twoHopFriends = friendSuggestion->getTwoHopFriends(userId);
            
            json response;
            response["userId"] = userId;
            
            json twoHopArray = json::array();
            for (int i = 0; i < twoHopFriends.size(); i++) {
                twoHopArray.push_back(twoHopFriends[i]);
            }
            
            response["twoHopFriends"] = twoHopArray;
            response["count"] = twoHopFriends.size();
            
            return crow::response(200, response.dump());
        } catch (const std::exception& e) {
            json error;
            error["error"] = e.what();
            return crow::response(500, error.dump());
        }
    });
    
    CROW_ROUTE(app, "/api/algo/unit-tests")
    .methods("GET"_method)
    ([graph, mutualFriends, shortestPath, graphStats, popularityRanker, friendSuggestion]
     (const crow::request& req) {
        json testResults;
        testResults["component"] = "Member 3 - Algorithms & Analytics";
        testResults["timestamp"] = std::time(nullptr);
        testResults["tester"] = "Member 3";
        
        try {
            // Test 1: PriorityQueue (Max-Heap)
            testResults["test1_priorityQueue"]["status"] = "Testing...";
            try {
                PriorityQueue<int> pq;
                pq.insert(10);
                pq.insert(5);
                pq.insert(15);
                pq.insert(3);
                pq.insert(20);
                
                bool test1 = (pq.extractMax() == 20);
                bool test2 = (pq.extractMax() == 15);
                bool test3 = (pq.extractMax() == 10);
                bool test4 = (pq.size() == 2);
                
                if (test1 && test2 && test3 && test4) {
                    testResults["test1_priorityQueue"]["status"] = "[PASS]";
                    testResults["test1_priorityQueue"]["details"] = "Max-heap correctly returns elements in descending order";
                } else {
                    testResults["test1_priorityQueue"]["status"] = "[FAIL]";
                    testResults["test1_priorityQueue"]["details"] = "Heap ordering incorrect";
                }
            } catch (const std::exception& e) {
                testResults["test1_priorityQueue"]["status"] = "[FAIL]";
                testResults["test1_priorityQueue"]["error"] = e.what();
            }
            // Test 2: MutualFriends
            testResults["test2_mutualFriends"]["status"] = "Testing...";
            try {
                LinkedList<int> allUsers = graph->getAllNodeIDs();
                if (allUsers.size() >= 2) {
                    LinkedList<int> mutuals = mutualFriends->getMutualFriends(allUsers[0], allUsers[1]);
                    int count = mutualFriends->getMutualFriendsCount(allUsers[0], allUsers[1]);
                    bool hasMutual = mutualFriends->hasMutualFriends(allUsers[0], allUsers[1]);
                    
                    bool consistent = (mutuals.size() == count);
                    bool logicCorrect = (count > 0) ? hasMutual : !hasMutual;
                    
                    if (consistent && logicCorrect) {
                        testResults["test2_mutualFriends"]["status"] = "[PASS]";
                        testResults["test2_mutualFriends"]["details"] = {
                            {"user1", allUsers[0]},
                            {"user2", allUsers[1]},
                            {"mutualCount", count},
                            {"hasMutuals", hasMutual},
                            {"consistency", "Count matches list size"}
                        };
                    } else {
                        testResults["test2_mutualFriends"]["status"] = "[FAIL]";
                        testResults["test2_mutualFriends"]["details"] = "Inconsistent results";
                    }
                } else {
                    testResults["test2_mutualFriends"]["status"] = "[SKIP]";
                    testResults["test2_mutualFriends"]["reason"] = "Need at least 2 users in graph";
                }
            } catch (const std::exception& e) {
                testResults["test2_mutualFriends"]["status"] = "[FAIL]";
                testResults["test2_mutualFriends"]["error"] = e.what();
            }
            
            // Test 3: ShortestPath (BFS)
            testResults["test3_shortestPath"]["status"] = "Testing...";
            try {
                LinkedList<int> allUsers = graph->getAllNodeIDs();
                if (allUsers.size() >= 2) {
                    LinkedList<int> path = shortestPath->findPath(allUsers[0], allUsers[1]);
                    int distance = shortestPath->getDistance(allUsers[0], allUsers[1]);
                    bool exists = shortestPath->pathExists(allUsers[0], allUsers[1]);
                    
                    bool consistent = (distance == -1 && path.isEmpty() && !exists) || 
                                     (distance >= 0 && !path.isEmpty() && exists);
                    bool pathLengthCorrect = path.isEmpty() || (path.size() == distance + 1);
                    
                    if (consistent && pathLengthCorrect) {
                        testResults["test3_shortestPath"]["status"] = "[PASS]";
                        testResults["test3_shortestPath"]["details"] = {
                            {"from", allUsers[0]},
                            {"to", allUsers[1]},
                            {"distance", distance},
                            {"pathExists", exists},
                            {"pathLength", path.size()},
                            {"consistency", "Distance matches path length"}
                        };
                    } else {
                        testResults["test3_shortestPath"]["status"] = "[FAIL]";
                        testResults["test3_shortestPath"]["details"] = "Inconsistent path/distance";
                    }
                } else {
                    testResults["test3_shortestPath"]["status"] = "[SKIP]";
                    testResults["test3_shortestPath"]["reason"] = "Need at least 2 users in graph";
                }
            } catch (const std::exception& e) {
                testResults["test3_shortestPath"]["status"] = "[FAIL]";
                testResults["test3_shortestPath"]["error"] = e.what();
            }
            
            // Test 4: GraphStats
            testResults["test4_graphStats"]["status"] = "Testing...";
            try {
                int totalUsers = graph->nodeCount();
                int totalFriendships = GraphStats::countEdges(*graph, true);
                float averageDegree = GraphStats::getAverageDegree(*graph);
                float density = GraphStats::getDensity(*graph);
                float clusteringCoefficient = GraphStats::getAverageClusteringCoefficient(*graph);
                int connectedComponents = GraphStats::countComponents(*graph);

                bool avgDegreeValid = (averageDegree >= 0);
                bool densityValid = (density >= 0 && density <= 1);
                bool clusteringValid = (clusteringCoefficient >= 0 && clusteringCoefficient <= 1);

                if (avgDegreeValid && densityValid && clusteringValid) {
                    testResults["test4_graphStats"]["status"] = "[PASS]";
                    testResults["test4_graphStats"]["details"] = {
                        {"totalUsers", totalUsers},
                        {"totalFriendships", totalFriendships},
                        {"averageDegree", averageDegree},
                        {"density", density},
                        {"clusteringCoefficient", clusteringCoefficient},
                        {"connectedComponents", connectedComponents},
                        {"validation", "All metrics within valid ranges"}
                    };
                } else {
                    testResults["test4_graphStats"]["status"] = "[FAIL]";
                    testResults["test4_graphStats"]["details"] = "Invalid metric values";
                }
            } catch (const std::exception& e) {
                testResults["test4_graphStats"]["status"] = "[FAIL]";
                testResults["test4_graphStats"]["error"] = e.what();
            }
            
            // Test 5: PopularityRanker (Uses PriorityQueue)
            testResults["test5_popularityRanker"]["status"] = "Testing...";
            try {
                LinkedList<UserScore> topUsers = popularityRanker->getTopNPopularUsers(3);
                LinkedList<UserScore> allRanked = popularityRanker->getAllUsersRanked();
                
                bool descendingOrder = true;
                for (int i = 1; i < topUsers.size(); i++) {
                    if (topUsers[i].score > topUsers[i-1].score) {
                        descendingOrder = false;
                        break;
                    }
                }
                
                bool sizeCorrect = (topUsers.size() <= 3) && 
                                  (topUsers.size() <= allRanked.size());
                
                if (descendingOrder && sizeCorrect) {
                    testResults["test5_popularityRanker"]["status"] = "[PASS]";
                    
                    json topUsersJson = json::array();
                    for (int i = 0; i < topUsers.size(); i++) {
                        topUsersJson.push_back({
                            {"userId", topUsers[i].userId},
                            {"score", topUsers[i].score}
                        });
                    }
                    
                    testResults["test5_popularityRanker"]["details"] = {
                        {"topUsers", topUsersJson},
                        {"totalRanked", allRanked.size()},
                        {"ordering", "Descending by score (Max-Heap working)"}
                    };
                } else {
                    testResults["test5_popularityRanker"]["status"] = "[FAIL]";
                    testResults["test5_popularityRanker"]["details"] = "Incorrect ordering or size";
                }
            } catch (const std::exception& e) {
                testResults["test5_popularityRanker"]["status"] = "[FAIL]";
                testResults["test5_popularityRanker"]["error"] = e.what();
            }
            // Test 6: FriendSuggestion (2-hop algorithm)
            testResults["test6_friendSuggestion"]["status"] = "Testing...";
            try {
                LinkedList<int> allUsers = graph->getAllNodeIDs();
                if (!allUsers.isEmpty()) {
                    LinkedList<Suggestion> suggestions = friendSuggestion->getSuggestions(allUsers[0], 5);
                    LinkedList<int> twoHop = friendSuggestion->getTwoHopFriends(allUsers[0]);
                    
                    bool validSuggestions = true;
                    LinkedList<Edge>& userFriends = graph->getNeighbors(allUsers[0]);
                    
                    // Suggestions should not include the user themselves or direct friends
                    for (int i = 0; i < suggestions.size(); i++) {
                        if (suggestions[i].userId == allUsers[0]) {
                            validSuggestions = false;
                            break;
                        }
                        for (int j = 0; j < userFriends.size(); j++) {
                            if (suggestions[i].userId == userFriends[j].to) {
                                validSuggestions = false;
                                break;
                            }
                        }
                    }
                    
                    if (validSuggestions) {
                        testResults["test6_friendSuggestion"]["status"] = "[PASS]";
                        testResults["test6_friendSuggestion"]["details"] = {
                            {"userId", allUsers[0]},
                            {"suggestionsCount", suggestions.size()},
                            {"twoHopFriendsCount", twoHop.size()},
                            {"validation", "No self or direct friends in suggestions"}
                        };
                    } else {
                        testResults["test6_friendSuggestion"]["status"] = "[FAIL]";
                        testResults["test6_friendSuggestion"]["details"] = "Invalid suggestions (contains self or direct friends)";
                    }
                } else {
                    testResults["test6_friendSuggestion"]["status"] = "[SKIP]";
                    testResults["test6_friendSuggestion"]["reason"] = "Need users in graph";
                }
            } catch (const std::exception& e) {
                testResults["test6_friendSuggestion"]["status"] = "[FAIL]";
                testResults["test6_friendSuggestion"]["error"] = e.what();
            }
            // Test Summary
            int passed = 0, failed = 0, skipped = 0;
            
            for (auto& [key, value] : testResults.items()) {
                if (key.find("test") == 0 && value.contains("status")) {
                    std::string status = value["status"].get<std::string>();
                    if (status.find("PASS") != std::string::npos) passed++;
                    else if (status.find("FAIL") != std::string::npos) failed++;
                    else if (status.find("SKIP") != std::string::npos) skipped++;
                }
            }
            
            testResults["summary"] = {
                {"totalTests", passed + failed + skipped},
                {"passed", passed},
                {"failed", failed},
                {"skipped", skipped},
                {"passRate", (passed + failed > 0) ? 
                    (double)passed / (passed + failed) * 100.0 : 0.0},
                {"overallStatus", (failed == 0 && passed > 0) ? 
                    "[PASS] ALL TESTS PASSED" : 
                    (failed > 0 ? "[FAIL] SOME TESTS FAILED" : "[SKIP] NO TESTS RUN")}
            };
            
            return crow::response(200, testResults.dump(2));
            
        } catch (const std::exception& e) {
            json error;
            error["error"] = "Test suite crashed";
            error["message"] = e.what();
            error["component"] = "Member 3 - Unit Tests";
            return crow::response(500, error.dump());
        }
    });
}

// STANDALONE TEST SERVER (Member 3 Only)
// Compile with: -DSTANDALONE_TEST flag
// For integration: compile WITHOUT this flag

#ifdef STANDALONE_TEST

#include "../../dsa/graph/Graph.h"

int main() {
    crow::App<CORS> app;
;
    
    // Initialize core graph
    Graph graph;
    
    // Add test data
    std::cout << "\nSetting up test data..." << std::endl;
    
    // Add test nodes and edges
    for (int i = 1; i <= 5; i++) {
        graph.addNode(i);
    }
    
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    
    std::cout << "[PASS] Graph initialized\n" << std::endl;
    
    // Initialize Member 3's algorithm modules
    MutualFriends mutualFriends(&graph);
    ShortestPath shortestPath(&graph);
    GraphStats graphStats;
    PopularityRanker popularityRanker(&graph);
    FriendSuggestion friendSuggestion(&graph, &mutualFriends);
    
    // Setup all algorithm routes
    setupAlgoRoutes(app, &graph, &mutualFriends, &shortestPath, 
                    &graphStats, &popularityRanker, &friendSuggestion);
    
    std::cout << "  Server: http://localhost:8080" << std::endl;
    std::cout << "\nAPI TEST ENDPOINT:" << std::endl;
    std::cout << "   http://localhost:8080/api/algo/unit-tests" << std::endl;
    std::cout << "\nAPI Endpoints:" << std::endl;
    std::cout << "   /api/algo/graph-stats" << std::endl;
    std::cout << "   /api/algo/shortest-path?start=X&end=Y" << std::endl;
    std::cout << "   /api/algo/mutual-friends?user1=X&user2=Y" << std::endl;
    std::cout << "   /api/algo/top-popular?n=5" << std::endl;
    std::cout << "   /api/algo/friend-suggestions?userId=X&limit=10" << std::endl;
    std::cout << "   /api/algo/two-hop-friends?userId=X" << std::endl;
    std::cout << "   /api/algo/users-within-distance?userId=X&distance=2" << std::endl;
    std::cout << "   /api/algo/user-degree?userId=X" << std::endl;
    std::cout << "   /api/algo/user-rank?userId=X" << std::endl;
    std::cout << "\nTest Commands:" << std::endl;
    std::cout << "   curl http://localhost:8080/api/algo/unit-tests" << std::endl;
    std::cout << "   curl http://localhost:8080/api/algo/graph-stats" << std::endl;
    std::cout << "\nPress Ctrl+C to stop server" << std::endl;
    
    // Start server
    app.port(8080).multithreaded().run();
    
    return 0;
}

#endif // STANDALONE_TEST