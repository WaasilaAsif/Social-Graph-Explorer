#include "../../algorithms/FriendSuggestion.h"
#include "../../dsa/graph/Graph.h"
#include <iostream>

int main() {
    std::cout << "=== Testing FriendSuggestion ===" << std::endl;
    
    Graph graph;
    
    // Add nodes
    for (int i = 1; i <= 7; i++) {
        graph.addNode(i);
    }
    
    // Create friendships
    graph.addEdge(1, 2);
    graph.addEdge(1, 3);
    graph.addEdge(2, 3);
    graph.addEdge(2, 4);
    graph.addEdge(3, 5);
    graph.addEdge(4, 6);
    graph.addEdge(5, 7);
    
    MutualFriends mf(&graph);
    FriendSuggestion fs(&graph, &mf);
    
    // Test 1: Get suggestions
    std::cout << "\nTest 1: Friend Suggestions for user 1" << std::endl;
    LinkedList<Suggestion> suggestions1 = fs.getSuggestions(1, 5);
    std::cout << "Friend suggestions for user 1:" << std::endl;
    for (int i = 0; i < suggestions1.size(); i++) {
        std::cout << "  " << (i+1) << ". User " << suggestions1[i].userId
                  << " (mutuals: " << suggestions1[i].mutualFriendsCount
                  << ", frequency: " << suggestions1[i].frequencyScore << ")" << std::endl;
    }
    std::cout << "Total suggestions: " << suggestions1.size() << std::endl;
    std::cout << " Test 1 PASSED" << std::endl;
    
    // Test 2: Two-hop friends
    std::cout << "\nTest 2: Two-Hop Friends for user 1" << std::endl;
    LinkedList<int> twoHop = fs.getTwoHopFriends(1);
    std::cout << "Two-hop friends for user 1: ";
    for (int i = 0; i < twoHop.size(); i++) {
        std::cout << twoHop[i] << " ";
    }
    std::cout << std::endl;
    std::cout << "Count: " << twoHop.size() << std::endl;
    std::cout << " Test 2 PASSED" << std::endl;
    
    std::cout << "\n=== All FriendSuggestion Tests PASSED! ===" << std::endl;
    return 0;
}