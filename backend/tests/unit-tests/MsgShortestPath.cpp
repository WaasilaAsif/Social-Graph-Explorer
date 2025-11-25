#include "../../algorithms/MsgShortestPath.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include <iostream>
#include <cassert>

using namespace std;

void testShortestPathDirect() {
    cout << "Testing shortest path (direct connection)..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    graph.addInteraction(2, 3);
    
    MsgShortestPath pathFinder(&graph);
    
    DynamicArray<int> path = pathFinder.findShortestPath(1, 2);
    
    assert(path.size() == 2);
    assert(path.get(0) == 1);
    assert(path.get(1) == 2);
    
    cout << "✓ Direct connection tests passed!" << endl;
}

void testShortestPathMultiHop() {
    cout << "Testing shortest path (multi-hop)..." << endl;
    ConversationGraph graph;
    
    // Create path: 1-2-3-4
    graph.addInteraction(1, 2);
    graph.addInteraction(2, 3);
    graph.addInteraction(3, 4);
    
    MsgShortestPath pathFinder(&graph);
    
    DynamicArray<int> path = pathFinder.findShortestPath(1, 4);
    
    assert(path.size() == 4);
    assert(path.get(0) == 1);
    assert(path.get(path.size() - 1) == 4);
    
    cout << "Path length: " << path.size() << " nodes" << endl;
    cout << "✓ Multi-hop tests passed!" << endl;
}

void testNoPathExists() {
    cout << "Testing no path exists..." << endl;
    ConversationGraph graph;
    
    // Two disconnected components
    graph.addInteraction(1, 2);
    graph.addInteraction(3, 4);
    
    MsgShortestPath pathFinder(&graph);
    
    DynamicArray<int> path = pathFinder.findShortestPath(1, 4);
    
    assert(path.size() == 0);
    
    cout << "✓ No path tests passed!" << endl;
}

void testSameSourceAndDest() {
    cout << "Testing same source and destination..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgShortestPath pathFinder(&graph);
    
    DynamicArray<int> path = pathFinder.findShortestPath(1, 1);
    
    assert(path.size() == 1);
    assert(path.get(0) == 1);
    
    cout << "✓ Same source/dest tests passed!" << endl;
}

void testShortestPathInComplexGraph() {
    cout << "Testing shortest path in complex graph..." << endl;
    ConversationGraph graph;
    
    // Create a graph with multiple paths
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(2, 4);
    graph.addInteraction(3, 4);
    graph.addInteraction(3, 5);
    graph.addInteraction(4, 6);
    graph.addInteraction(5, 6);
    
    MsgShortestPath pathFinder(&graph);
    
    // Find shortest path from 1 to 6
    DynamicArray<int> path = pathFinder.findShortestPath(1, 6);
    
    assert(path.size() > 0);
    assert(path.get(0) == 1);
    assert(path.get(path.size() - 1) == 6);
    
    cout << "Path found with " << path.size() << " nodes" << endl;
    
    cout << "✓ Complex graph tests passed!" << endl;
}

void testNonExistentUsers() {
    cout << "Testing non-existent users..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgShortestPath pathFinder(&graph);
    
    DynamicArray<int> path1 = pathFinder.findShortestPath(999, 2);
    assert(path1.size() == 0);
    
    DynamicArray<int> path2 = pathFinder.findShortestPath(1, 999);
    assert(path2.size() == 0);
    
    cout << "✓ Non-existent users tests passed!" << endl;
}

int main() {
    cout << "=== MsgShortestPath Unit Tests ===" << endl;
    
    try {
        testShortestPathDirect();
        testShortestPathMultiHop();
        testNoPathExists();
        testSameSourceAndDest();
        testShortestPathInComplexGraph();
        testNonExistentUsers();
        
        cout << "\n✓ ALL MSGSHORTESTPATH TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
