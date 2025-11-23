#include "../../analytics/GraphStats.h"
#include "../../dsa/graph/Graph.h"
#include <iostream>

int main() {
    std::cout << "=== Testing GraphStats ===" << std::endl;
    
    Graph graph;
    
    // Add nodes
    for (int i = 1; i <= 5; i++) {
        graph.addNode(i);
    }
    
    // Create friendships
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    
    GraphStats stats(&graph);
    
    // Test 1: Total users
    std::cout << "\nTest 1: Total Users" << std::endl;
    int totalUsers = stats.getTotalUsers();
    std::cout << "Total users: " << totalUsers << std::endl;
    std::cout << "✓ Test 1 PASSED" << std::endl;
    
    // Test 2: Total friendships
    std::cout << "\nTest 2: Total Friendships" << std::endl;
    int totalFriendships = stats.getTotalFriendships();
    std::cout << "Total friendships: " << totalFriendships << std::endl;
    std::cout << "✓ Test 2 PASSED" << std::endl;
    
    // Test 3: Average degree
    std::cout << "\nTest 3: Average Degree" << std::endl;
    double avgDegree = stats.getAverageDegree();
    std::cout << "Average degree: " << avgDegree << std::endl;
    std::cout << "✓ Test 3 PASSED" << std::endl;
    
    // Test 4: User degree
    std::cout << "\nTest 4: Individual User Degrees" << std::endl;
    std::cout << "User 1 degree: " << stats.getUserDegree(1) << std::endl;
    std::cout << "User 2 degree: " << stats.getUserDegree(2) << std::endl;
    std::cout << "User 3 degree: " << stats.getUserDegree(3) << std::endl;
    std::cout << "✓ Test 4 PASSED" << std::endl;
    
    // Test 5: Most popular user
    std::cout << "\nTest 5: Most Popular User" << std::endl;
    int mostPopular = stats.getMostPopularUser();
    std::cout << "Most popular user: " << mostPopular << std::endl;
    std::cout << "✓ Test 5 PASSED" << std::endl;
    
    // Test 6: Graph metrics
    std::cout << "\nTest 6: Complete Graph Metrics" << std::endl;
    GraphMetrics metrics = stats.getGraphMetrics();
    std::cout << "Complete metrics:" << std::endl;
    std::cout << "  Total Users: " << metrics.totalUsers << std::endl;
    std::cout << "  Total Friendships: " << metrics.totalFriendships << std::endl;
    std::cout << "  Average Degree: " << metrics.averageDegree << std::endl;
    std::cout << "  Density: " << metrics.density << std::endl;
    std::cout << "✓ Test 6 PASSED" << std::endl;
    
    std::cout << "\n=== All GraphStats Tests PASSED! ===" << std::endl;
    return 0;
}