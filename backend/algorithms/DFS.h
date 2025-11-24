#ifndef DFS_H
#define DFS_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/Stack.h"
#include "../dsa/containers/HashMap.h"
#include <stdexcept>
#include <iostream>

class DFS {
public:
    // Perform DFS starting from a given node ID (iterative approach using Stack)
    // Returns nodes in order of visitation
    static LinkedList<int> traverse(const Graph& graph, int startID) {
        if (!graph.hasNode(startID))
            throw std::runtime_error("Start node does not exist");

        LinkedList<int> visitedOrder;  
        HashMap<int, bool> visited(100);  
        Stack<int> stack;  

        stack.push(startID);

        while (!stack.isEmpty()) {
            int current = stack.pop();  

            // Skip if already visited
            if (visited.contains(current))  
                continue;

            visited.put(current, true);  
            visitedOrder.append(current);

            // Push neighbors in reverse order to maintain left-to-right traversal
            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = neighbors.size() - 1; i >= 0; --i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    stack.push(neighborID);
                }
            }
        }

        return visitedOrder;
    }

    // Recursive DFS (alternative implementation)
    static LinkedList<int> traverseRecursive(const Graph& graph, int startID) {
        if (!graph.hasNode(startID))
            throw std::runtime_error("Start node does not exist");

        LinkedList<int> visitedOrder;  
        HashMap<int, bool> visited(100);  
        
        dfsRecursiveHelper(graph, startID, visited, visitedOrder);
        
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
        Stack<int> stack;  

        stack.push(startID);

        while (!stack.isEmpty()) {
            int current = stack.pop();  

            if (visited.contains(current))  
                continue;

            if (current == targetID)
                return true;

            visited.put(current, true);  

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to;  
                if (!visited.contains(neighborID)) {  
                    stack.push(neighborID);
                }
            }
        }

        return false;
    }

    // Find a path between two nodes (not necessarily shortest)
    // DFS doesn't guarantee shortest path, but can find a path
    static LinkedList<int> findPath(const Graph& graph, int startID, int targetID) {
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
        Stack<int> stack;  

        stack.push(startID);
        parent.put(startID, -1);  

        bool found = false;

        while (!stack.isEmpty() && !found) {
            int current = stack.pop();  

            if (visited.contains(current))  
                continue;

            visited.put(current, true);  

            if (current == targetID) {
                found = true;
                break;
            }

            const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
            for (int i = 0; i < neighbors.size(); ++i) {
                int neighborID = neighbors[i].to; 
                if (!visited.contains(neighborID)) {  
                    stack.push(neighborID);
                    if (!parent.contains(neighborID)) {  
                        parent.put(neighborID, current);  
                    }
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

    // Detect if the graph has a cycle (for undirected graphs)
    static bool hasCycle(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();  
        HashMap<int, bool> visited(100);  

        // Check each component
        for (int i = 0; i < allNodes.size(); ++i) {
            if (!visited.contains(allNodes[i])) {  
                if (hasCycleHelper(graph, allNodes[i], -1, visited))  
                    return true;
            }
        }

        return false;
    }

    // Check if graph is connected (all nodes reachable from any node)
    static bool isConnected(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();  
        
        if (allNodes.isEmpty())
            return true;

        // Traverse from first node
        LinkedList<int> reachable = traverse(graph, allNodes[0]);  
        
        // Check if all nodes were reached
        return reachable.size() == allNodes.size();
    }

    // Count connected components
    static int countComponents(const Graph& graph) {
        LinkedList<int> allNodes = graph.getAllNodeIDs();  
        HashMap<int, bool> visited(100);  
        int components = 0;

        for (int i = 0; i < allNodes.size(); ++i) {
            if (!visited.contains(allNodes[i])) {  
                components++;
                // Visit all nodes in this component
                LinkedList<int> component = traverse(graph, allNodes[i]);  
                for (int j = 0; j < component.size(); ++j) {
                    visited.put(component[j], true);  
                }
            }
        }

        return components;
    }

    static void printTraversal(const Graph& graph, int startID) {
        LinkedList<int> order = traverse(graph, startID);  
        std::cout << "DFS from " << startID << ": ";
        for (int i = 0; i < order.size(); ++i) {
            std::cout << order[i];
            if (i < order.size() - 1) std::cout << " -> ";
        }
        std::cout << std::endl;
    }

private:
    // Helper for recursive DFS
    static void dfsRecursiveHelper(const Graph& graph, int current,  
                                   HashMap<int, bool>& visited,  
                                   LinkedList<int>& visitedOrder) {  
        visited.put(current, true);  
        visitedOrder.append(current);

        const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
        for (int i = 0; i < neighbors.size(); ++i) {
            int neighborID = neighbors[i].to; 
            if (!visited.contains(neighborID)) {  
                dfsRecursiveHelper(graph, neighborID, visited, visitedOrder);
            }
        }
    }

    // Helper for cycle detection
    static bool hasCycleHelper(const Graph& graph, int current, 
                              int parent,  
                              HashMap<int, bool>& visited) {  
        visited.put(current, true);  

        const LinkedList<Edge>& neighbors = graph.getNeighbors(current);
        for (int i = 0; i < neighbors.size(); ++i) {
            int neighborID = neighbors[i].to;  
            
            if (!visited.contains(neighborID)) {  
                if (hasCycleHelper(graph, neighborID, current, visited))
                    return true;
            }
            // If visited and not parent, we found a cycle
            else if (neighborID != parent) {
                return true;
            }
        }

        return false;
    }
};

#endif