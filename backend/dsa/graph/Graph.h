#ifndef GRAPH_H
#define GRAPH_H

#include "../containers/LinkedList.h"
#include "../containers/HashMap.h"
#include "../containers/DynamicArray.h"  // ✅ ADD THIS - Graph.h uses DynamicArray directly
#include "Edge.h"
#include "Node.h"
#include <stdexcept>
#include <iostream>
#include <new>  // ✅ ADD THIS for std::nothrow

class Graph {
private:
    // Map from node ID (int) to Node
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

        // ✅ FIXED: Get the node pointer first before doing anything
        Node* nodeToDelete = nodes.get(id);

        // Get all node IDs first
        LinkedList<int> allIds = getAllNodeIDs();
        
        // Remove this node from other nodes' adjacency lists
        // ✅ FIXED: Use try-catch to ensure node is deleted even if edge removal fails
        try {
            for (int i = 0; i < allIds.size(); ++i) {
                if (allIds[i] == id) continue; // skip the node being removed
                
                Node* node = nodes.get(allIds[i]);
                LinkedList<Edge>& edges = node->edges;
                // Remove edges pointing to this node
                removeEdgeFromList(edges, id);
            }
        } catch (...) {
            // Even if edge removal fails, we still want to delete the node
            // and remove it from the map
        }

        // Delete the node and remove from map
        delete nodeToDelete;
        nodes.remove(id);
    }

    // Add an edge between two nodes (undirected by default)
    void addEdge(int from, int to, int weight = 1, bool undirected = true) {
        if (!nodes.contains(from) || !nodes.contains(to))
            throw std::runtime_error("One or both nodes do not exist");

        // ✅ FIXED: Check if edge already exists to prevent duplicates
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

        // ✅ FIXED: Check if edge exists first
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
        // ✅ FIXED: More robust cleanup - delete nodes even if some fail
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

    // Debug print
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
    // ✅ FIXED: Remove ALL matching edges, not just the first
    void removeEdgeFromList(LinkedList<Edge>& edges, int targetNode) {
        // Remove all edges pointing to targetNode
        for (int i = edges.size() - 1; i >= 0; --i) {
            if (edges[i].to == targetNode) {
                Edge toRemove(targetNode, edges[i].weight);
                edges.remove(toRemove);
            }
        }
    }
};

#endif // GRAPH_H