#ifndef GRAPH_H
#define GRAPH_H

#include "../containers/LinkedList.h"
#include "../containers/HashMap.h"
#include "../containers/DynamicArray.h"  
#include "Edge.h"
#include "Node.h"
#include <stdexcept>
#include <iostream>
#include <new>  

class Graph {
private:
    // Map from node ID to Node
    HashMap<int, Node*> nodes;

public:
    Graph() : nodes(50) {}  // Initialize with reasonable bucket count

    ~Graph() {
        clear();
    }

    // Disable copy (or implement deep copy if needed)
    Graph(const Graph&) = delete;
    Graph& operator=(const Graph&) = delete;

    // Add a node with the given ID
    void addNode(int id) {
        if (nodes.contains(id))
            throw std::runtime_error("Node already exists");
        
        Node* newNode = new Node(id);  // Let it throw std::bad_alloc if it fails
        
        try {
            nodes.put(id, newNode);
        } catch (...) {
            delete newNode;
            throw;
        }
    }

    // Remove a node and all its edges
    void removeNode(int id) {
    if (!nodes.contains(id))
        throw std::runtime_error("Node does not exist");
    
    Node* nodeToDelete = nodes.get(id);
    
    // Remove from map FIRST
    nodes.remove(id);
    
    // Clean up edges in other nodes
    LinkedList<int> allIds = getAllNodeIDs();
    for (int i = 0; i < allIds.size(); ++i) {
        Node* node = nodes.get(allIds[i]);
        removeEdgeFromList(node->edges, id);
    }
    
    // Delete last (can't throw)
    delete nodeToDelete;
}

    // Add an edge between two nodes (undirected by default)
    void addEdge(int from, int to, int weight = 1, bool undirected = true) {
        if (!nodes.contains(from) || !nodes.contains(to))
            throw std::runtime_error("One or both nodes do not exist");

        // Check if edge already exists to prevent duplicates
        if (hasEdge(from, to)) {
            return; // Edge already exists, silently return (or throw if you prefer)
        }

        nodes.get(from)->edges.append(Edge(to, weight));
        if (undirected)
            nodes.get(to)->edges.append(Edge(from, weight));
    }

    // Remove an edge between two nodes
    void removeEdge(int from, int to, bool undirected = true) {
        if (!nodes.contains(from) || !nodes.contains(to))
            throw std::runtime_error("One or both nodes do not exist");

        // Check if edge exists first
        if (!hasEdge(from, to)) {
            return; // Edge doesn't exist, silently return (or throw if you prefer)
        }

        removeEdgeFromList(nodes.get(from)->edges, to);

        if (undirected) {
            removeEdgeFromList(nodes.get(to)->edges, from);
        }
    }

    // Get neighbors of a node
    LinkedList<Edge>& getNeighbors(int id) {
        if (!nodes.contains(id))
            throw std::runtime_error("Node does not exist");
        return nodes.get(id)->edges;
    }

    // Get neighbors of a node (const version)
    const LinkedList<Edge>& getNeighbors(int id) const {
        if (!nodes.contains(id))
            throw std::runtime_error("Node does not exist");
        return nodes.get(id)->edges;
    }

    // Check if node exists
    bool hasNode(int id) const {
        return nodes.contains(id);
    }

    // Check if an edge exists
    bool hasEdge(int from, int to) const {
        if (!hasNode(from) || !hasNode(to))
            return false;
        const LinkedList<Edge>& edges = nodes.get(from)->edges;
        for (int i = 0; i < edges.size(); ++i) {
            if (edges[i].to == to)
                return true;
        }
        return false;
    }

    // Get number of nodes
    int nodeCount() const {
        return nodes.size();
    }

    // Get all node IDs
    LinkedList<int> getAllNodeIDs() const {
        LinkedList<int> ids;
        DynamicArray<int> allKeys = nodes.keys();
        
        // Convert DynamicArray to LinkedList
        for (int i = 0; i < allKeys.size(); i++) {
            ids.append(allKeys.get(i));
        }
        
        return ids;
    }

    // Clear all nodes and edges
    void clear() {
        LinkedList<int> allIds = getAllNodeIDs();
        // delete nodes even if some fail
        for (int i = 0; i < allIds.size(); ++i) {
            try {
                Node* node = nodes.get(allIds[i]);
                delete node;
            } catch (...) {
                // Continue deleting other nodes even if one fails
            }
        }
        nodes.clear();
    }

    void print() const {
        LinkedList<int> allIds = getAllNodeIDs();
        for (int i = 0; i < allIds.size(); ++i) {
            std::cout << allIds[i] << " -> ";
            const LinkedList<Edge>& edges = nodes.get(allIds[i])->edges;
            if (edges.isEmpty()) {
                std::cout << "(no edges)";
            } else {
                for (int j = 0; j < edges.size(); ++j) {
                    std::cout << edges[j].to << "(" << edges[j].weight << ")";
                    if (j < edges.size() - 1) std::cout << ", ";
                }
            }
            std::cout << std::endl;
        }
    }

private:
    // Helper function to remove an edge from an adjacency list
    // Remove ALL matching edges, not just the first
void removeEdgeFromList(LinkedList<Edge>& edges, int targetNode) {
    edges.removeIf([targetNode](const Edge& e) { return e.to == targetNode; });
}
   
};

#endif 