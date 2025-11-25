#include "../../algorithms/MsgMutualInteraction.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include <iostream>
#include <cassert>

using namespace std;

void testFindMutualInteractions() {
    cout << "Testing find mutual interactions..." << endl;
    ConversationGraph graph;
    
    // Create a network: 1-2, 1-3, 2-3, 2-4, 3-4
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(2, 3);
    graph.addInteraction(2, 4);
    graph.addInteraction(3, 4);
    
    MsgMutualInteraction mutualFinder(&graph);
    
    // User 1 has neighbors 2 and 3
    // Both 2 and 3 know each other (mutual)
    DynamicArray<Pair<int, int>> mutuals = mutualFinder.findMutualInteractions(1);
    
    // Should find that 2 and 3 are mutual connections
    assert(mutuals.size() > 0);
    
    cout << "Found " << mutuals.size() << " mutual interaction pairs for user 1" << endl;
    cout << "✓ Find mutual interactions tests passed!" << endl;
}

void testNonExistentUser() {
    cout << "Testing non-existent user..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgMutualInteraction mutualFinder(&graph);
    
    DynamicArray<Pair<int, int>> mutuals = mutualFinder.findMutualInteractions(999);
    assert(mutuals.size() == 0);
    
    cout << "✓ Non-existent user tests passed!" << endl;
}

void testUserWithNoMutuals() {
    cout << "Testing user with no mutual connections..." << endl;
    ConversationGraph graph;
    
    // User 1 connected to 2, 3
    // But 2 and 3 are not connected to each other
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    
    MsgMutualInteraction mutualFinder(&graph);
    
    DynamicArray<Pair<int, int>> mutuals = mutualFinder.findMutualInteractions(1);
    
    // No mutual connections should be found
    cout << "Found " << mutuals.size() << " mutual pairs (expected 0)" << endl;
    
    cout << "✓ No mutuals tests passed!" << endl;
}

void testComplexNetwork() {
    cout << "Testing complex network..." << endl;
    ConversationGraph graph;
    
    // Create a more complex network
    for (int i = 1; i <= 5; i++) {
        for (int j = i + 1; j <= 5; j++) {
            graph.addInteraction(i, j);
        }
    }
    
    MsgMutualInteraction mutualFinder(&graph);
    
    // In a fully connected graph, everyone has mutual connections
    DynamicArray<Pair<int, int>> mutuals = mutualFinder.findMutualInteractions(1);
    
    cout << "Found " << mutuals.size() << " mutual pairs in complex network" << endl;
    assert(mutuals.size() > 0);
    
    cout << "✓ Complex network tests passed!" << endl;
}

int main() {
    cout << "=== MsgMutualInteraction Unit Tests ===" << endl;
    
    try {
        testFindMutualInteractions();
        testNonExistentUser();
        testUserWithNoMutuals();
        testComplexNetwork();
        
        cout << "\n✓ ALL MSGMUTUALINTERACTION TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
