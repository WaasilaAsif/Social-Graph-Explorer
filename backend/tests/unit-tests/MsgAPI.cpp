#include "../../messaging/MessageStore.h"
#include "../../dsa/messaging_ds/MsgTrie.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include "../../algorithms/MsgFriendSuggestion.h"
#include "../../algorithms/MsgMutualInteraction.h"
#include "../../algorithms/MsgShortestPath.h"
#include "../../algorithms/MsgTopKMessages.h"
#include "../../algorithms/MsgPopularityRanker.h"
#include <iostream>
#include <cassert>

using namespace std;

void testMessageStoreBasics() {
    cout << "Testing MessageStore basics..." << endl;
    
    MessageStore msgStore;
    
    // Add messages  
    int msgId1 = msgStore.addMessage(1, 2, "Hello world");
    int msgId2 = msgStore.addMessage(2, 1, "Hi there");
    int msgId3 = msgStore.addMessage(1, 3, "Test message");
    
    assert(msgId1 == 1);
    assert(msgId2 == 2);
    assert(msgId3 == 3);
    
    // Retrieve messages
    Message* msg1 = msgStore.getMessage(msgId1);
    assert(msg1 != nullptr);
    assert(msg1->content == "Hello world");
    
    cout << "✓ MessageStore basic tests passed!" << endl;
}

void testWordExtraction() {
    cout << "Testing word extraction..." << endl;
    
    MessageStore msgStore;
    
    DynamicArray<string> words = msgStore.extractWords("Hello world test");
    
    assert(words.size() == 3);
    assert(words.get(0) == "hello");
    assert(words.get(1) == "world");
    assert(words.get(2) == "test");
    
    cout << "✓ Word extraction tests passed!" << endl;
}

void testTrieIndexing() {
    cout << "Testing Trie word indexing..." << endl;
    
    MsgTrie trie;
    MessageStore msgStore;
    
    // Add messages and index
    int msgId1 = msgStore.addMessage(1, 2, "hello world");
    int msgId2 = msgStore.addMessage(2, 1, "hello there");
    int msgId3 = msgStore.addMessage(1, 3, "goodbye world");
    
    // Extract and index words
    DynamicArray<string> words1 = msgStore.extractWords("hello world");
    for (int i = 0; i < words1.size(); i++) {
        trie.insert(words1.get(i), msgId1);
    }
    
    DynamicArray<string> words2 = msgStore.extractWords("hello there");
    for (int i = 0; i < words2.size(); i++) {
        trie.insert(words2.get(i), msgId2);
    }
    
    // Search
    DynamicArray<int> results = trie.search("hello");
    assert(results.size() == 2);
    
    cout << "✓ Trie indexing tests passed!" << endl;
}

void testConversationGraph() {
    cout << "Testing ConversationGraph..." << endl;
    
    ConversationGraph graph;
    
    // Add interactions
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 2); // Weight increases to 2
    graph.addInteraction(1, 3);
    
    // Get neighbors
    DynamicArray<int> neighbors = graph.getNeighbors(1);
    assert(neighbors.size() == 2);
    
    // Check weights
    int weight2 = graph.getInteractionWeight(1, 2);
    int weight3 = graph.getInteractionWeight(1, 3);
    
    assert(weight2 == 2); // Weight 2
    assert(weight3 == 1); // Weight 1
    
    cout << "✓ ConversationGraph tests passed!" << endl;
}

void testTopKInteractions() {
    cout << "Testing top K interactions..." << endl;
    
    ConversationGraph graph;
    
    // Add interactions
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 2); // Weight 2
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 3);
    graph.addInteraction(1, 3); // Weight 3
    
    MsgTopKMessages topK(&graph);
    DynamicArray<Pair<int, int>> results = topK.getTopKInteractions(1, 2);
    
    assert(results.size() == 2);
    assert(results.get(0).first == 3); // User 3 has weight 3
    assert(results.get(0).second == 3);
    assert(results.get(1).first == 2); // User 2 has weight 2
    assert(results.get(1).second == 2);
    
    cout << "✓ Top K interactions tests passed!" << endl;
}

