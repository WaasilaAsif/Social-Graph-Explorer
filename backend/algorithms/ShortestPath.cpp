#include "ShortestPath.h"

ShortestPath::ShortestPath(Graph* g) : graph(g) {}

LinkedList<int> ShortestPath::reconstructPath(
    const HashMap<int, int>& parent,
    int start,
    int end
) {
    LinkedList<int> path;
    int current = end;
    
    while (current != start) {
        path.append(current);
        current = parent.get(current);
    }
    path.append(start);
    
    // Reverse the path
    LinkedList<int> reversedPath;
    for (int i = path.size() - 1; i >= 0; i--) {
        reversedPath.append(path[i]);
    }
    
    return reversedPath;
}

LinkedList<int> ShortestPath::findPath(int startUserId, int endUserId) {
    Queue<int> queue;
    HashMap<int, bool> visited;
    HashMap<int, int> parent;
    
    queue.enqueue(startUserId);
    visited.put(startUserId, true);
    
    while (!queue.isEmpty()) {
        int current = queue.dequeue();
        
        if (current == endUserId) {
            return reconstructPath(parent, startUserId, endUserId);
        }
        
        LinkedList<Edge>& neighbors = graph->getNeighbors(current);
        for (int i = 0; i < neighbors.size(); i++) {
            int neighbor = neighbors[i].to;
            if (!visited.contains(neighbor)) {
                visited.put(neighbor, true);
                parent.put(neighbor, current);
                queue.enqueue(neighbor);
            }
        }
    }
    
    return LinkedList<int>(); // Empty path if not found
}

int ShortestPath::getDistance(int startUserId, int endUserId) {
    LinkedList<int> path = findPath(startUserId, endUserId);
    return path.size() > 0 ? path.size() - 1 : -1;
}

bool ShortestPath::pathExists(int startUserId, int endUserId) {
    return getDistance(startUserId, endUserId) != -1;
}

LinkedList<int> ShortestPath::getUsersWithinDistance(int userId, int maxDistance) {
    LinkedList<int> result;
    Queue<int> queue;
    HashMap<int, int> distance;
    
    queue.enqueue(userId);
    distance.put(userId, 0);
    
    while (!queue.isEmpty()) {
        int current = queue.dequeue();
        int currentDist = distance.get(current);
        
        if (currentDist < maxDistance) {
            LinkedList<Edge>& neighbors = graph->getNeighbors(current);
            for (int i = 0; i < neighbors.size(); i++) {
                int neighbor = neighbors[i].to;
                if (!distance.contains(neighbor)) {
                    distance.put(neighbor, currentDist + 1);
                    queue.enqueue(neighbor);
                    result.append(neighbor);
                }
            }
        }
    }
    
    return result;
}