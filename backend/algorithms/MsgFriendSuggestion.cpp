#include "MsgFriendSuggestion.h"

MsgFriendSuggestion::MsgFriendSuggestion(ConversationGraph* graph)
    : convGraph(graph) {}

DynamicArray<int> MsgFriendSuggestion::suggestFriends(int userId, int k) {
    DynamicArray<int> suggestions;
    
    if (!convGraph->userExists(userId) || k <= 0) {
        return suggestions;
    }
    
    // Get direct neighbors (already connected users)
    DynamicArray<int> neighbors = convGraph->getNeighbors(userId);
    
    // Map to count mutual connections: friendId -> count
    HashMap<int, int> mutualCounts;
    
    // For each neighbor, check their neighbors (friends of friends)
    for (int i = 0; i < neighbors.size(); i++) {
        int neighborId = neighbors.get(i);
        DynamicArray<int> neighborNeighbors = convGraph->getNeighbors(neighborId);
        
        for (int j = 0; j < neighborNeighbors.size(); j++) {
            int candidate = neighborNeighbors.get(j);
            
            // Skip self and existing neighbors
            if (candidate == userId) continue;
            
            bool isExistingNeighbor = false;
            for (int k = 0; k < neighbors.size(); k++) {
                if (neighbors.get(k) == candidate) {
                    isExistingNeighbor = true;
                    break;
                }
            }
            
            if (!isExistingNeighbor) {
                // Count mutual connections
                if (mutualCounts.contains(candidate)) {
                    int count = mutualCounts.get(candidate);
                    mutualCounts.put(candidate, count + 1);
                } else {
                    mutualCounts.put(candidate, 1);
                }
            }
        }
    }
    
    // Convert to array of pairs for sorting
    DynamicArray<Pair<int, int>> candidates; // (userId, mutualCount)
    mutualCounts.forEach([&candidates](const int& key, const int& value) {
        candidates.push_back(Pair<int, int>(key, value));
    });
    
    // Simple selection sort by mutual count (descending)
    for (int i = 0; i < candidates.size() && i < k; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < candidates.size(); j++) {
            if (candidates.get(j).second > candidates.get(maxIdx).second) {
                maxIdx = j;
            }
        }
        if (maxIdx != i) {
            Pair<int, int> temp = candidates.get(i);
            candidates.removeAt(i);
            candidates.push_back(temp);
        }
    }
    
    // Take top k suggestions
    for (int i = 0; i < candidates.size() && i < k; i++) {
        suggestions.push_back(candidates.get(i).first);
    }
    
    return suggestions;
}
