#ifndef GRAPHSTATS_H
#define GRAPHSTATS_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/Queue.h"
#include "DFS.h"
#include <stdexcept>
class GraphStats {
public:
    // Get degree of a node (number of edges)
    static int getDegree(const Graph& graph, int nodeID) {
        if (!graph.hasNode(nodeID))
            throw std::runtime_error("Node does not exist");
        
        return graph.getNeighbors(nodeID).size();
    }
    
    // Get all node degrees
    static HashMap<int, int> getAllDegrees(const Graph& graph) {
        HashMap<int, int> degrees(100);
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        
        for (int i = 0; i < allNodes.size(); ++i) {
            int nodeID = allNodes[i];
            degrees.put(nodeID, getDegree(graph, nodeID));
        }
        
        return degrees;
    }
    
    // Get average degree
    static float getAverageDegree(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        int nodeCount = allNodes.size();
        
        if (nodeCount == 0)
            return 0.0f;
        
        int totalDegree = 0;
        for (int i = 0; i < nodeCount; ++i) {
            totalDegree += getDegree(graph, allNodes[i]);
        }
        
        return (float)totalDegree / nodeCount;
    }
    
    // Count total edges (for undirected graph, divide by 2)
    static int countEdges(const Graph& graph, bool undirected = true) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        int edgeCount = 0;
        
        for (int i = 0; i < allNodes.size(); ++i) {
            edgeCount += graph.getNeighbors(allNodes[i]).size();
        }
        
        if (undirected)
            edgeCount /= 2;
        
        return edgeCount;
    }
    
    // Get density (actual edges / possible edges)
    static float getDensity(const Graph& graph) {
        int nodeCount = graph.nodeCount();
        
        if (nodeCount <= 1)
            return 0.0f;
        
        int actualEdges = countEdges(graph, true);
        int possibleEdges = (nodeCount * (nodeCount - 1)) / 2;
        
        return (float)actualEdges / possibleEdges;
    }
    
    // Check if graph is connected
    static bool isConnected(const Graph& graph) {
        return DFS::isConnected(graph);
    }
    
    // Count connected components
    static int countComponents(const Graph& graph) {
        return DFS::countComponents(graph);
    }
    
    // Get diameter (longest shortest path between any two nodes)
    // Returns -1 if graph is not connected
    static int getDiameter(const Graph& graph) {
        if (!isConnected(graph))
            return -1;
        
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        int maxDistance = 0;
        
        for (int i = 0; i < allNodes.size(); ++i) {
            HashMap<int, int> distances = bfsDistances(graph, allNodes[i]);
            
            DynamicArray<int> distKeys = distances.keys();
            for (int j = 0; j < distKeys.size(); ++j) {
                int dist = distances.get(distKeys.get(j));
                if (dist > maxDistance)
                    maxDistance = dist;
            }
        }
        
        return maxDistance;
    }
    
    // Get clustering coefficient for a node
    static float getClusteringCoefficient(const Graph& graph, int nodeID) {
        if (!graph.hasNode(nodeID))
            throw std::runtime_error("Node does not exist");
        
        const LinkedList<Edge>& neighbors = graph.getNeighbors(nodeID);
        int degree = neighbors.size();
        
        if (degree < 2)
            return 0.0f;
        
        // Count triangles (edges between neighbors)
        int triangles = 0;
        for (int i = 0; i < neighbors.size(); ++i) {
            for (int j = i + 1; j < neighbors.size(); ++j) {
                if (graph.hasEdge(neighbors[i].to, neighbors[j].to))
                    triangles++;
            }
        }
        
        int possibleEdges = (degree * (degree - 1)) / 2;
        return (float)triangles / possibleEdges;
    }
    
    // Get average clustering coefficient for the graph
    static float getAverageClusteringCoefficient(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        int nodeCount = allNodes.size();
        
        if (nodeCount == 0)
            return 0.0f;
        
        float totalCoeff = 0.0f;
        for (int i = 0; i < nodeCount; ++i) {
            totalCoeff += getClusteringCoefficient(graph, allNodes[i]);
        }
        
        return totalCoeff / nodeCount;
    }
    
    // Find node with highest degree
    static int findMostConnectedNode(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();
        
        if (allNodes.isEmpty())
            throw std::runtime_error("Graph is empty");
        
        int maxNode = allNodes[0];
        int maxDegree = getDegree(graph, maxNode);
        
        for (int i = 1; i < allNodes.size(); ++i) {
            int degree = getDegree(graph, allNodes[i]);
            if (degree > maxDegree) {
                maxDegree = degree;
                maxNode = allNodes[i];
            }
        }
        
        return maxNode;
    }
    
    // Print statistics summary
    static void printStats(const Graph& graph) {
        std::cout << "=== Graph Statistics ===" << std::endl;
        std::cout << "Nodes: " << graph.nodeCount() << std::endl;
        std::cout << "Edges: " << countEdges(graph, true) << std::endl;
        std::cout << "Average Degree: " << getAverageDegree(graph) << std::endl;
        std::cout << "Density: " << getDensity(graph) << std::endl;
        std::cout << "Connected: " << (isConnected(graph) ? "Yes" : "No") << std::endl;
        std::cout << "Components: " << countComponents(graph) << std::endl;
        
        if (isConnected(graph)) {
            std::cout << "Diameter: " << getDiameter(graph) << std::endl;
        }
        
        std::cout << "Average Clustering: " << getAverageClusteringCoefficient(graph) << std::endl;
        std::cout << "========================" << std::endl;
    }

private:
    // Helper: BFS to get all distances from a source node
    static HashMap<int, int> bfsDistances(const Graph& graph, int startID) {
        HashMap<int, int> distances(100);
        HashMap<int, bool> visited(100);
        Queue<int> queue;
        
        queue.enqueue(startID);
        visited.put(startID, true);
        distances.put(startID, 0);
        
        while (!queue.isEmpty()) {
            int current = queue.dequeue();
            int currentDist = distances.get(current);
            
            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;
                if (!visited.contains(neighborID)) {
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);
                    distances.put(neighborID, currentDist + 1);
                }
            }
        }
        
        return distances;
    }
};

#endif 