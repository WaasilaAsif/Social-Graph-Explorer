// full_integration.cpp
// Complete example showing how all Member 2 components work together
// Simulates a real social network scenario
#include "../../dsa/graph/Graph.h"
#include "../../algorithms/BFS.h"
#include "../../algorithms/DFS.h"
#include "../../algorithms/GraphLayout.h"
#include "../../algorithms/Graphstats.h"
#include <iostream>
#include <iomanip>

using namespace std;

// ========== SCENARIO: Building a Social Network ==========

class SocialNetworkDemo {
private:
    Graph friendshipGraph;
    
    // User ID to name mapping (for demo purposes)
    HashMap<int, string> userNames;
    
public:
    SocialNetworkDemo() : userNames(50) {}
    
    // Initialize demo network
    void setupDemoNetwork() {
        cout << "\n=== Setting Up Demo Social Network ===\n\n";
        
        // Add users (nodes)
        addUser(1, "Alice");
        addUser(2, "Bob");
        addUser(3, "Charlie");
        addUser(4, "Diana");
        addUser(5, "Eve");
        addUser(6, "Frank");
        addUser(7, "Grace");
        addUser(8, "Henry");
        addUser(9, "Ivy");
        addUser(10, "Jack");
        
        // Add friendships (edges)
        addFriendship(1, 2);  // Alice <-> Bob
        addFriendship(1, 3);  // Alice <-> Charlie
        addFriendship(2, 3);  // Bob <-> Charlie (triangle!)
        addFriendship(2, 4);  // Bob <-> Diana
        addFriendship(3, 5);  // Charlie <-> Eve
        addFriendship(4, 5);  // Diana <-> Eve
        addFriendship(5, 6);  // Eve <-> Frank
        addFriendship(6, 7);  // Frank <-> Grace
        addFriendship(7, 8);  // Grace <-> Henry
        addFriendship(8, 9);  // Henry <-> Ivy
        addFriendship(9, 10); // Ivy <-> Jack
        
        cout << "Network setup complete!\n";
        cout << "Created " << friendshipGraph.nodeCount() << " users\n";
        cout << "Formed " << GraphStats::countEdges(friendshipGraph, true) << " friendships\n\n";
    }
    
    void addUser(int id, const string& name) {
        friendshipGraph.addNode(id);
        userNames.put(id, name);
        cout << "  Added user: " << name << " (ID: " << id << ")\n";
    }
    
    void addFriendship(int user1, int user2) {
        friendshipGraph.addEdge(user1, user2);
        cout << "  " << userNames.get(user1) << " <-> " << userNames.get(user2) << "\n";
    }
    
    // Demo 1: Network Analysis
    void demoNetworkAnalysis() {
        cout << "\n========== DEMO 1: Network Analysis ==========\n\n";
        
        // Basic stats
        cout << "--- Basic Statistics ---\n";
        cout << "Total users: " << friendshipGraph.nodeCount() << "\n";
        cout << "Total friendships: " << GraphStats::countEdges(friendshipGraph, true) << "\n";
        cout << "Average friends per user: " << fixed << setprecision(2) 
             << GraphStats::getAverageDegree(friendshipGraph) << "\n";
        cout << "Network density: " << GraphStats::getDensity(friendshipGraph) << "\n\n";
        
        // Connection analysis
        cout << "--- Connection Analysis ---\n";
        cout << "Network is " << (GraphStats::isConnected(friendshipGraph) ? "connected" : "disconnected") << "\n";
        cout << "Number of communities: " << GraphStats::countComponents(friendshipGraph) << "\n";
        cout << "Network diameter: " << GraphStats::getDiameter(friendshipGraph) << " degrees\n\n";
        
        // Clustering
        cout << "--- Clustering Analysis ---\n";
        cout << "Average clustering coefficient: " 
             << GraphStats::getAverageClusteringCoefficient(friendshipGraph) << "\n\n";
        
        // Most popular user
        int popularID = GraphStats::findMostConnectedNode(friendshipGraph);
        cout << "Most connected user: " << userNames.get(popularID) 
             << " with " << GraphStats::getDegree(friendshipGraph, popularID) << " friends\n\n";
        
        // Individual user stats
        cout << "--- Individual User Friend Counts ---\n";
        LinkedList<int> allUsers = friendshipGraph.getAllNodeIDs();
        for (int i = 0; i < allUsers.size(); ++i) {
            int userID = allUsers[i];
            int friendCount = GraphStats::getDegree(friendshipGraph, userID);
            cout << "  " << setw(10) << left << userNames.get(userID) 
                 << " : " << friendCount << " friends\n";
        }
        cout << "\n";
    }
    
