#ifndef SHORTESTPATH_H
#define SHORTESTPATH_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/Queue.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/LinkedList.h"

class ShortestPath {
private:
    Graph* graph;
    
    // Helper function to reconstruct path
    LinkedList<int> reconstructPath(
        const HashMap<int, int>& parent,
        int start,
        int end
    );

public:
    ShortestPath(Graph* g);
    
    // Find shortest path between two users
    LinkedList<int> findPath(int startUserId, int endUserId);
    
    // Get distance (number of hops) between two users
    int getDistance(int startUserId, int endUserId);
    
    // Check if path exists
    bool pathExists(int startUserId, int endUserId);
    
    // Get all users within N hops
    LinkedList<int> getUsersWithinDistance(int userId, int maxDistance);
};

#endif // SHORTESTPATH_H