#include "../dsa/graph/Graph.h"
#include "../algorithms/DFS.h"
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

    std::cout << "DFS Traversal (Iterative) from 1: ";
    LinkedList<int> order1 = DFS::traverse(g1, 1);
    for (int i = 0; i < order1.size(); ++i)
        std::cout << order1[i] << " ";
    std::cout << "\n";

    std::cout << "DFS Traversal (Recursive) from 1: ";
    LinkedList<int> orderRec1 = DFS::traverseRecursive(g1, 1);
    for (int i = 0; i < orderRec1.size(); ++i)
        std::cout << orderRec1[i] << " ";
    std::cout << "\n";

    std::cout << "Path from 1 to 3: ";
    LinkedList<int> path1 = DFS::findPath(g1, 1, 3);
    for (int i = 0; i < path1.size(); ++i)
        std::cout << path1[i] << " ";
    std::cout << "\n";

    std::cout << "Path exists from 1 to 4: " << (DFS::existsPath(g1, 1, 4) ? "Yes" : "No") << "\n";
    std::cout << "Has cycle: " << (DFS::hasCycle(g1) ? "Yes" : "No") << "\n";
    std::cout << "Is connected: " << (DFS::isConnected(g1) ? "Yes" : "No") << "\n";
    std::cout << "Number of components: " << DFS::countComponents(g1) << "\n\n";

    // case 2
    std::cout << "--- TEST CASE 2: Disconnected Graph ---\n";
    Graph g2;
    g2.addNode(1);
    g2.addNode(2);
    g2.addNode(3);
    g2.addNode(4);
    g2.addNode(5);
    g2.addEdge(1, 2);
    g2.addEdge(3, 4);
    g2.addEdge(4, 5);
    // Two components: {1,2} and {3,4,5}

    std::cout << "DFS Traversal from 1: ";
    LinkedList<int> order2 = DFS::traverse(g2, 1);
    for (int i = 0; i < order2.size(); ++i)
        std::cout << order2[i] << " ";
    std::cout << "\n";

    std::cout << "DFS Traversal from 3: ";
    LinkedList<int> order2b = DFS::traverse(g2, 3);
    for (int i = 0; i < order2b.size(); ++i)
        std::cout << order2b[i] << " ";
    std::cout << "\n";

    std::cout << "Path exists from 1 to 3: " << (DFS::existsPath(g2, 1, 3) ? "Yes" : "No") << "\n";
    std::cout << "Path from 1 to 3: ";
    LinkedList<int> path2 = DFS::findPath(g2, 1, 3);
    if (path2.isEmpty())
        std::cout << "No path found";
    else
        for (int i = 0; i < path2.size(); ++i)
            std::cout << path2[i] << " ";
    std::cout << "\n";

    std::cout << "Has cycle: " << (DFS::hasCycle(g2) ? "Yes" : "No") << "\n";
    std::cout << "Is connected: " << (DFS::isConnected(g2) ? "Yes" : "No") << "\n";
    std::cout << "Number of components: " << DFS::countComponents(g2) << "\n\n";

    // case 3
    std::cout << "--- TEST CASE 3: Tree Structure (No Cycles) ---\n";
    Graph g3;
    g3.addNode(1);
    g3.addNode(2);
    g3.addNode(3);
    g3.addNode(4);
    g3.addNode(5);
    g3.addNode(6);
    g3.addNode(7);
    g3.addEdge(1, 2);
    g3.addEdge(1, 3);
    g3.addEdge(2, 4);
    g3.addEdge(2, 5);
    g3.addEdge(3, 6);
    g3.addEdge(3, 7);
    // Tree structure:
    //       1
    //      / \
    //     2   3
    //    / \ / \
    //   4  5 6  7

    std::cout << "DFS Traversal (Iterative) from 1: ";
    LinkedList<int> order3 = DFS::traverse(g3, 1);
    for (int i = 0; i < order3.size(); ++i)
        std::cout << order3[i] << " ";
    std::cout << "\n";

    std::cout << "DFS Traversal (Recursive) from 1: ";
    LinkedList<int> orderRec3 = DFS::traverseRecursive(g3, 1);
    for (int i = 0; i < orderRec3.size(); ++i)
        std::cout << orderRec3[i] << " ";
    std::cout << "\n";

    std::cout << "Path from 1 to 7: ";
    LinkedList<int> path3 = DFS::findPath(g3, 1, 7);
    for (int i = 0; i < path3.size(); ++i)
        std::cout << path3[i] << " ";
    std::cout << "\n";

    std::cout << "Path exists from 4 to 7: " << (DFS::existsPath(g3, 4, 7) ? "Yes" : "No") << "\n";
    std::cout << "Has cycle: " << (DFS::hasCycle(g3) ? "Yes" : "No") << "\n";
    std::cout << "Is connected: " << (DFS::isConnected(g3) ? "Yes" : "No") << "\n";
    std::cout << "Number of components: " << DFS::countComponents(g3) << "\n\n";

    // ========== TEST CASE 4: Graph with Multiple Cycles ==========
    std::cout << "=== TEST CASE 4: Graph with Multiple Cycles ===\n";
    Graph g4;
    g4.addNode(1);
    g4.addNode(2);
    g4.addNode(3);
    g4.addNode(4);
    g4.addNode(5);
    g4.addEdge(1, 2);
    g4.addEdge(2, 3);
    g4.addEdge(3, 1);  // Cycle 1: 1-2-3-1
    g4.addEdge(3, 4);
    g4.addEdge(4, 5);
    g4.addEdge(5, 3);  // Cycle 2: 3-4-5-3

    std::cout << "DFS Traversal from 1: ";
    LinkedList<int> order4 = DFS::traverse(g4, 1);
    for (int i = 0; i < order4.size(); ++i)
        std::cout << order4[i] << " ";
    std::cout << "\n";

    std::cout << "Path from 1 to 5: ";
    LinkedList<int> path4 = DFS::findPath(g4, 1, 5);
    for (int i = 0; i < path4.size(); ++i)
        std::cout << path4[i] << " ";
    std::cout << "\n";

    std::cout << "Has cycle: " << (DFS::hasCycle(g4) ? "Yes" : "No") << "\n";
    std::cout << "Is connected: " << (DFS::isConnected(g4) ? "Yes" : "No") << "\n";
    std::cout << "Number of components: " << DFS::countComponents(g4) << "\n";

    return 0;
}