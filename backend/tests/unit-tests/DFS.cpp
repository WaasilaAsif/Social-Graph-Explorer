#include "../../dsa/graph/Graph.h"
#include "../../algorithms/DFS.h"
#include <iostream>

int main() {
    Graph g;
    g.addNode(1);  
    g.addNode(2);  
    g.addNode(3);  
    g.addNode(4);  

    g.addEdge(1, 2);  
    g.addEdge(2, 3);  
    g.addEdge(3, 4);  
    g.addEdge(1, 4);  

    std::cout << "DFS Traversal from 1:\n";
    LinkedList<int> order = DFS::traverse(g, 1);
    for (int i = 0; i < order.size(); ++i)
        std::cout << order[i] << " ";
    std::cout << "\n";

    std::cout << "DFS path from 1 to 3:\n";
    LinkedList<int> path = DFS::findPath(g, 1, 3);
    for (int i = 0; i < path.size(); ++i)
        std::cout << path[i] << " ";
    std::cout << "\n";

    std::cout << "Recursive DFS from 1:\n";
    LinkedList<int> recursiveOrder = DFS::traverseRecursive(g, 1);
    for (int i = 0; i < recursiveOrder.size(); ++i)
        std::cout << recursiveOrder[i] << " ";
    std::cout << "\n";

    std::cout << "Graph has cycle: ";
    bool hasCycle = DFS::hasCycle(g);
    std::cout << (hasCycle ? "Yes" : "No") << "\n";

    std::cout << "Graph is connected: ";
    bool isConnected = DFS::isConnected(g);
    std::cout << (isConnected ? "Yes" : "No") << "\n";

    std::cout << "Number of components: ";
    int components = DFS::countComponents(g);
    std::cout << components << "\n";

    return 0;
}