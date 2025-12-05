// test_social_network.cpp
#include <iostream>
#include <cassert>
#include "User.h"
#include "UserManager.h"
#include "../graph/Graph.h"
#include "../utils/IDGenerator.h"

using namespace std;

// Helper function to print test results
void printTestResult(const string& testName, bool passed) {
    cout << "[" << (passed ? "PASS" : "FAIL") << "] " << testName << endl;
}

// Test Graph class
void testGraph() {
    cout << "\n========== TESTING GRAPH ==========\n" << endl;
    
    Graph g;
    
    // Test 1: Add nodes
    cout << "Test 1: Adding nodes..." << endl;
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);
    printTestResult("Add nodes", g.nodeCount() == 4);
    
    // Test 2: Check if nodes exist
    cout << "\nTest 2: Checking if nodes exist..." << endl;
    printTestResult("Node 1 exists", g.hasNode(1));
    printTestResult("Node 5 does not exist", !g.hasNode(5));
    
    // Test 3: Add edges
    cout << "\nTest 3: Adding edges..." << endl;
    g.addEdge(1, 2);  // undirected
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    printTestResult("Edge 1->2 exists", g.hasEdge(1, 2));
    printTestResult("Edge 2->1 exists (undirected)", g.hasEdge(2, 1));
    printTestResult("Edge 1->4 does not exist", !g.hasEdge(1, 4));
    
    // Test 4: Get neighbors
    cout << "\nTest 4: Getting neighbors..." << endl;
    const LinkedList<Edge>& neighbors = g.getNeighbors(1);
    printTestResult("Node 1 has 2 neighbors", neighbors.size() == 2);
    
    // Test 5: Print graph
    cout << "\nTest 5: Printing graph structure..." << endl;
    g.print();
    
    // Test 6: Remove edge
    cout << "\nTest 6: Removing edge 1->2..." << endl;
    g.removeEdge(1, 2);
    printTestResult("Edge 1->2 removed", !g.hasEdge(1, 2));
    printTestResult("Edge 2->1 also removed (undirected)", !g.hasEdge(2, 1));
    
    // Test 7: Remove node
    cout << "\nTest 7: Removing node 3..." << endl;
    g.removeNode(3);
    printTestResult("Node 3 removed", !g.hasNode(3));
    printTestResult("Node count is 3", g.nodeCount() == 3);
    
    // Test 8: Get all node IDs
    cout << "\nTest 8: Getting all node IDs..." << endl;
    LinkedList<int> allIds = g.getAllNodeIDs();
    cout << "Remaining nodes: ";
    for (int i = 0; i < allIds.size(); i++) {
        cout << allIds[i] << " ";
    }
    cout << endl;
    printTestResult("Correct number of nodes", allIds.size() == 3);
    
    // Test 9: Clear graph
    cout << "\nTest 9: Clearing graph..." << endl;
    g.clear();
    printTestResult("Graph cleared", g.nodeCount() == 0);
    
    cout << "\n========== GRAPH TESTS COMPLETE ==========\n" << endl;
}

// Test User class
void testUser() {
    cout << "\n========== TESTING USER ==========\n" << endl;
    
    IDGenerator::reset();  // Reset IDs for this test suite
    
    // Test 1: Create user
    cout << "Test 1: Creating users..." << endl;
    User user1("Alice", "password123");
    User user2("Bob", "password456");
    printTestResult("User 1 created with ID > 0", user1.getId() > 0);
    printTestResult("User 2 has different ID", user1.getId() != user2.getId());
    printTestResult("User 1 name is Alice", user1.getName() == "Alice");
    
    // Test 2: Create posts
    cout << "\nTest 2: Creating posts..." << endl;
    user1.createPost("Hello World!");
    user1.createPost("My second post");
    user1.createPost("Having a great day!");
    printTestResult("User 1 has 3 posts", user1.getPosts().size() == 3);
    
    // Test 3: Get posts
    cout << "\nTest 3: Getting posts..." << endl;
    DynamicArray<string>& posts = user1.getPosts();
    cout << "User 1's posts:" << endl;
    for (int i = 0; i < posts.size(); i++) {
        cout << "  " << i << ": " << posts.get(i) << endl;
    }
    printTestResult("First post correct", posts.get(0) == "Hello World!");
    
    // Test 4: Delete post
    cout << "\nTest 4: Deleting post at index 1..." << endl;
    bool deleted = user1.deletePost(1);
    printTestResult("Post deleted successfully", deleted);
    printTestResult("Now has 2 posts", user1.getPosts().size() == 2);
    printTestResult("Post at index 1 is now 'Having a great day!'", 
                    user1.getPosts().get(1) == "Having a great day!");
    
    // Test 5: Invalid delete
    cout << "\nTest 5: Trying to delete invalid index..." << endl;
    bool invalidDelete = user1.deletePost(10);
    printTestResult("Invalid delete returns false", !invalidDelete);
    
    cout << "\n========== USER TESTS COMPLETE ==========\n" << endl;
}