    // Demo 2: Pathfinding and Connections
    void demoPathfinding() {
        cout << "\n========== DEMO 2: Pathfinding & Connections ==========\n\n";
        
        // Example 1: Close friends
        cout << "--- Example 1: Alice to Bob ---\n";
        findConnection(1, 2);
        
        // Example 2: Distant connection
        cout << "\n--- Example 2: Alice to Jack ---\n";
        findConnection(1, 10);
        
        // Example 3: Medium distance
        cout << "\n--- Example 3: Bob to Henry ---\n";
        findConnection(2, 8);
    }
    
    void findConnection(int fromID, int toID) {
        string fromName = userNames.get(fromID);
        string toName = userNames.get(toID);
        
        // Check if path exists
        bool pathExists = BFS::existsPath(friendshipGraph, fromID, toID);
        cout << "Connection from " << fromName << " to " << toName << ": ";
        
        if (!pathExists) {
            cout << "NOT CONNECTED\n";
            return;
        }
        
        cout << "CONNECTED\n";
        
        // Get distance
        int distance = BFS::distance(friendshipGraph, fromID, toID);
        cout << "Degrees of separation: " << distance << "\n";
        
        // Get path
        LinkedList<int> path = BFS::shortestPath(friendshipGraph, fromID, toID);
        cout << "Connection path: ";
        for (int i = 0; i < path.size(); ++i) {
            cout << userNames.get(path[i]);
            if (i < path.size() - 1)
                cout << " -> ";
        }
        cout << "\n";
    }
    
    // Demo 3: Network Traversal
    void demoTraversal() {
        cout << "\n========== DEMO 3: Network Traversal ==========\n\n";
        
        int startID = 1; // Alice
        
        // BFS Traversal
        cout << "--- BFS Traversal (Level by Level) from " << userNames.get(startID) << " ---\n";
        LinkedList<int> bfsOrder = BFS::traverse(friendshipGraph, startID);
        cout << "Visit order: ";
        for (int i = 0; i < bfsOrder.size(); ++i) {
            cout << userNames.get(bfsOrder[i]);
            if (i < bfsOrder.size() - 1)
                cout << " -> ";
        }
        cout << "\n\n";
        
        // DFS Traversal
        cout << "--- DFS Traversal (Depth First) from " << userNames.get(startID) << " ---\n";
        LinkedList<int> dfsOrder = DFS::traverse(friendshipGraph, startID);
        cout << "Visit order: ";
        for (int i = 0; i < dfsOrder.size(); ++i) {
            cout << userNames.get(dfsOrder[i]);
            if (i < dfsOrder.size() - 1)
                cout << " -> ";
        }
        cout << "\n\n";
        
        // Compare
        cout << "Notice the difference:\n";
        cout << "  BFS explores by friendship level (friends, friends-of-friends, etc.)\n";
        cout << "  DFS explores deeply through one connection chain before backtracking\n\n";
    }
    
    // Demo 4: Graph Visualization Setup
    void demoVisualization() {
        cout << "\n========== DEMO 4: Graph Visualization Setup ==========\n\n";
        
        // Generate different layouts
        cout << "--- Layer-Based Layout ---\n";
        HashMap<int, Vector2> layerLayout = GraphLayout::generateLayout(friendshipGraph);
        GraphLayout::centerLayout(layerLayout);
        printLayout(layerLayout);
        
        cout << "\n--- Circular Layout ---\n";
        HashMap<int, Vector2> circularLayout = GraphLayout::generateCircularLayout(friendshipGraph, 200.0f);
        GraphLayout::centerLayout(circularLayout);
        printLayout(circularLayout);
        
        cout << "\n--- Force-Directed Layout ---\n";
        HashMap<int, Vector2> forceLayout = GraphLayout::generateForceDirectedLayout(friendshipGraph, 30);
        GraphLayout::centerLayout(forceLayout);
        printLayout(forceLayout);
    }
    
    void printLayout(const HashMap<int, Vector2>& positions) {
        LinkedList<int> allUsers = friendshipGraph.getAllNodeIDs();
        
        // Print first 5 users as example
        cout << "Sample positions (for visualization):\n";
        int limit = (allUsers.size() < 5) ? allUsers.size() : 5;
        for (int i = 0; i < limit; ++i) {
            int userID = allUsers[i];
            Vector2 pos = positions.get(userID);
            cout << "  " << setw(10) << left << userNames.get(userID)
                 << " : (" << fixed << setprecision(1) 
                 << setw(7) << pos.x << ", " << setw(7) << pos.y << ")\n";
        }
    }
    
