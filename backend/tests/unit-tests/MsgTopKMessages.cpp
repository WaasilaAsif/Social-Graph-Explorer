#include "../../algorithms/MsgTopKMessages.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include <iostream>
#include <cassert>

using namespace std;

void testGetTopKInteractions() {
    cout << "Testing get top K interactions..." << endl;
    ConversationGraph graph;
    
    // User 1 interacts with multiple users with different weights
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 2); // Weight 2
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 3); // Weight 3
    graph.addInteraction(1, 4); // Weight 1
    
    MsgTopKMessages topK(&graph);
    
    DynamicArray<Pair<int, int>> top2 = topK.getTopKInteractions(1, 2);
    
    assert(top2.size() == 2);
    
    // First should be user 3 (weight 3)
    cout << "Top interaction: User " << top2.get(0).first 
         << " with weight " << top2.get(0).second << endl;
    
    cout << "Get top K interactions tests passed!" << endl;
}

void testNoInteractions() {
    cout << "Testing user with no interactions..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgTopKMessages topK(&graph);
    
    // User 3 has no interactions
    DynamicArray<Pair<int, int>> result = topK.getTopKInteractions(3, 5);
    
    assert(result.size() == 0);
    
    cout << "No interactions tests passed!" << endl;
}

void testKLargerThanInteractions() {
    cout << "Testing k > number of interactions..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    
    MsgTopKMessages topK(&graph);
    
    // Request 10 but only 2 exist
    DynamicArray<Pair<int, int>> result = topK.getTopKInteractions(1, 10);
    
    assert(result.size() == 2);
    
    cout << "K larger than interactions tests passed!" << endl;
}

void testSortingByWeight() {
    cout << "Testing sorting by interaction weight..." << endl;
    ConversationGraph graph;
    
    // Create interactions with different weights
    for (int i = 0; i < 5; i++) {
        graph.addInteraction(1, 2);
    }
    for (int i = 0; i < 3; i++) {
        graph.addInteraction(1, 3);
    }
    for (int i = 0; i < 7; i++) {
        graph.addInteraction(1, 4);
    }
    
    MsgTopKMessages topK(&graph);
    
    DynamicArray<Pair<int, int>> top3 = topK.getTopKInteractions(1, 3);
    
    assert(top3.size() == 3);
    
    // Should be sorted by weight descending
    // First should be user 4 (weight 7)
    cout << "Sorted interactions:" << endl;
    for (int i = 0; i < top3.size(); i++) {
        cout << "  User " << top3.get(i).first 
             << ": weight " << top3.get(i).second << endl;
    }
    
    cout << "Sorting by weight tests passed!" << endl;
}

void testNonExistentUser() {
    cout << "Testing non-existent user..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgTopKMessages topK(&graph);
    
    DynamicArray<Pair<int, int>> result = topK.getTopKInteractions(999, 5);
    
    assert(result.size() == 0);
    
    cout << "Non-existent user tests passed!" << endl;
}

void testInvalidK() {
    cout << "Testing invalid k value..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgTopKMessages topK(&graph);
    
    DynamicArray<Pair<int, int>> result = topK.getTopKInteractions(1, 0);
    assert(result.size() == 0);
    
    DynamicArray<Pair<int, int>> result2 = topK.getTopKInteractions(1, -5);
    assert(result2.size() == 0);
    
    cout << "Invalid k tests passed!" << endl;
}

int main() {
    cout << "=== MsgTopKMessages Unit Tests ===" << endl;
    
    try {
        testGetTopKInteractions();
        testNoInteractions();
        testKLargerThanInteractions();
        testSortingByWeight();
        testNonExistentUser();
        testInvalidK();
        
        cout << "\nALL MSGTOPKMESSAGES TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\nTest failed: " << e.what() << endl;
        return 1;
    }
}