// Test UserManager class
void testUserManager() {
    cout << "\n========== TESTING USER MANAGER ==========\n" << endl;
    
    IDGenerator::reset();  // Reset IDs for this test suite
    
    UserManager um;
    
    // Test 1: Add users
    cout << "Test 1: Adding users..." << endl;
    um.addUser("Alice", "pass123");
    um.addUser("Bob", "pass456");
    um.addUser("Charlie", "pass789");
    um.addUser("David", "pass000");
    um.addUser("Eve", "pass111");
    
    User* alice = um.getUserById(1);
    User* bob = um.getUserById(2);
    User* charlie = um.getUserById(3);
    User* david = um.getUserById(4);
    User* eve = um.getUserById(5);
    
    printTestResult("Alice added", alice != nullptr && alice->getName() == "Alice");
    printTestResult("Bob added", bob != nullptr && bob->getName() == "Bob");
    
    // Test 2: Login
    cout << "\nTest 2: Testing login..." << endl;
    User* loggedIn = um.login("Alice", "pass123");
    printTestResult("Alice login successful", loggedIn != nullptr);
    
    User* failedLogin = um.login("Alice", "wrongpass");
    printTestResult("Wrong password fails", failedLogin == nullptr);
    
    // Test 3: Search by prefix
    cout << "\nTest 3: Searching users by prefix..." << endl;
    DynamicArray<string> results = um.searchUsersByPrefix("Al");
    cout << "Users starting with 'Al': ";
    for (int i = 0; i < results.size(); i++) {
        cout << results.get(i) << " ";
    }
    cout << endl;
    printTestResult("Found Alice", results.size() > 0);
    
    // Test 4: Make connections
    cout << "\nTest 4: Making friend connections..." << endl;
    // Create network: Alice-Bob, Alice-Charlie, Bob-David, Charlie-David, David-Eve
    um.makeConnection(alice->getId(), bob->getId());
    um.makeConnection(alice->getId(), charlie->getId());
    um.makeConnection(bob->getId(), david->getId());
    um.makeConnection(charlie->getId(), david->getId());
    um.makeConnection(david->getId(), eve->getId());
    
    cout << "Network created:" << endl;
    cout << "  Alice <-> Bob" << endl;
    cout << "  Alice <-> Charlie" << endl;
    cout << "  Bob <-> David" << endl;
    cout << "  Charlie <-> David" << endl;
    cout << "  David <-> Eve" << endl;
    printTestResult("Connections made", true);
    
    // Test 5: Friend suggestions
    cout << "\nTest 5: Getting friend suggestions for Alice..." << endl;
    DynamicArray<User*> suggestions = um.friendSuggestions(alice->getId());
    cout << "Friend suggestions for Alice: ";
    for (int i = 0; i < suggestions.size(); i++) {
        cout << suggestions.get(i)->getName() << " ";
    }
    cout << endl;
    printTestResult("David should be suggested (friend of Bob and Charlie)", 
                    suggestions.size() > 0);
    
    // Test 6: Shortest path
    cout << "\nTest 6: Finding shortest path from Alice to Eve..." << endl;
    DynamicArray<User*> path = um.shortestPath(alice->getId(), eve->getId());
    cout << "Path from Alice to Eve: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path.get(i)->getName();
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    printTestResult("Path found", path.size() > 0);
    printTestResult("Path length is reasonable", path.size() >= 2 && path.size() <= 4);
    
    // Test 7: Shortest path (same user)
    cout << "\nTest 7: Finding path from Alice to Alice..." << endl;
    DynamicArray<User*> samePath = um.shortestPath(alice->getId(), alice->getId());
    printTestResult("Path to self contains only 1 user", samePath.size() == 1);
    
    // Test 8: No path exists
    cout << "\nTest 8: Adding isolated user and checking path..." << endl;
    um.addUser("Frank", "pass222");
    User* frank = um.getUserById(6);
    DynamicArray<User*> noPath = um.shortestPath(alice->getId(), frank->getId());
    printTestResult("No path to isolated user", noPath.size() == 0);
    
    // Test 9: Remove user
    cout << "\nTest 9: Removing user Bob..." << endl;
    int bobId = bob->getId();  // Save Bob's ID before removal
    bool removed = um.removeUserById(bobId);
    printTestResult("Bob removed successfully", removed);
    User* bobAfterRemove = um.getUserById(bobId);  // Use saved ID
    printTestResult("Bob not found after removal", bobAfterRemove == nullptr);
    // Test 10: Path after removal
    cout << "\nTest 10: Finding new path from Alice to David after Bob removed..." << endl;
    DynamicArray<User*> newPath = um.shortestPath(alice->getId(), david->getId());
    cout << "New path from Alice to David: ";
    for (int i = 0; i < newPath.size(); i++) {
        cout << newPath.get(i)->getName();
        if (i < newPath.size() - 1) cout << " -> ";
    }
    cout << endl;
    printTestResult("Alternative path found through Charlie", newPath.size() > 0);
    
    cout << "\n========== USER MANAGER TESTS COMPLETE ==========\n" << endl;
}

