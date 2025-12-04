#include "MsgShortestPath.h"

MsgShortestPath::MsgShortestPath(ConversationGraph* graph)
    : convGraph(graph) {}

DynamicArray<int> MsgShortestPath::findShortestPath(int srcId, int destId) {
    DynamicArray<int> path;
    
    if (!convGraph->userExists(srcId) || !convGraph->userExists(destId)) {
        return path;
    }
    
    if (srcId == destId) {
        path.push_back(srcId);
        return path;
    }
    
    // BFS to find shortest path
    Queue<int> q;
    HashMap<int, bool> visited;
    HashMap<int, int> parent; // Track parent for path reconstruction
    
    q.enqueue(srcId);
    visited.put(srcId, true);
    parent.put(srcId, -1);
    
    bool found = false;
    
    while (!q.isEmpty()) {
        int current = q.dequeue();
        
        if (current == destId) {
            found = true;
            break;
        }
        
        DynamicArray<int> neighbors = convGraph->getNeighbors(current);
        
        for (int i = 0; i < neighbors.size(); i++) {
            int neighbor = neighbors.get(i);
            
            if (!visited.contains(neighbor)) {
                visited.put(neighbor, true);
                parent.put(neighbor, current);
                q.enqueue(neighbor);
            }
        }
    }
    
    if (!found) {
        return path; // No path found
    }
    
    // Reconstruct path from dest to src
    DynamicArray<int> reversePath;
    int current = destId;
    
    while (current != -1) {
        reversePath.push_back(current);
        current = parent.get(current);
    }
    
    // Reverse the path
    for (int i = reversePath.size() - 1; i >= 0; i--) {
        path.push_back(reversePath.get(i));
    }
    
    return path;
}
