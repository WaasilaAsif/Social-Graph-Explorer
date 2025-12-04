#include "TopKConversations.h"
using namespace std;

TopKConversations::TopKConversations() : maxHeap(false), nextId(0) {}  // false = max heap

void TopKConversations::addConversation(const string& userId, int interactionCount) {
    // Encode: interactionCount * 10000 + id to store both in heap
    int id = nextId++;
    int encodedValue = interactionCount * 10000 + id;
    
    // Store userId mapping
    idToUser.put(id, userId);
    
    // Add to max heap
    maxHeap.push(encodedValue);
}

DynamicArray<string> TopKConversations::getTopK(int k) {
    DynamicArray<string> topUsers;
    DynamicArray<int> tempValues;  // Store popped values to restore heap
    
    // Pop top k elements
    int count = 0;
    while (count < k && !maxHeap.isEmpty()) {
        int value;
        if (maxHeap.pop(value)) {
            tempValues.push_back(value);
            
            // Decode to get id
            int id = value % 10000;
            
            // Get userId from map
            if (idToUser.contains(id)) {
                topUsers.push_back(idToUser.get(id));
            }
            count++;
        }
    }
    
    // Restore heap by pushing back the popped values
    for (int i = 0; i < tempValues.size(); i++) {
        maxHeap.push(tempValues.get(i));
    }
    
    return topUsers;
}
