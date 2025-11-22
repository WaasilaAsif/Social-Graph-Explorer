#ifndef GRAPH_H
#define GRAPH_H

#include "../containers/LinkedList.h"
#include "../containers/HashMap.h"
#include "Edge.h"
#include "Node.h"
#include <stdexcept>
#include <iostream>

// *** MODIFIED: Graph class now uses int IDs instead of string ***
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
        nodes.put(id, new Node(id));
    }

    // Remove a node and all its edges
    void removeNode(int id) {
        if (!nodes.contains(id))
            throw std::runtime_error("Node does not exist");

        // Get all node IDs first
        LinkedList<int> allIds = getAllNodeIDs();
        
        // Remove this node from other nodes' adjacency lists
        for (int i = 0; i < allIds.size(); ++i) {
            if (allIds[i] == id) continue; // skip the node being removed
            
            Node* node = nodes.get(allIds[i]);
            LinkedList<Edge>& edges = node->edges;
            // Remove edges pointing to this node
            removeEdgeFromList(edges, id);
        }

        // Delete the node and remove from map
        delete nodes.get(id);
        nodes.remove(id);
    }

    // Add an edge between two nodes (undirected by default)
    void addEdge(int from, int to, int weight = 1, bool undirected = true) {
        if (!nodes.contains(from) || !nodes.contains(to))
            throw std::runtime_error("One or both nodes do not exist");

        nodes.get(from)->edges.append(Edge(to, weight));
        if (undirected)
            nodes.get(to)->edges.append(Edge(from, weight));
    }

    // Remove an edge between two nodes
    void removeEdge(int from, int to, bool undirected = true) {
        if (!nodes.contains(from) || !nodes.contains(to))
            throw std::runtime_error("One or both nodes do not exist");

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
        for (int i = 0; i < allIds.size(); ++i) {
            delete nodes.get(allIds[i]);
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
    void removeEdgeFromList(LinkedList<Edge>& edges, int targetNode) {
        for (int i = 0; i < edges.size(); ++i) {
            if (edges[i].to == targetNode) {
                Edge toRemove(targetNode, edges[i].weight);
                edges.remove(toRemove);
                break;
            }
        }
    }
};

#endif // GRAPH_H