void testFriendSuggestions() {
    cout << "Testing friend suggestions..." << endl;
    
    ConversationGraph graph;
    
    // Create network: 1-2, 2-3, 2-4
    graph.addInteraction(1, 2);
    graph.addInteraction(2, 3);
    graph.addInteraction(2, 4);
    
    MsgFriendSuggestion suggester(&graph);
    DynamicArray<int> suggestions = suggester.suggestFriends(1, 3);
    
    // Should suggest 3 and 4 (friends of friend 2)
    assert(suggestions.size() == 2);
    
    cout << "✓ Friend suggestions tests passed!" << endl;
}

void testMutualInteractions() {
    cout << "Testing mutual interactions..." << endl;
    
    ConversationGraph graph;
    
    // Create network with mutual connections
    graph.addInteraction(1, 2);
    graph.addInteraction(1, 3);
    graph.addInteraction(2, 3);
    
    MsgMutualInteraction mutual(&graph);
    DynamicArray<Pair<int, int>> results = mutual.findMutualInteractions(1);
    
    // Should find (2, 3) as mutual connection - both 2 and 3 are neighbors of 1, and they connect to each other
    assert(results.size() > 0);
    
    cout << "✓ Mutual interactions tests passed!" << endl;
}

void testShortestPath() {
    cout << "Testing shortest path..." << endl;
    
    ConversationGraph graph;
    
    // Create path: 1-2-3-4
    graph.addInteraction(1, 2);
    graph.addInteraction(2, 3);
    graph.addInteraction(3, 4);
    
    MsgShortestPath pathFinder(&graph);
    DynamicArray<int> path = pathFinder.findShortestPath(1, 4);
    
    assert(path.size() == 4); // [1, 2, 3, 4]
    assert(path.get(0) == 1);
    assert(path.get(1) == 2);
    assert(path.get(2) == 3);
    assert(path.get(3) == 4);
    
    cout << "✓ Shortest path tests passed!" << endl;
}

void testIntegrationScenario() {
    cout << "Testing integration scenario..." << endl;
    
    MessageStore msgStore;
    MsgTrie trie;
    ConversationGraph graph;
    
    // Add messages
    int msgId1 = msgStore.addMessage(1, 2, "Hey how are you");
    int msgId2 = msgStore.addMessage(2, 1, "I am doing great thanks");
    int msgId3 = msgStore.addMessage(1, 3, "Hello friend");
    
    // Index words
    DynamicArray<string> words1 = msgStore.extractWords("Hey how are you");
    for (int i = 0; i < words1.size(); i++) {
        trie.insert(words1.get(i), msgId1);
    }
    
    DynamicArray<string> words2 = msgStore.extractWords("I am doing great thanks");
    for (int i = 0; i < words2.size(); i++) {
        trie.insert(words2.get(i), msgId2);
    }
    
    // Build conversation graph
    graph.addInteraction(1, 2);
    graph.addInteraction(2, 1);
    graph.addInteraction(1, 3);
    
    // Search
    DynamicArray<int> results = trie.search("great");
    assert(results.size() == 1);
    assert(results.get(0) == msgId2);
    
    // Top K
    MsgTopKMessages topK(&graph);
    DynamicArray<Pair<int, int>> topUsers = topK.getTopKInteractions(1, 2);
    assert(topUsers.size() == 2);
    
    cout << "✓ Integration scenario tests passed!" << endl;
}

int main() {
    cout << "=== Messaging System Integration Tests ===" << endl;
    
    try {
        testMessageStoreBasics();
        testWordExtraction();
        testTrieIndexing();
        testConversationGraph();
        testTopKInteractions();
        testFriendSuggestions();
        testMutualInteractions();
        testShortestPath();
        testIntegrationScenario();
        
        cout << "\n✓ ALL MESSAGING INTEGRATION TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
