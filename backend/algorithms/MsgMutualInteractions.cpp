#include "MsgMutualInteraction.h"
#include "../dsa/containers/HashMap.h"

MsgMutualInteraction::MsgMutualInteraction(ConversationGraph* graph)
    : convGraph(graph) {}

DynamicArray<Pair<int, int>> MsgMutualInteraction::findMutualInteractions(int userId) {
    DynamicArray<Pair<int, int>> mutualPairs;
    
    if (!convGraph->userExists(userId)) {
        return mutualPairs;
    }
    
    // Get all neighbors of the user
    DynamicArray<int> neighbors = convGraph->getNeighbors(userId);
    
    // For each neighbor, find mutual connections
    for (int i = 0; i < neighbors.size(); i++) {
        int neighborId = neighbors.get(i);
        DynamicArray<int> neighborNeighbors = convGraph->getNeighbors(neighborId);
        
        // Check if any of neighbor's neighbors are also user's neighbors
        for (int j = 0; j < neighborNeighbors.size(); j++) {
            int potentialMutual = neighborNeighbors.get(j);
            
            if (potentialMutual == userId) continue;
            
            // Check if potentialMutual is also a neighbor of userId
            bool isMutual = false;
            for (int k = 0; k < neighbors.size(); k++) {
                if (neighbors.get(k) == potentialMutual) {
                    isMutual = true;
                    break;
                }
            }
            
            if (isMutual) {
                mutualPairs.push_back(Pair<int, int>(neighborId, potentialMutual));
            }
        }
    }
    
    return mutualPairs;
}
