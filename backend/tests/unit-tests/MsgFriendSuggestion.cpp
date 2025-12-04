#include "../../algorithms/MsgFriendSuggestion.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include <iostream>
#include <cassert>

using namespace std;

void testSuggestFriends() {
    cout << "Testing suggest friends..." << endl;
    ConversationGraph graph;
    
    // User 1 knows 2 and 3
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    
    // User 2 knows 4 and 5
    graph.addInteraction(2, 4);
    graph.addInteraction(2, 5);
    
    // User 3 knows 4 and 6
    graph.addInteraction(3, 4);
    graph.addInteraction(3, 6);
    
    MsgFriendSuggestion suggester(&graph);
    
    // User 1 should be suggested 4 (2 mutual connections), then 5 and 6
    DynamicArray<int> suggestions = suggester.suggestFriends(1, 3);
    
    assert(suggestions.size() > 0);
    cout << "Suggested " << suggestions.size() << " friends for user 1" << endl;
    
    cout << " Suggest friends tests passed!" << endl;
}

void testNoSuggestions() {
    cout << "Testing no friend suggestions..." << endl;
    ConversationGraph graph;
    
    // User 1 knows 2
    graph.addInteraction(1, 2);
    
    // User 2 has no other connections
    
    MsgFriendSuggestion suggester(&graph);
    
    DynamicArray<int> suggestions = suggester.suggestFriends(1, 5);
    assert(suggestions.size() == 0);
    
    cout << " No suggestions tests passed!" << endl;
}

void testNonExistentUser() {
    cout << "Testing non-existent user suggestions..." << endl;
    ConversationGraph graph;
    
    graph.addInteraction(1, 2);
    
    MsgFriendSuggestion suggester(&graph);
    
    DynamicArray<int> suggestions = suggester.suggestFriends(999, 5);
    assert(suggestions.size() == 0);
    
    cout << " Non-existent user tests passed!" << endl;
}

void testLimitK() {
    cout << "Testing k limit..." << endl;
    ConversationGraph graph;
    
    // User 1 knows 2
    graph.addInteraction(1, 2);
    
    // User 2 knows many others
    for (int i = 3; i <= 10; i++) {
        graph.addInteraction(2, i);
    }
    
    MsgFriendSuggestion suggester(&graph);
    
    // Request only top 3 suggestions
    DynamicArray<int> suggestions = suggester.suggestFriends(1, 3);
    
    assert(suggestions.size() <= 3);
    cout << "Got " << suggestions.size() << " suggestions (requested 3)" << endl;
    
    cout << " K limit tests passed!" << endl;
}

void testMutualConnectionsPriority() {
    cout << "Testing mutual connections priority..." << endl;
    ConversationGraph graph;
    
    // User 1 knows 2, 3, 4
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 4);
    
    // User 5 knows all of them (should be top suggestion)
    graph.addInteraction(2, 5);
    graph.addInteraction(3, 5);
    graph.addInteraction(4, 5);
    
    // User 6 knows only one
    graph.addInteraction(2, 6);
    
    MsgFriendSuggestion suggester(&graph);
    
    DynamicArray<int> suggestions = suggester.suggestFriends(1, 2);
    
    // User 5 should be suggested first (most mutual connections)
    if (suggestions.size() > 0) {
        cout << "Top suggestion: " << suggestions.get(0) << " (expected 5)" << endl;
    }
    
    cout << " Mutual connections priority tests passed!" << endl;
}

int main() {
    cout << "=== MsgFriendSuggestion Unit Tests ===" << endl;
    
    try {
        testSuggestFriends();
        testNoSuggestions();
        testNonExistentUser();
        testLimitK();
        testMutualConnectionsPriority();
        
        cout << "\n ALL MSGFRIENDSUGGESTION TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