    // Demo 5: Friend Network Exploration
    void demoFriendNetwork() {
        cout << "\n========== DEMO 5: Friend Network Exploration ==========\n\n";
        
        int userID = 2; // Bob
        cout << "Exploring " << userNames.get(userID) << "'s friend network:\n\n";
        
        // Direct friends
        cout << "--- Direct Friends ---\n";
        const LinkedList<Edge>& friends = friendshipGraph.getNeighbors(userID);
        cout << userNames.get(userID) << " has " << friends.size() << " direct friends:\n";
        for (int i = 0; i < friends.size(); ++i) {
            cout << "  - " << userNames.get(friends[i].to) << "\n";
        }
        
        // Friends of friends
        cout << "\n--- Friends of Friends ---\n";
        HashMap<int, bool> fofMap(50);
        fofMap.put(userID, true); // Exclude self
        
        for (int i = 0; i < friends.size(); ++i) {
            int friendID = friends[i].to;
            fofMap.put(friendID, true); // Exclude direct friends
            
            const LinkedList<Edge>& friendsOfFriend = friendshipGraph.getNeighbors(friendID);
            for (int j = 0; j < friendsOfFriend.size(); ++j) {
                int fofID = friendsOfFriend[j].to;
                if (!fofMap.contains(fofID)) {
                    cout << "  - " << userNames.get(fofID) 
                         << " (through " << userNames.get(friendID) << ")\n";
                    fofMap.put(fofID, true);
                }
            }
        }
        cout << "\n";
    }
    
    // Demo 6: Community Detection (Simple)
    void demoCommunityDetection() {
        cout << "\n========== DEMO 6: Community Detection ==========\n\n";
        
        // Detect cycles (indicates tight communities)
        bool hasCycles = DFS::hasCycle(friendshipGraph);
        cout << "Network has cycles (tight friend groups): " 
             << (hasCycles ? "YES" : "NO") << "\n\n";
        
        // Find highly clustered users
        cout << "--- Users with High Clustering (Close-Knit Groups) ---\n";
        LinkedList<int> allUsers = friendshipGraph.getAllNodeIDs();
        
        for (int i = 0; i < allUsers.size(); ++i) {
            int userID = allUsers[i];
            float clustering = GraphStats::getClusteringCoefficient(friendshipGraph, userID);
            if (clustering > 0.3f) {  // Threshold
                cout << "  " << setw(10) << left << userNames.get(userID)
                     << " : " << fixed << setprecision(2) << clustering 
                     << " (part of tight group)\n";
            }
        }
        cout << "\n";
    }
    
    // Run all demos
    void runAllDemos() {
        setupDemoNetwork();
        demoNetworkAnalysis();
        demoPathfinding();
        demoTraversal();
        demoVisualization();
        demoFriendNetwork();
        demoCommunityDetection();
        
        cout << "\n========== All Demos Complete! ==========\n\n";
    }
};

// ========== MAIN FUNCTION ==========

int main() {
    cout << "\n";
    cout << "=========================================================\n";
    cout << "||      Social Network Graph - Integration Demo        ||\n";
    cout << "||             Member 2: Graph Engineer                ||\n";
    cout << "=========================================================\n";
    
    SocialNetworkDemo demo;
    demo.runAllDemos();
    
    cout << "This demo showcases:\n";
    cout << "   Graph data structure\n";
    cout << "   BFS & DFS algorithms\n";
    cout << "   Pathfinding algorithms\n";
    cout << "   Graph statistics & analytics\n";
    cout << "   Graph layout for visualization\n";
    cout << "   Network analysis features\n";
    cout << "\nAll components working together! \n\n";
    
    return 0;
}

/*
 * EXPECTED OUTPUT SUMMARY:
 * 
 * 1. Network Setup
 *    - 10 users added
 *    - 11 friendships formed
 * 
 * 2. Network Analysis
 *    - Average 2.2 friends per user
 *    - Network is connected
 *    - Diameter of 9 degrees
 *    - Multiple users with 2-3 friends
 * 
 * 3. Pathfinding
 *    - Alice to Bob: 1 degree (direct friends)
 *    - Alice to Jack: 9 degrees (longest path)
 *    - Shows connection paths
 * 
 * 4. Traversal
 *    - BFS and DFS show different visit orders
 *    - Demonstrates algorithm differences
 * 
 * 5. Visualization
 *    - Three different layout algorithms
 *    - Coordinates for rendering graph
 * 
 * 6. Friend Network
 *    - Direct friends list
 *    - Friends-of-friends (potential connections)
 * 
 * 7. Community Detection
 *    - Identifies tight friend groups
 *    - Shows clustering coefficients
 */

/*
 * COMPILATION INSTRUCTIONS:
 * 
 * g++ -std=c++11 full_integration_example.cpp -o social_network_demo
 * ./social_network_demo
 * 
 * Make sure all header files are in correct locations:
 * - Graph.h, Node.h, Edge.h in ../backend/dsa/graph/
 * - LinkedList.h, HashMap.h, Queue.h, Stack.h in ../backend/dsa/containers/
 * - BFS.h, DFS.h, GraphLayout.h in ../backend/algorithms/
 * - GraphStats.h in ../backend/analytics/
 * - Vector2.h in ../backend/dsa/utils/
 */