#include "../../dsa/graph/Graph.h"
#include "../../algorithms/BFS.h"
#include <iostream>

int main() {
    Graph g;
    // *** CHANGED: Use int instead of string ***
    g.addNode(1);
    g.addNode(2);
    g.addNode(3);
    g.addNode(4);

    // *** CHANGED: Use int instead of string ***
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(1, 4);

    std::cout << "BFS Traversal from 1:\n";
    // *** CHANGED: LinkedList<int> instead of LinkedList<string> ***
    LinkedList<int> order = BFS::traverse(g, 1);
    for (int i = 0; i < order.size(); ++i)
        std::cout << order[i] << " ";
    std::cout << "\n";

    std::cout << "Shortest path from 1 to 3:\n";
    // *** CHANGED: LinkedList<int> instead of LinkedList<string> ***
    LinkedList<int> path = BFS::shortestPath(g, 1, 3);
    for (int i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";

    // *** ADDITIONAL TEST: Distance ***
    std::cout << "Distance from 1 to 3: ";
    int dist = BFS::distance(g, 1, 3);
    std::cout << dist << "\n";

    // *** ADDITIONAL TEST: Path exists ***
    std::cout << "Path exists from 1 to 4: ";
    bool exists = BFS::existsPath(g, 1, 4);
    std::cout << (exists ? "Yes" : "No") << "\n";

    return 0;
}