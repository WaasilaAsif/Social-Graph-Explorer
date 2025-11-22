#include "../../dsa/graph/Graph.h"
#include "../../algorithms/DFS.h"
#include <iostream>

int main() {
    Graph g;
    // *** CHANGED: Use int instead of string ***
    // Using numbers instead of letters
    g.addNode(1);  // A -> 1
    g.addNode(2);  // B -> 2
    g.addNode(3);  // C -> 3
    g.addNode(4);  // D -> 4

    // *** CHANGED: Use int instead of string ***
    g.addEdge(1, 2);  // A-B
    g.addEdge(2, 3);  // B-C
    g.addEdge(3, 4);  // C-D
    g.addEdge(1, 4);  // A-D

    std::cout << "DFS Traversal from 1:\n";
    // *** CHANGED: LinkedList<int> instead of LinkedList<string> ***
    LinkedList<int> order = DFS::traverse(g, 1);
    for (int i = 0; i < order.size(); ++i)
        std::cout << order[i] << " ";
    std::cout << "\n";

    std::cout << "DFS path from 1 to 3:\n";
    // *** CHANGED: LinkedList<int> instead of LinkedList<string> ***
    LinkedList<int> path = DFS::findPath(g, 1, 3);
    for (int i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";

    // *** ADDITIONAL TEST: Recursive DFS ***
    std::cout << "Recursive DFS from 1:\n";
    LinkedList<int> recursiveOrder = DFS::traverseRecursive(g, 1);
    for (int i = 0; i < recursiveOrder.size(); ++i)
        std::cout << recursiveOrder[i] << " ";
    std::cout << "\n";

    // *** ADDITIONAL TEST: Has cycle ***
    std::cout << "Graph has cycle: ";
    bool hasCycle = DFS::hasCycle(g);
    std::cout << (hasCycle ? "Yes" : "No") << "\n";

    // *** ADDITIONAL TEST: Is connected ***
    std::cout << "Graph is connected: ";
    bool isConnected = DFS::isConnected(g);
    std::cout << (isConnected ? "Yes" : "No") << "\n";

    // *** ADDITIONAL TEST: Count components ***
    std::cout << "Number of components: ";
    int components = DFS::countComponents(g);
    std::cout << components << "\n";

    return 0;
}