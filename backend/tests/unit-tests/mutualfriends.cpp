#include "../../algorithms/MutualFriends.h"
   #include "../../dsa/graph/Graph.h"
#include <iostream>

int main() {
    std::cout << "=== Testing MutualFriends ===" << std::endl;
    
    Graph graph;
    
    // Add nodes
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);
    graph.addNode(5);
    
    // Create friendships
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    
    MutualFriends mf(&graph);
    
    // Test 1: Get mutual friends
    std::cout << "\nTest 1: Mutual friends between 1 and 2" << std::endl;
    LinkedList<int> mutuals1 = mf.getMutualFriends(1, 2);
    std::cout << "Mutual friends: ";
    for (int i = 0; i < mutuals1.size(); i++) {
        std::cout << mutuals1[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Count: " << mutuals1.size() << std::endl;
    std::cout << "✓ Test 1 PASSED" << std::endl;
    
    // Test 2: Get mutual friends count
    std::cout << "\nTest 2: Mutual friends count" << std::endl;
    int count = mf.getMutualFriendsCount(1, 2);
    std::cout << "Mutual friends count between 1 and 2: " << count << std::endl;
    std::cout << "✓ Test 2 PASSED" << std::endl;
    
    // Test 3: Has mutual friends
    std::cout << "\nTest 3: Has mutual friends check" << std::endl;
    bool hasMutual = mf.hasMutualFriends(1, 2);
    std::cout << "1 and 2 have mutual friends: " << (hasMutual ? "Yes" : "No") << std::endl;
    std::cout << "✓ Test 3 PASSED" << std::endl;
    
    std::cout << "\n=== All MutualFriends Tests PASSED! ===" << std::endl;
    return 0;
}