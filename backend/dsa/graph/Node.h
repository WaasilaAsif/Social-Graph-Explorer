#ifndef NODE_H
#define NODE_H

#include "../containers/LinkedList.h"
#include "Edge.h"

class Node {
public:
    int id;  
    LinkedList<Edge> edges;  // adjacency list

    Node(int id) : id(id) {}
};

#endif