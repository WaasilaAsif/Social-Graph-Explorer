#include <iostream>
#include <cassert>
#include "../../algorithms/MutualFriends.h"
#include "../../algorithms/ShortestPath.h"
#include "../../analytics/PopularityRanker.h"

using namespace std;

void testMutualFriends() {
    cout << "\n=== Testing Mutual Friends Algorithm ===" << endl;
    cout << "Expected Complexity: O(d1 + d2) where d = degree\n" << endl;
    
    // Test Case 1: Users with mutual friends
    cout << "Test 1: Users with mutual friends" << endl;
    Graph g1;
    // Add nodes first
    g1.addNode(1); g1.addNode(2); g1.addNode(3); 
    g1.addNode(4); g1.addNode(5); g1.addNode(6);
    // Then add edges
    g1.addEdge(1, 3); g1.addEdge(1, 4); g1.addEdge(1, 5);
    g1.addEdge(2, 3); g1.addEdge(2, 4); g1.addEdge(2, 6);
    
    MutualFriends mf1(&g1);
    LinkedList<int> mutuals = mf1.getMutualFriends(1, 2);
    
    cout << "  User 1 friends: 3, 4, 5" << endl;
    cout << "  User 2 friends: 3, 4, 6" << endl;
    cout << "  Mutual friends found: " << mutuals.size() << endl;
    cout << "  Expected: 2 (users 3 and 4)" << endl;
    assert(mutuals.size() == 2);
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 2: Users with no mutual friends
    cout << "Test 2: Users with NO mutual friends" << endl;
    Graph g2;
    g2.addNode(1); g2.addNode(2); g2.addNode(3); 
    g2.addNode(4); g2.addNode(5); g2.addNode(6);
    g2.addEdge(1, 3); g2.addEdge(1, 4);
    g2.addEdge(2, 5); g2.addEdge(2, 6);
    
    MutualFriends mf2(&g2);
    mutuals = mf2.getMutualFriends(1, 2);
    
    cout << "  User 1 friends: 3, 4" << endl;
    cout << "  User 2 friends: 5, 6" << endl;
    cout << "  Mutual friends found: " << mutuals.size() << endl;
    cout << "  Expected: 0" << endl;
    assert(mutuals.size() == 0);
    assert(mf2.hasMutualFriends(1, 2) == false);
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 3: One user has no friends
    cout << "Test 3: One user has no friends" << endl;
    Graph g3;
    g3.addNode(1); g3.addNode(2); g3.addNode(3); g3.addNode(4);
    g3.addEdge(1, 3); g3.addEdge(1, 4);
    // User 2 exists but has no friends
    
    MutualFriends mf3(&g3);
    int count = mf3.getMutualFriendsCount(1, 2);
    
    cout << "  User 1 friends: 3, 4" << endl;
    cout << "  User 2 friends: none" << endl;
    cout << "  Mutual friends count: " << count << endl;
    cout << "  Expected: 0" << endl;
    assert(count == 0);
    cout << "  ✓ PASSED\n" << endl;
    
    cout << "[x]
 All Mutual Friends tests passed!" << endl;
}

void testShortestPath() {
    cout << "\n=== Testing Shortest Path Algorithm ===" << endl;
    cout << "Expected Complexity: O(V + E) - BFS\n" << endl;
    
    // Test Case 1: Path exists
    cout << "Test 1: Finding path in connected graph" << endl;
    Graph g1;
    // Add nodes first
    g1.addNode(1); g1.addNode(2); g1.addNode(3); g1.addNode(4); g1.addNode(5);
    // Create path: 1-2-3-4-5
    g1.addEdge(1, 2); 
    g1.addEdge(2, 3); 
    g1.addEdge(3, 4);
    g1.addEdge(4, 5);
    
    ShortestPath sp1(&g1);
    LinkedList<int> path = sp1.findPath(1, 5);
    int distance = sp1.getDistance(1, 5);
    
    cout << "  Graph: 1-2-3-4-5 (linear)" << endl;
    cout << "  Path from 1 to 5: ";
    for (int i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << endl;
    cout << "  Path length: " << path.size() << " nodes" << endl;
    cout << "  Distance (hops): " << distance << endl;
    cout << "  Expected: 5 nodes, 4 hops" << endl;
    assert(path.size() == 5);
    assert(distance == 4);
    assert(sp1.pathExists(1, 5) == true);
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 2: No path exists
    cout << "Test 2: Disconnected components" << endl;
    Graph g2;
    g2.addNode(1); g2.addNode(2); g2.addNode(3); g2.addNode(4);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4); // Separate component
    
    ShortestPath sp2(&g2);
    path = sp2.findPath(1, 4);
    distance = sp2.getDistance(1, 4);
    
    cout << "  Graph: {1-2} and {3-4} (disconnected)" << endl;
    cout << "  Path from 1 to 4: " << (path.size() == 0 ? "none" : "found") << endl;
    cout << "  Distance: " << distance << endl;
    cout << "  Expected: no path, distance = -1" << endl;
    assert(path.size() == 0);
    assert(distance == -1);
    assert(sp2.pathExists(1, 4) == false);
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 3: Multiple paths - BFS finds shortest
    cout << "Test 3: Multiple paths (BFS finds shortest)" << endl;
    Graph g3;
    g3.addNode(1); g3.addNode(2); g3.addNode(3); g3.addNode(4);
    // Create diamond: 1->2->4 and 1->3->4
    //                 1->4 (direct)
    g3.addEdge(1, 2);
    g3.addEdge(2, 4);
    g3.addEdge(1, 3);
    g3.addEdge(3, 4);
    g3.addEdge(1, 4); // Direct path
    
    ShortestPath sp3(&g3);
    path = sp3.findPath(1, 4);
    distance = sp3.getDistance(1, 4);
    
    cout << "  Graph: Diamond with direct edge 1->4" << endl;
    cout << "  Distance from 1 to 4: " << distance << endl;
    cout << "  Expected: 1 (shortest path)" << endl;
    assert(distance == 1);
    cout << "  ✓ PASSED\n" << endl;
    
    cout << "[x]
 All Shortest Path tests passed!" << endl;
}

