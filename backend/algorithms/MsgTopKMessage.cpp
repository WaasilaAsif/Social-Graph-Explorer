#include "MsgTopKMessages.h"

MsgTopKMessages::MsgTopKMessages(ConversationGraph* graph)
    : convGraph(graph) {}

DynamicArray<Pair<int, int>> MsgTopKMessages::getTopKInteractions(int userId, int k) {
    DynamicArray<Pair<int, int>> topK; // (neighborId, interactionWeight)
    
    if (!convGraph->userExists(userId) || k <= 0) {
        return topK;
    }
    
    // Get all neighbors and their interaction weights
    DynamicArray<int> neighbors = convGraph->getNeighbors(userId);
    DynamicArray<Pair<int, int>> interactions;
    
    for (int i = 0; i < neighbors.size(); i++) {
        int neighborId = neighbors.get(i);
        int weight = convGraph->getInteractionWeight(userId, neighborId);
        interactions.push_back(Pair<int, int>(neighborId, weight));
    }
    
    // Sort by weight (descending) using selection sort
    for (int i = 0; i < interactions.size() && i < k; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < interactions.size(); j++) {
            if (interactions.get(j).second > interactions.get(maxIdx).second) {
                maxIdx = j;
            }
        }
        
        // Swap
        if (maxIdx != i) {
            Pair<int, int> temp = interactions.get(i);
            Pair<int, int> maxItem = interactions.get(maxIdx);
            
            // Manual swap since we don't have direct array access
            interactions.removeAt(i);
            interactions.push_back(maxItem);
            interactions.removeAt(maxIdx);
            interactions.push_back(temp);
        }
    }
    
    // Take top k
    for (int i = 0; i < interactions.size() && i < k; i++) {
        topK.push_back(interactions.get(i));
    }
    
    return topK;
}
