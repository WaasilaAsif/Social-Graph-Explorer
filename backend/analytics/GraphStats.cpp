#include "GraphStats.h"
#include "../dsa/containers/Queue.h"

GraphStats::GraphStats(Graph* g) : graph(g) {}

int GraphStats::getTotalUsers() {
    return graph->nodeCount();
}

int GraphStats::getTotalFriendships() {
    int totalEdges = 0;
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    for (int i = 0; i < allUsers.size(); i++) {
        totalEdges += graph->getNeighbors(allUsers[i]).size();
    }
    
    // Divide by 2 because edges are counted twice (undirected graph)
    return totalEdges / 2;
}

double GraphStats::getAverageDegree() {
    int totalUsers = getTotalUsers();
    if (totalUsers == 0) return 0.0;
    
    int totalDegree = 0;
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    for (int i = 0; i < allUsers.size(); i++) {
        totalDegree += getUserDegree(allUsers[i]);
    }
    
    return static_cast<double>(totalDegree) / totalUsers;
}

int GraphStats::getUserDegree(int userId) {
    return graph->getNeighbors(userId).size();
}

int GraphStats::getMostPopularUser() {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    if (allUsers.isEmpty()) return -1;
    
    int mostPopular = allUsers[0];
    int maxDegree = getUserDegree(mostPopular);
    
    for (int i = 1; i < allUsers.size(); i++) {
        int degree = getUserDegree(allUsers[i]);
        if (degree > maxDegree) {
            maxDegree = degree;
            mostPopular = allUsers[i];
        }
    }
    
    return mostPopular;
}

LinkedList<int> GraphStats::getTopNPopularUsers(int n) {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    // Create array of (userId, degree) pairs
    LinkedList<int> userDegrees;
    for (int i = 0; i < allUsers.size(); i++) {
        userDegrees.append(allUsers[i]);
    }
    
    // Simple selection sort to get top N
    LinkedList<int> topUsers;
    int count = (n < allUsers.size()) ? n : allUsers.size();
    
    for (int i = 0; i < count; i++) {
        int maxIdx = i;
        int maxDegree = getUserDegree(userDegrees[i]);
        
        for (int j = i + 1; j < userDegrees.size(); j++) {
            int degree = getUserDegree(userDegrees[j]);
            if (degree > maxDegree) {
                maxDegree = degree;
                maxIdx = j;
            }
        }
        
        // Swap
        int temp = userDegrees[i];
        userDegrees[i] = userDegrees[maxIdx];
        userDegrees[maxIdx] = temp;
        
        topUsers.append(userDegrees[i]);
    }
    
    return topUsers;
}

int GraphStats::countTriangles(int userId) {
    int triangles = 0;
    LinkedList<Edge>& friends = graph->getNeighbors(userId);
    
    // Check all pairs of friends
    for (int i = 0; i < friends.size(); i++) {
        for (int j = i + 1; j < friends.size(); j++) {
            if (graph->hasEdge(friends[i].to, friends[j].to)) {
                triangles++;
            }
        }
    }
    
    return triangles;
}

double GraphStats::calculateLocalClustering(int userId) {
    int degree = getUserDegree(userId);
    
    if (degree < 2) return 0.0;
    
    int triangles = countTriangles(userId);
    int possibleTriangles = (degree * (degree - 1)) / 2;
    
    return static_cast<double>(triangles) / possibleTriangles;
}

double GraphStats::getClusteringCoefficient() {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    if (allUsers.isEmpty()) return 0.0;
    
    double totalClustering = 0.0;
    int validUsers = 0;
    
    for (int i = 0; i < allUsers.size(); i++) {
        if (getUserDegree(allUsers[i]) >= 2) {
            totalClustering += calculateLocalClustering(allUsers[i]);
            validUsers++;
        }
    }
    
    if (validUsers == 0) return 0.0;
    
    return totalClustering / validUsers;
}

double GraphStats::getGraphDensity() {
    int n = getTotalUsers();
    if (n < 2) return 0.0;
    
    int maxPossibleEdges = (n * (n - 1)) / 2;
    int actualEdges = getTotalFriendships();
    
    return static_cast<double>(actualEdges) / maxPossibleEdges;
}

int GraphStats::countConnectedComponents() {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    HashMap<int, bool> visited;
    int components = 0;
    
    for (int i = 0; i < allUsers.size(); i++) {
        int userId = allUsers[i];
        if (!visited.contains(userId)) {
            // BFS from this node
            Queue<int> queue;
            queue.enqueue(userId);
            visited.put(userId, true);
            
            while (!queue.isEmpty()) {
                int current = queue.dequeue();
                LinkedList<Edge>& neighbors = graph->getNeighbors(current);
                
                for (int j = 0; j < neighbors.size(); j++) {
                    int neighbor = neighbors[j].to;
                    if (!visited.contains(neighbor)) {
                        visited.put(neighbor, true);
                        queue.enqueue(neighbor);
                    }
                }
            }
            
            components++;
        }
    }
    
    return components;
}

int GraphStats::getConnectedComponents() {
    return countConnectedComponents();
}

HashMap<int, int> GraphStats::getDegreeDistribution() {
    HashMap<int, int> distribution;
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    for (int i = 0; i < allUsers.size(); i++) {
        int degree = getUserDegree(allUsers[i]);
        
        if (distribution.contains(degree)) {
            int count = distribution.get(degree);
            distribution.put(degree, count + 1);
        } else {
            distribution.put(degree, 1);
        }
    }
    
    return distribution;
}

GraphMetrics GraphStats::getGraphMetrics() {
    GraphMetrics metrics;
    
    metrics.totalUsers = getTotalUsers();
    metrics.totalFriendships = getTotalFriendships();
    metrics.averageDegree = getAverageDegree();
    
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    
    if (!allUsers.isEmpty()) {
        int maxDeg = 0, minDeg = getUserDegree(allUsers[0]);
        
        for (int i = 0; i < allUsers.size(); i++) {
            int degree = getUserDegree(allUsers[i]);
            if (degree > maxDeg) maxDeg = degree;
            if (degree < minDeg) minDeg = degree;
        }
        
        metrics.maxDegree = maxDeg;
        metrics.minDegree = minDeg;
    } else {
        metrics.maxDegree = 0;
        metrics.minDegree = 0;
    }
    
    metrics.mostPopularUser = getMostPopularUser();
    metrics.clusteringCoefficient = getClusteringCoefficient();
    metrics.connectedComponents = getConnectedComponents();
    metrics.density = getGraphDensity();
    
    return metrics;
}