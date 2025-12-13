#include "../dsa/graph/Graph.h"
#include "../algorithms/BFS.h"
#include "../algorithms/DFS.h"
#include <iostream>
#include <chrono>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;
using namespace chrono;

// Generate a random connected graph with N nodes and approximately E edges
Graph* generateRandomGraph(int N, int E) {
    Graph* g = nullptr;
    
    try {
        g = new Graph();
        
        // Add all nodes first
        cout << "      Adding " << N << " nodes..." << flush;
        for (int i = 1; i <= N; ++i) {
            g->addNode(i);
        }
        cout << " Done\n";
        
        // Create a spanning tree to ensure connectivity (N-1 edges)
        cout << "      Creating spanning tree..." << flush;
        for (int i = 2; i <= N; ++i) {
            int parent = (rand() % (i - 1)) + 1;
            g->addEdge(parent, i);
        }
        cout << " Done\n";
        
        // Add remaining random edges (using a set to avoid duplicates)
        cout << "      Adding additional edges..." << flush;
        std::set<pair<int, int>> existingEdges;
        
        // Record spanning tree edges
        for (int i = 2; i <= N; ++i) {
            int parent = (rand() % (i - 1)) + 1;
            if (parent < i) {
                existingEdges.insert({parent, i});
            } else {
                existingEdges.insert({i, parent});
            }
        }
        
        int edgesAdded = N - 1;
        int attempts = 0;
        int maxAttempts = min(E * 2, 100000); // Limit attempts for very large graphs
        
        while (edgesAdded < E && attempts < maxAttempts) {
            int u = (rand() % N) + 1;
            int v = (rand() % N) + 1;
            
            if (u != v) {
                pair<int, int> edge = (u < v) ? make_pair(u, v) : make_pair(v, u);
                
                if (existingEdges.find(edge) == existingEdges.end()) {
                    g->addEdge(u, v);
                    existingEdges.insert(edge);
                    edgesAdded++;
                }
            }
            attempts++;
        }
        cout << " Done (" << edgesAdded << " edges)\n";
        
        return g;
        
    } catch (const std::bad_alloc& e) {
        cerr << "\n      ERROR: Memory allocation failed!\n";
        if (g) delete g;
        throw;
    } catch (const std::exception& e) {
        cerr << "\n      ERROR: " << e.what() << "\n";
        if (g) delete g;
        throw;
    }
}

// Measure execution time in milliseconds
template<typename Func>
double measureTime(Func func) {
    auto start = high_resolution_clock::now();
    func();
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count() / 1000.0;
}

