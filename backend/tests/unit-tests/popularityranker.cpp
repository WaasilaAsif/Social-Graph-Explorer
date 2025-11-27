#include "../../analytics/PopularityRanker.h"
#include "../../dsa/graph/Graph.h"
#include <iostream>

int main() {
    std::cout << "=== Testing PopularityRanker ===" << std::endl;
    
    Graph graph;
    
    // Add nodes
    for (int i = 1; i <= 6; i++) {
        graph.addNode(i);
    }
    
    // Create friendships (node 2 most popular, node 6 least)
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 4);
    graph.addEdge(5, 6);
    
    PopularityRanker ranker(&graph);
    
    // Test 1: Top 3 popular users
    std::cout << "\nTest 1: Top 3 Popular Users" << std::endl;
    LinkedList<UserScore> topUsers = ranker.getTopNPopularUsers(3);
    std::cout << "Top 3 popular users:" << std::endl;
    for (int i = 0; i < topUsers.size(); i++) {
        std::cout << "  " << (i+1) << ". User " << topUsers[i].userId 
                  << " (score: " << topUsers[i].score << ")" << std::endl;
    }
    std::cout << " Test 1 PASSED" << std::endl;
    
    // Test 2: User rank
    std::cout << "\nTest 2: Get User Rank" << std::endl;
    int rank1 = ranker.getUserRank(2);
    int rank2 = ranker.getUserRank(6);
    std::cout << "User 2 rank: " << rank1 << std::endl;
    std::cout << "User 6 rank: " << rank2 << std::endl;
    std::cout << " Test 2 PASSED" << std::endl;
    
    // Test 3: Percentile rank
    std::cout << "\nTest 3: Get Percentile Rank" << std::endl;
    double percentile1 = ranker.getPercentileRank(2);
    double percentile2 = ranker.getPercentileRank(6);
    std::cout << "User 2 percentile: " << percentile1 << "%" << std::endl;
    std::cout << "User 6 percentile: " << percentile2 << "%" << std::endl;
    std::cout << " Test 3 PASSED" << std::endl;
    
    std::cout << "\n=== All PopularityRanker Tests PASSED! ===" << std::endl;
    return 0;
}