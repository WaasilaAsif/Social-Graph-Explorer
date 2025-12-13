#include "../dsa/graph/Graph.h"
#include "../algorithms/BFS.h"
#include <iostream>
int main() {
    // case 1
    std::cout << "--- TEST CASE 1: Simple Connected Graph ---\n";
    Graph g1;
    g1.addNode(1);
    g1.addNode(2);
    g1.addNode(3);
    g1.addNode(4);
    g1.addEdge(1, 2);
    g1.addEdge(2, 3);
    g1.addEdge(3, 4);
    g1.addEdge(1, 4);

    std::cout << "BFS Traversal from 1: ";
    LinkedList<int> order1 = BFS::traverse(g1, 1);
    for (int i = 0; i < order1.size(); ++i)
        std::cout << order1[i] << " ";
    std::cout << "\n";

    std::cout << "Shortest path from 1 to 3: ";
    LinkedList<int> path1 = BFS::shortestPath(g1, 1, 3);
    for (int i = 0; i < path1.size(); ++i)
        std::cout << path1[i] << " ";
    std::cout << "\n";

    std::cout << "Distance from 1 to 3: " << BFS::distance(g1, 1, 3) << "\n";
    std::cout << "Path exists from 1 to 4: " << (BFS::existsPath(g1, 1, 4) ? "Yes" : "No") << "\n\n";

    // case 2
    std::cout << "--- TEST CASE 2: Disconnected Graph ---\n";
    Graph g2;
    g2.addNode(1);
    g2.addNode(2);
    g2.addNode(3);
    g2.addNode(4);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    // No connection between {1,2} and {3,4}

    std::cout << "BFS Traversal from 1: ";
    LinkedList<int> order2 = BFS::traverse(g2, 1);
    for (int i = 0; i < order2.size(); ++i)
        std::cout << order2[i] << " ";
    std::cout << "\n";

    std::cout << "Path exists from 1 to 3: " << (BFS::existsPath(g2, 1, 3) ? "Yes" : "No") << "\n";
    std::cout << "Distance from 1 to 3: " << BFS::distance(g2, 1, 3) << " (should be -1 for no path)\n\n";

    // case 3
    std::cout << "--- TEST CASE 3: Linear Chain Graph ---\n";
    Graph g3;
    g3.addNode(1);
    g3.addNode(2);
    g3.addNode(3);
    g3.addNode(4);
    g3.addNode(5);
    g3.addEdge(1, 2);
    g3.addEdge(2, 3);
    g3.addEdge(3, 4);
    g3.addEdge(4, 5);

    std::cout << "BFS Traversal from 1: ";
    LinkedList<int> order3 = BFS::traverse(g3, 1);
    for (int i = 0; i < order3.size(); ++i)
        std::cout << order3[i] << " ";
    std::cout << "\n";

    std::cout << "Shortest path from 1 to 5: ";
    LinkedList<int> path3 = BFS::shortestPath(g3, 1, 5);
    for (int i = 0; i < path3.size(); ++i)
        std::cout << path3[i] << " ";
    std::cout << "\n";

    std::cout << "Distance from 1 to 5: " << BFS::distance(g3, 1, 5) << "\n";

    return 0;
}