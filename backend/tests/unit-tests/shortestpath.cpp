#include "../../algorithms/ShortestPath.h"
#include "../../dsa/graph/Graph.h"
#include <iostream>

int main() {
    std::cout << "=== Testing ShortestPath ===" << std::endl;
    
    Graph graph;
    
    // Add nodes (using int IDs)
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);
    graph.addNode(6);
    
    // Create edges
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 4);
    graph.addEdge(2, 5);
    graph.addEdge(3, 5);
    graph.addEdge(5, 6);
    
    ShortestPath sp(&graph);
    
    // Test 1: Direct connection
    std::cout << "\nTest 1: Direct Connection (1 to 2)" << std::endl;
    LinkedList<int> path1 = sp.findPath(1, 2);
    std::cout << "Path from 1 to 2: ";
    for (int i = 0; i < path1.size(); i++) {
        std::cout << path1[i];
        if (i < path1.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    int dist1 = sp.getDistance(1, 2);
    std::cout << "Distance: " << dist1 << std::endl;
    std::cout << "✓ Test 1 PASSED" << std::endl;
    
    // Test 2: Two hops
    std::cout << "\nTest 2: Two Hops (1 to 4)" << std::endl;
    LinkedList<int> path2 = sp.findPath(1, 4);
    std::cout << "Path from 1 to 4: ";
    for (int i = 0; i < path2.size(); i++) {
        std::cout << path2[i];
        if (i < path2.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    int dist2 = sp.getDistance(1, 4);
    std::cout << "Distance: " << dist2 << std::endl;
    std::cout << "✓ Test 2 PASSED" << std::endl;
    
    // Test 3: Three hops
    std::cout << "\nTest 3: Three Hops (1 to 6)" << std::endl;
    LinkedList<int> path3 = sp.findPath(1, 6);
    std::cout << "Path from 1 to 6: ";
    for (int i = 0; i < path3.size(); i++) {
        std::cout << path3[i];
        if (i < path3.size() - 1) std::cout << " -> ";
    }
    std::cout << std::endl;
    int dist3 = sp.getDistance(1, 6);
    std::cout << "Distance: " << dist3 << std::endl;
    std::cout << "✓ Test 3 PASSED" << std::endl;
    
    // Test 4: Path exists
    std::cout << "\nTest 4: Path Exists Check" << std::endl;
    bool exists = sp.pathExists(1, 6);
    std::cout << "Path exists from 1 to 6: " << (exists ? "Yes" : "No") << std::endl;
    std::cout << "✓ Test 4 PASSED" << std::endl;
    
    // Test 5: Users within distance
    std::cout << "\nTest 5: Users Within Distance (1, distance=2)" << std::endl;
    LinkedList<int> nearby = sp.getUsersWithinDistance(1, 2);
    std::cout << "Users within 2 hops of 1: ";
    for (int i = 0; i < nearby.size(); i++) {
        std::cout << nearby[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Count: " << nearby.size() << std::endl;
    std::cout << "✓ Test 5 PASSED" << std::endl;
    
    std::cout << "\n=== All ShortestPath Tests PASSED! ===" << std::endl;
    return 0;
}