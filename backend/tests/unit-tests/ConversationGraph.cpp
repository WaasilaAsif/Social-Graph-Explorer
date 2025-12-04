#include "../../dsa/messaging_ds/ConversationGraph.h"
#include <iostream>
#include <cassert>
#include <algorithm>

using namespace std;

void testAddInteraction() {
    cout << "Testing add interaction..." << endl;
    ConversationGraph graph;
    
    // Add interactions
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(2, 3);
    
    // Verify users exist
    assert(graph.userExists(1));
    assert(graph.userExists(2));
    assert(graph.userExists(3));
    assert(!graph.userExists(4));
    
    cout << " Add interaction tests passed!" << endl;
}

void testInteractionWeights() {
    cout << "Testing interaction weights..." << endl;
    ConversationGraph graph;
    
    // Add single interaction
    graph.addInteraction(1, 2);
    assert(graph.getInteractionWeight(1, 2) == 1);
    assert(graph.getInteractionWeight(2, 1) == 1); // Bidirectional
    
    // Add multiple interactions between same users
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 2);
    assert(graph.getInteractionWeight(1, 2) == 3);
    assert(graph.getInteractionWeight(2, 1) == 3);
    
    // Check non-existent interaction
    assert(graph.getInteractionWeight(1, 3) == 0);
    assert(graph.getInteractionWeight(5, 6) == 0);
    
    cout << " Interaction weights tests passed!" << endl;
}

void testGetNeighbors() {
    cout << "Testing get neighbors..." << endl;
    ConversationGraph graph;
    
    // Build a small conversation network
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 4);
    graph.addInteraction(2, 3);
    
    // Get neighbors of user 1
    DynamicArray<int> neighbors = graph.getNeighbors(1);
    assert(neighbors.size() == 3);
    
    // Check all neighbors are present
    bool found2 = false, found3 = false, found4 = false;
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors.get(i) == 2) found2 = true;
        if (neighbors.get(i) == 3) found3 = true;
        if (neighbors.get(i) == 4) found4 = true;
    }
    assert(found2 && found3 && found4);
    
    // Get neighbors of user 2
    neighbors = graph.getNeighbors(2);
    assert(neighbors.size() == 2); // Connected to 1 and 3
    
    // Get neighbors of non-existent user
    neighbors = graph.getNeighbors(99);
    assert(neighbors.size() == 0);
    
    cout << " Get neighbors tests passed!" << endl;
}

void testBidirectionalEdges() {
    cout << "Testing bidirectional edges..." << endl;
    ConversationGraph graph;
    
    // Add interaction A -> B
    graph.addInteraction(5, 10);
    
    // Both users should have each other as neighbors
    DynamicArray<int> neighbors5 = graph.getNeighbors(5);
    DynamicArray<int> neighbors10 = graph.getNeighbors(10);
    
    assert(neighbors5.size() == 1);
    assert(neighbors5.get(0) == 10);
    
    assert(neighbors10.size() == 1);
    assert(neighbors10.get(0) == 5);
    
    // Weights should be equal in both directions
    assert(graph.getInteractionWeight(5, 10) == graph.getInteractionWeight(10, 5));
    
    cout << " Bidirectional edges tests passed!" << endl;
}

void testComplexNetwork() {
    cout << "Testing complex network..." << endl;
    ConversationGraph graph;
    
    // Build a conversation network
    // User 1 talks to 2 (5 times), 3 (2 times)
    for (int i = 0; i < 5; i++) graph.addInteraction(1, 2);
    for (int i = 0; i < 2; i++) graph.addInteraction(1, 3);
    
    // User 2 talks to 3 (3 times)
    for (int i = 0; i < 3; i++) graph.addInteraction(2, 3);
    
    // User 4 talks to 1 (1 time)
    graph.addInteraction(4, 1);
    
    // Verify weights
    assert(graph.getInteractionWeight(1, 2) == 5);
    assert(graph.getInteractionWeight(1, 3) == 2);
    assert(graph.getInteractionWeight(2, 3) == 3);
    assert(graph.getInteractionWeight(1, 4) == 1);
    
    // Verify neighbor counts
    assert(graph.getNeighbors(1).size() == 3); // 2, 3, 4
    assert(graph.getNeighbors(2).size() == 2); // 1, 3
    assert(graph.getNeighbors(3).size() == 2); // 1, 2
    assert(graph.getNeighbors(4).size() == 1); // 1
    
    cout << " Complex network tests passed!" << endl;
}

int main() {
    cout << "=== ConversationGraph Unit Tests ===" << endl;
    
    try {
        testAddInteraction();
        testInteractionWeights();
        testGetNeighbors();
        testBidirectionalEdges();
        testComplexNetwork();
        
        cout << "\n ALL CONVERSATIONGRAPH TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
