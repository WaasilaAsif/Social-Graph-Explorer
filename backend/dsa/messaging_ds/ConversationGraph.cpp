#include "ConversationGraph.h"
using namespace std;

ConversationGraph::ConversationGraph() {}

void ConversationGraph::addInteraction(int userA, int userB) {
    // Ensure both users exist in adjacency list
    if (!adj.contains(userA)) {
        adj.put(userA, DynamicArray<Pair<int, int>>());
    }
    if (!adj.contains(userB)) {
        adj.put(userB, DynamicArray<Pair<int, int>>());
    }

    // Check if edge already exists and increment weight
    DynamicArray<Pair<int, int>>& neighborsA = adj.get(userA);
    bool foundA = false;
    for (int i = 0; i < neighborsA.size(); i++) {
        if (neighborsA.get(i).first == userB) {
            neighborsA.get(i).second++;
            foundA = true;
            break;
        }
    }
    if (!foundA) {
        neighborsA.push_back(Pair<int, int>(userB, 1));
    }

    // Add reverse edge for undirected graph
    DynamicArray<Pair<int, int>>& neighborsB = adj.get(userB);
    bool foundB = false;
    for (int i = 0; i < neighborsB.size(); i++) {
        if (neighborsB.get(i).first == userA) {
            neighborsB.get(i).second++;
            foundB = true;
            break;
        }
    }
    if (!foundB) {
        neighborsB.push_back(Pair<int, int>(userA, 1));
    }
}

DynamicArray<int> ConversationGraph::getNeighbors(int user) const {
    DynamicArray<int> neighbors;
    
    if (!adj.contains(user)) {
        return neighbors;
    }

    DynamicArray<Pair<int, int>> neighborList = adj.get(user);
    for (int i = 0; i < neighborList.size(); i++) {
        neighbors.push_back(neighborList.get(i).first);
    }

    return neighbors;
}

int ConversationGraph::getInteractionWeight(int userA, int userB) const {
    if (!adj.contains(userA)) {
        return 0;
    }

    DynamicArray<Pair<int, int>> neighbors = adj.get(userA);
    for (int i = 0; i < neighbors.size(); i++) {
        if (neighbors.get(i).first == userB) {
            return neighbors.get(i).second;
        }
    }

    return 0;
}

bool ConversationGraph::userExists(int user) const {
    return adj.contains(user);
}