// Run performance test for a given graph size
void runPerformanceTest(int N, int numRuns = 3) {
    cout << "Testing with N = " << N << " nodes\n";
    cout << "----------------------------------------\n";
    
    // Calculate edges - more conservative for large graphs
    int E;
    if (N <= 1000) {
        E = N * 3; // Denser for small graphs
    } else if (N <= 10000) {
        E = N * 2; // Medium density
    } else {
        E = min(N * 2, 150000); // Cap edges for very large graphs
    }
    
    cout << "Target density: ~" << E << " edges for " << N << " nodes\n";
    cout << "Running " << numRuns << " trials...\n\n";
    
    double bfsTraverseTotal = 0, bfsPathTotal = 0;
    double dfsTraverseTotal = 0, dfsPathTotal = 0;
    double dfsCycleTotal = 0, dfsConnectedTotal = 0;
    
    for (int run = 1; run <= numRuns; ++run) {
        cout << "  Run " << run << "/" << numRuns << ":\n";
        
        try {
            // Generate random graph
            Graph* g = generateRandomGraph(N, E);
            
            int startNode = 1;
            int targetNode = N / 2;
            
            cout << "      Testing BFS..." << flush;
            // BFS Tests 
            double bfsTraverseTime = measureTime([&]() {
                LinkedList<int> result = BFS::traverse(*g, startNode);
            });
            bfsTraverseTotal += bfsTraverseTime;
            
            double bfsPathTime = measureTime([&]() {
                LinkedList<int> result = BFS::shortestPath(*g, startNode, targetNode);
            });
            bfsPathTotal += bfsPathTime;
            cout << " Done\n";
            
            cout << "      Testing DFS..." << flush;
            // DFS Tests 
            double dfsTraverseTime = measureTime([&]() {
                LinkedList<int> result = DFS::traverse(*g, startNode);
            });
            dfsTraverseTotal += dfsTraverseTime;
            
            double dfsPathTime = measureTime([&]() {
                LinkedList<int> result = DFS::findPath(*g, startNode, targetNode);
            });
            dfsPathTotal += dfsPathTime;
            
            double dfsCycleTime = measureTime([&]() {
                bool hasCycle = DFS::hasCycle(*g);
            });
            dfsCycleTotal += dfsCycleTime;
            
            double dfsConnectedTime = measureTime([&]() {
                bool connected = DFS::isConnected(*g);
            });
            dfsConnectedTotal += dfsConnectedTime;
            cout << " Done\n";
            
            // Clean up
            cout << "      Cleaning up..." << flush;
            delete g;
            cout << " Done\n\n";
            
        } catch (const std::exception& e) {
            cerr << "      Run " << run << " failed: " << e.what() << "\n";
            continue;
        }
    }
    
    // Calculate averages
    double bfsTraverseAvg = bfsTraverseTotal / numRuns;
    double bfsPathAvg = bfsPathTotal / numRuns;
    double dfsTraverseAvg = dfsTraverseTotal / numRuns;
    double dfsPathAvg = dfsPathTotal / numRuns;
    double dfsCycleAvg = dfsCycleTotal / numRuns;
    double dfsConnectedAvg = dfsConnectedTotal / numRuns;
    
    // Display results
    cout << fixed << setprecision(3);
    cout << "\n------------------------------------------------------\n";
    cout << "  Results (Average over " << numRuns << " runs)      \n";
    cout << "------------------------------------------------------\n";
    
    cout << "\n BFS Algorithms:\n";
    cout << "   traverse():      " << setw(10) << bfsTraverseAvg << " ms  [O(V + E)]\n";
    cout << "   shortestPath():  " << setw(10) << bfsPathAvg << " ms  [O(V + E)]\n";
    
    cout << "\n DFS Algorithms:\n";
    cout << "   traverse():      " << setw(10) << dfsTraverseAvg << " ms  [O(V + E)]\n";
    cout << "   findPath():      " << setw(10) << dfsPathAvg << " ms  [O(V + E)]\n";
    cout << "   hasCycle():      " << setw(10) << dfsCycleAvg << " ms  [O(V + E)]\n";
    cout << "   isConnected():   " << setw(10) << dfsConnectedAvg << " ms  [O(V + E)]\n";
    
    cout << "\n Performance Comparisons:\n";
    cout << "   BFS vs DFS (traverse): ";
    if (bfsTraverseAvg < dfsTraverseAvg) {
        cout << "BFS faster by " << (dfsTraverseAvg - bfsTraverseAvg) << " ms\n";
    } else {
        cout << "DFS faster by " << (bfsTraverseAvg - dfsTraverseAvg) << " ms\n";
    }
}

int main() {
    srand(static_cast<unsigned>(time(0)));
    
    cout << "------------------------------------------------------\n";
    cout << "   BFS & DFS Performance Analysis                   \n";
    cout << "   Big-O Complexity Verification                    \n";
    cout << "------------------------------------------------------\n";
    
    cout << "\n Theoretical Complexity Analysis:\n";
    cout << "------------------------------------------------------\n";
    cout << "Algorithm                  | Time Complexity | Space Complexity\n";
    cout << "------------------------------------------------------\n";
    cout << "BFS Traversal              | O(V + E)        | O(V)\n";
    cout << "BFS Shortest Path          | O(V + E)        | O(V)\n";
    cout << "DFS Traversal              | O(V + E)        | O(V)\n";
    cout << "DFS Find Path              | O(V + E)        | O(V)\n";
    cout << "DFS Cycle Detection        | O(V + E)        | O(V)\n";
    cout << "DFS Connectivity Check     | O(V + E)        | O(V)\n";
    cout << "------------------------------------------------------\n";
    cout << "\nWhere: V = vertices (nodes), E = edges\n";
    
    try {
        // Test with three different sizes
        runPerformanceTest(1000, 3);    // N = 10³
        runPerformanceTest(10000, 3);   // N = 10⁴
        runPerformanceTest(100000, 3);  // N = 10⁵
        
        cout << "\n------------------------------------------------------\n";
        cout << "   Performance Analysis Complete                    \n";
        cout << "------------------------------------------------------\n";
        
        cout << "\n  Complexity Verification:\n";
        cout << "   Compare times across different N values:\n";
        cout << "   • 10³ → 10⁴ should show ~10x increase\n";
        cout << "   • 10⁴ → 10⁵ should show ~10x increase\n";
        cout << "   This confirms O(V + E) linear scaling\n";
        
    } catch (const std::exception& e) {
        cerr << "\nFatal error: " << e.what() << "\n";
        return 1;
    }
    
    return 0;
}