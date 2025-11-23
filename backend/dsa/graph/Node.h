#ifndef NODE_H
#define NODE_H

#include "../containers/LinkedList.h"
#include "Edge.h"

// *** MODIFIED: Node class now uses int ID instead of string ***
class Node {
public:
    int id;  // Changed from std::string to int
    LinkedList<Edge> edges;  // adjacency list

    Node(int id) : id(id) {}
};

#endif // NODE_H