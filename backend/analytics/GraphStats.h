#ifndef GRAPHSTATS_H
#define GRAPHSTATS_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/LinkedList.h"

struct GraphMetrics {
    int totalUsers;
    int totalFriendships;
    double averageDegree;
    int maxDegree;
    int minDegree;
    int mostPopularUser;
    double clusteringCoefficient;
    int connectedComponents;
    double density;
};

class GraphStats {
private:
    Graph* graph;
    
    // Helper functions
    int countTriangles(int userId);
    double calculateLocalClustering(int userId);
    int countConnectedComponents();

public:
    GraphStats(Graph* g);
    
    // Get comprehensive statistics
    GraphMetrics getGraphMetrics();
    
    // Individual metrics
    int getTotalUsers();
    int getTotalFriendships();
    double getAverageDegree();
    int getUserDegree(int userId);
    
    // Advanced metrics
    int getMostPopularUser();
    LinkedList<int> getTopNPopularUsers(int n);
    double getClusteringCoefficient();
    double getGraphDensity();
    int getConnectedComponents();
    
    // Degree distribution
    HashMap<int, int> getDegreeDistribution();
};

#endif // GRAPHSTATS_H