void testPopularityRanker() {
    cout << "\n=== Testing Popularity Ranker Algorithm ===" << endl;
    cout << "Expected Complexity: O(V log V) - Heap operations\n" << endl;
    
    // Test Case 1: Clear ranking
    cout << "Test 1: Ranking users by friend count" << endl;
    Graph g1;
    // Add all nodes
    g1.addNode(1); g1.addNode(2); g1.addNode(3); 
    g1.addNode(4); g1.addNode(5);
    // User 1: 4 friends
    g1.addEdge(1, 2); g1.addEdge(1, 3); g1.addEdge(1, 4); g1.addEdge(1, 5);
    // User 2: 2 friends
    g1.addEdge(2, 1); g1.addEdge(2, 3);
    // User 3: 3 friends
    g1.addEdge(3, 1); g1.addEdge(3, 2); g1.addEdge(3, 4);
    // User 4: 1 friend
    g1.addEdge(4, 1);
    
    PopularityRanker pr1(&g1);
    LinkedList<UserScore> top3 = pr1.getTopNPopularUsers(3);
    
    cout << "  Top 3 users:" << endl;
    for (int i = 0; i < top3.size() && i < 3; i++) {
        cout << "    #" << (i+1) << ": User " << top3[i].userId 
             << " (score: " << top3[i].score << ")" << endl;
    }
    
    assert(top3.size() == 3);
    assert(top3[0].userId == 1); // Most popular
    assert(top3[0].score == 4);
    cout << "  Expected: User 1 is most popular with score 4" << endl;
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 2: User rank
    cout << "Test 2: Getting specific user rank" << endl;
    int rank1 = pr1.getUserRank(1);
    int rank2 = pr1.getUserRank(2);
    int rank4 = pr1.getUserRank(4);
    
    cout << "  User 1 rank: " << rank1 << " (expected: 1)" << endl;
    cout << "  User 2 rank: " << rank2 << " (expected: 3)" << endl;
    cout << "  User 4 rank: " << rank4 << " (expected: 4)" << endl;
    
    assert(rank1 == 1);
    assert(rank4 > rank1); // Less popular user has higher rank number
    cout << "  ✓ PASSED\n" << endl;
    
    // Test Case 3: Percentile rank
    cout << "Test 3: Percentile ranking" << endl;
    double percentile1 = pr1.getPercentileRank(1);
    double percentile4 = pr1.getPercentileRank(4);
    
    cout << "  User 1 percentile: " << percentile1 << "%" << endl;
    cout << "  User 4 percentile: " << percentile4 << "%" << endl;
    cout << "  Expected: User 1 > User 4 percentile" << endl;
    
    assert(percentile1 > percentile4); // More popular = higher percentile
    assert(percentile1 >= 75.0); // Should be in top quartile
    cout << "  ✓ PASSED\n" << endl;
    
    cout << "[x]
 All Popularity Ranker tests passed!" << endl;
}

int main() {
    cout << "========================================" << endl;
    cout << "  ALGORITHM VALIDATION TEST SUITE" << endl;
    cout << "========================================" << endl;
    
    try {
        testMutualFriends();
        testShortestPath();
        testPopularityRanker();
        
        cout << "\n========================================" << endl;
        cout << "  [x]
 ALL TESTS PASSED SUCCESSFULLY!" << endl;
        cout << "========================================" << endl;
        cout << "\nAll algorithms validated with 3+ test cases each." << endl;
        cout << "Ready for benchmarking phase." << endl;
        
        return 0;
    } catch (const exception& e) {
        cout << "\nX
 TEST FAILED: " << e.what() << endl;
        return 1;
    } catch (...) {
        cout << "\nX
 TEST FAILED: Unknown error" << endl;
        return 1;
    }
}