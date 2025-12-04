#include "../../messaging/TopKConversations.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testAddAndGetTopK() {
    cout << "Testing add and getTopK..." << endl;
    TopKConversations topK;
    
    // Add conversations with different interaction counts
    topK.addConversation("alice", 50);
    topK.addConversation("bob", 100);
    topK.addConversation("charlie", 75);
    topK.addConversation("david", 200);
    topK.addConversation("eve", 30);
    
    // Get top 3
    DynamicArray<string> top3 = topK.getTopK(3);
    assert(top3.size() == 3);
    assert(top3.get(0) == "david");   // 200
    assert(top3.get(1) == "bob");     // 100
    assert(top3.get(2) == "charlie"); // 75
    
    cout << " Add and getTopK tests passed!" << endl;
}

void testGetMoreThanAvailable() {
    cout << "Testing getTopK with k > size..." << endl;
    TopKConversations topK;
    
    topK.addConversation("user1", 10);
    topK.addConversation("user2", 20);
    
    // Request more than available
    DynamicArray<string> result = topK.getTopK(5);
    assert(result.size() == 2); // Should only return available items
    
    cout << " Get more than available tests passed!" << endl;
}

void testNonDestructiveGetTopK() {
    cout << "Testing non-destructive getTopK..." << endl;
    TopKConversations topK;
    
    topK.addConversation("alice", 50);
    topK.addConversation("bob", 100);
    topK.addConversation("charlie", 75);
    
    // Get top 2 multiple times
    DynamicArray<string> first = topK.getTopK(2);
    assert(first.size() == 2);
    
    DynamicArray<string> second = topK.getTopK(2);
    assert(second.size() == 2);
    
    // Results should be the same (non-destructive)
    assert(first.get(0) == second.get(0));
    assert(first.get(1) == second.get(1));
    
    cout << " Non-destructive getTopK tests passed!" << endl;
}

void testSameInteractionCount() {
    cout << "Testing users with same interaction count..." << endl;
    TopKConversations topK;
    
    topK.addConversation("user1", 50);
    topK.addConversation("user2", 50);
    topK.addConversation("user3", 50);
    topK.addConversation("user4", 100);
    
    DynamicArray<string> top2 = topK.getTopK(2);
    assert(top2.size() == 2);
    assert(top2.get(0) == "user4"); // Highest
    // Second can be any of user1, user2, user3
    
    cout << " Same interaction count tests passed!" << endl;
}

void testEmptyTopK() {
    cout << "Testing empty TopK..." << endl;
    TopKConversations topK;
    
    DynamicArray<string> result = topK.getTopK(5);
    assert(result.size() == 0);
    
    cout << " Empty TopK tests passed!" << endl;
}

void testLargeTopK() {
    cout << "Testing large TopK dataset..." << endl;
    TopKConversations topK;
    
    // Add 100 conversations
    for (int i = 0; i < 100; i++) {
        topK.addConversation("user" + to_string(i), i * 10);
    }
    
    // Get top 10
    DynamicArray<string> top10 = topK.getTopK(10);
    assert(top10.size() == 10);
    
    // Verify they're in descending order
    assert(top10.get(0) == "user99");  // 990
    assert(top10.get(1) == "user98");  // 980
    assert(top10.get(9) == "user90");  // 900
    
    cout << " Large TopK tests passed!" << endl;
}

int main() {
    cout << "=== TopKConversations Unit Tests ===" << endl;
    
    try {
        testAddAndGetTopK();
        testGetMoreThanAvailable();
        testNonDestructiveGetTopK();
        testSameInteractionCount();
        testEmptyTopK();
        testLargeTopK();
        
        cout << "\n ALL TOPKCONVERSATIONS TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