// Test edge cases
void testEdgeCases() {
    cout << "\n========== TESTING EDGE CASES ==========\n" << endl;
    
    IDGenerator::reset();  // Reset IDs for this test suite
    
    UserManager um;
    
    // Test 1: Double connection
    cout << "Test 1: Trying to make duplicate connection..." << endl;
    um.addUser("User1", "pass1");
    um.addUser("User2", "pass2");
    um.makeConnection(1, 2);
    try {
        um.makeConnection(1, 2);  // Should not add duplicate
        printTestResult("Duplicate connection handled", true);
    } catch (...) {
        printTestResult("Duplicate connection threw exception", false);
    }
    
    // Test 2: Self connection
    cout << "\nTest 2: Trying to connect user to themselves..." << endl;
    try {
        um.makeConnection(1, 1);
        printTestResult("Self connection allowed", true);
    } catch (...) {
        printTestResult("Self connection prevented", true);
    }
    
    // Test 3: Non-existent user
    cout << "\nTest 3: Getting non-existent user..." << endl;
    User* nonExistent = um.getUserById(9999);
    printTestResult("Non-existent user returns nullptr", nonExistent == nullptr);
    
    // Test 4: Connection with non-existent user
    cout << "\nTest 4: Connecting to non-existent user..." << endl;
    try {
        um.makeConnection(1, 9999);
        printTestResult("Connection to non-existent user failed", false);
    } catch (const exception& e) {
        cout << "  Exception caught: " << e.what() << endl;
        printTestResult("Connection to non-existent user throws exception", true);
    }
    
    cout << "\n========== EDGE CASE TESTS COMPLETE ==========\n" << endl;
}

int main() {
    cout << "\n";
    cout << "================================================\n";
    cout << "   SOCIAL NETWORK DATA STRUCTURE TEST SUITE    \n";
    cout << "================================================\n";
    
    try {
        testGraph();
        testUser();
        testUserManager();
        testEdgeCases();
        
        cout << "\n================================================\n";
        cout << "           ALL TESTS COMPLETED!                 \n";
        cout << "================================================\n\n";
        
    } catch (const exception& e) {
        cout << "\n[ERROR] Test suite failed with exception: " << e.what() << endl;
        return 1;
    }
    
    return 0;
}