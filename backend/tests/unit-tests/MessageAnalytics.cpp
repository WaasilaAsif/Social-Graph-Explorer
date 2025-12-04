#include "../../messaging/MessageAnalytics.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testAddInteraction() {
    cout << "Testing add message interaction..." << endl;
    MessageAnalytics analytics;
    
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("bob", "charlie");
    analytics.addMessageInteraction("alice", "charlie");
    
    // Verify interactions were added
    assert(analytics.getInteractionCount("alice", "bob") == 1);
    assert(analytics.getInteractionCount("bob", "charlie") == 1);
    assert(analytics.getInteractionCount("alice", "charlie") == 1);
    
    cout << " Add interaction tests passed!" << endl;
}

void testMultipleInteractions() {
    cout << "Testing multiple interactions between same users..." << endl;
    MessageAnalytics analytics;
    
    // Multiple interactions between alice and bob
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("alice", "bob");
    
    // Bidirectional - both should have same count
    assert(analytics.getInteractionCount("alice", "bob") == 3);
    assert(analytics.getInteractionCount("bob", "alice") == 3);
    
    cout << " Multiple interactions tests passed!" << endl;
}

void testGetMostActiveUsers() {
    cout << "Testing getMostActiveUsers..." << endl;
    MessageAnalytics analytics;
    
    // Create a network
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("alice", "charlie");
    analytics.addMessageInteraction("alice", "david");
    analytics.addMessageInteraction("bob", "charlie");
    analytics.addMessageInteraction("eve", "frank");
    
    // Get top 3 most active users
    DynamicArray<string> top3 = analytics.getMostActiveUsers(3);
    assert(top3.size() == 3);
    
    // Alice should be most active (3 connections)
    assert(top3.get(0) == "alice");
    
    cout << " Get most active users tests passed!" << endl;
}

void testNonExistentUsers() {
    cout << "Testing non-existent user interactions..." << endl;
    MessageAnalytics analytics;
    
    analytics.addMessageInteraction("alice", "bob");
    
    // Query non-existent users
    assert(analytics.getInteractionCount("alice", "nonexistent") == 0);
    assert(analytics.getInteractionCount("user1", "user2") == 0);
    
    cout << " Non-existent users tests passed!" << endl;
}

void testEmptyAnalytics() {
    cout << "Testing empty analytics..." << endl;
    MessageAnalytics analytics;
    
    DynamicArray<string> topUsers = analytics.getMostActiveUsers(5);
    assert(topUsers.size() == 0);
    
    assert(analytics.getInteractionCount("anyone", "anyone") == 0);
    
    cout << " Empty analytics tests passed!" << endl;
}

void testComplexNetwork() {
    cout << "Testing complex network..." << endl;
    MessageAnalytics analytics;
    
    // Build a complex interaction network
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("alice", "bob");
    analytics.addMessageInteraction("alice", "charlie");
    analytics.addMessageInteraction("bob", "charlie");
    analytics.addMessageInteraction("charlie", "david");
    analytics.addMessageInteraction("david", "eve");
    analytics.addMessageInteraction("eve", "alice");
    
    // Verify specific interaction counts
    assert(analytics.getInteractionCount("alice", "bob") == 2);
    assert(analytics.getInteractionCount("bob", "charlie") == 1);
    
    // Get top 3 active users
    DynamicArray<string> top3 = analytics.getMostActiveUsers(3);
    assert(top3.size() == 3);
    
    cout << " Complex network tests passed!" << endl;
}

int main() {
    cout << "=== MessageAnalytics Unit Tests ===" << endl;
    
    try {
        testAddInteraction();
        testMultipleInteractions();
        testGetMostActiveUsers();
        testNonExistentUsers();
        testEmptyAnalytics();
        testComplexNetwork();
        
        cout << "\n ALL MESSAGEANALYTICS TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
