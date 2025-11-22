// test_graph.cpp
#include "../dsa/graph/Graph.h"
#include <iostream>

int main() {
    Graph g;

    std::cout << "Adding nodes...\n";
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);

    std::cout << "Node count: " << g.nodeCount() << "\n"; // 3

    std::cout << "Adding edges...\n";
    g.addEdge(1, 2);
    g.addEdge(2, 3);

    std::cout << "Has edge 1->2: " << (g.hasEdge(1, 2) ? "Yes" : "No") << "\n"; // Yes
    std::cout << "Has edge 1->3: " << (g.hasEdge(1, 3) ? "Yes" : "No") << "\n"; // No

    std::cout << "\nGraph structure:\n";
    g.print();

    std::cout << "\nRemoving edge 1->2...\n";
    g.removeEdge(1, 2);
    g.print();

    std::cout << "\nRemoving node 3...\n";
    g.removeNode(3);
    g.print();

    return 0;
}