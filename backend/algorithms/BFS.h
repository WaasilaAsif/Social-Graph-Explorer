#ifndef BFS_H
#define BFS_H

#include "../dsa/graph/Graph.h"         
#include "../dsa/containers/Queue.h" 
#include "../dsa/containers/HashMap.h"
#include <stdexcept>
#include <iostream>

class BFS {
public:
    // Returns nodes in order of visitation
    static LinkedList<int> traverse(const Graph& graph, int startID) {
        if (!graph.hasNode(startID))
            throw std::runtime_error("Start node does not exist");

        LinkedList<int> visitedOrder;
        HashMap<int, bool> visited(100);  
        Queue<int> queue;  

        queue.enqueue(startID);
        visited.put(startID, true);  

        while (!queue.isEmpty()) {
            int current = queue.dequeue(); 
            visitedOrder.append(current);

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);  
                }
            }
        }

        return visitedOrder;
    }

    // Check if a path exists between two nodes
    static bool existsPath(const Graph& graph, int startID, int targetID) {
        if (!graph.hasNode(startID) || !graph.hasNode(targetID))
            throw std::runtime_error("Start or target node does not exist");

        // Early exit if start == target
        if (startID == targetID)
            return true;

        HashMap<int, bool> visited(100);  
        Queue<int> queue;  

        queue.enqueue(startID);
        visited.put(startID, true);  
        while (!queue.isEmpty()) {
            int current = queue.dequeue();  

            if (current == targetID)
                return true;

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);  
                }
            }
        }

        return false;
    }

    // Find shortest path between two nodes (returns empty list if no path exists)
    static LinkedList<int> shortestPath(const Graph& graph, int startID, int targetID) {
        if (!graph.hasNode(startID) || !graph.hasNode(targetID))
            throw std::runtime_error("Start or target node does not exist");

        LinkedList<int> path;  

        // Early exit if start == target
        if (startID == targetID) {
            path.append(startID);
            return path;
        }

        HashMap<int, bool> visited(100);  
        HashMap<int, int> parent(100);    
        Queue<int> queue;  

        queue.enqueue(startID);
        visited.put(startID, true);  
        parent.put(startID, -1);     
        bool found = false;

        while (!queue.isEmpty() && !found) {
            int current = queue.dequeue();  

            if (current == targetID) {
                found = true;
                break;
            }

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);  
                    parent.put(neighborID, current);  
                }
            }
        }

        // Reconstruct path if found
        if (found) {
            int current = targetID;  
            LinkedList<int> reversePath;  
            
            while (current != -1) {  
                reversePath.append(current);
                current = parent.get(current);  
            }

            // Reverse the path
            for (int i = reversePath.size() - 1; i >= 0; --i) {
                path.append(reversePath[i]);
            }
        }

        return path; // Empty if no path found
    }

    // Get distance (number of edges) between two nodes (-1 if no path)
    static int distance(const Graph& graph, int startID, int targetID) {
        if (!graph.hasNode(startID) || !graph.hasNode(targetID))
            throw std::runtime_error("Start or target node does not exist");

        if (startID == targetID)
            return 0;

        HashMap<int, bool> visited(100);  
        HashMap<int, int> dist(100);      
        Queue<int> queue;  

        queue.enqueue(startID);
        visited.put(startID, true);  
        dist.put(startID, 0);        
        while (!queue.isEmpty()) {
            int current = queue.dequeue();  

            if (current == targetID)
                return dist.get(current);  

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    queue.enqueue(neighborID);
                    visited.put(neighborID, true);  
                    dist.put(neighborID, dist.get(current) + 1);  
                }
            }
        }

        return -1; // No path found
    }

    static void printTraversal(const Graph& graph, int startID) {
        LinkedList<int> order = traverse(graph, startID); 
        std::cout << "BFS from " << startID << ": ";
        for (int i = 0; i < order.size(); ++i) {
            std::cout << order[i];
            if (i < order.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }
};

#endif 