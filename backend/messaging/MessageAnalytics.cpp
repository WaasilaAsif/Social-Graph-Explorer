#include "MessageAnalytics.h"
#include "../dsa/messaging_ds/MsgHeap.h"

MessageAnalytics::MessageAnalytics() : nextUserId(0) {}

int MessageAnalytics::getUserId(const string& userId) {
    if (!userIdMap.contains(userId)) {
        int id = nextUserId++;
        userIdMap.put(userId, id);
        reverseMap.put(id, userId);
        return id;
    }
    return userIdMap.get(userId);
}

void MessageAnalytics::addMessageInteraction(const string& senderId, const string& receiverId) {
    // Map string IDs to integers
    int senderIntId = getUserId(senderId);
    int receiverIntId = getUserId(receiverId);
    
    // Add interaction to conversation graph
    graph.addInteraction(senderIntId, receiverIntId);
}

DynamicArray<string> MessageAnalytics::getMostActiveUsers(int k) {
    // Create a max heap to get top-k users by activity (degree)
    MsgHeap maxHeap(false);  // false = max heap
    
    // Store pairs of (activity_count, userId) for sorting
    DynamicArray<Pair<int, int>> userActivity;
    
    // Iterate through all users and count their activity
    userIdMap.forEach([&](const string& userId, int intId) {
        if (graph.userExists(intId)) {
            int activityCount = graph.getNeighbors(intId).size();
            userActivity.push_back(Pair<int, int>(activityCount, intId));
        }
    });
    
    // Push all activities into max heap
    for (int i = 0; i < userActivity.size(); i++) {
        // Push activity count (we'll track users separately)
        maxHeap.push(userActivity.get(i).first * 1000 + userActivity.get(i).second);
    }
    
    // Extract top k users
    DynamicArray<string> topUsers;
    int count = 0;
    while (count < k && !maxHeap.isEmpty()) {
        int value;
        if (maxHeap.pop(value)) {
            int userId = value % 1000;
            if (reverseMap.contains(userId)) {
                topUsers.push_back(reverseMap.get(userId));
                count++;
            }
        }
    }
    
    return topUsers;
}

int MessageAnalytics::getInteractionCount(const string& userId1, const string& userId2) {
    // Check if users exist in the map
    if (!userIdMap.contains(userId1) || !userIdMap.contains(userId2)) {
        return 0;
    }
    
    int id1 = userIdMap.get(userId1);
    int id2 = userIdMap.get(userId2);
    
    // Get interaction weight from graph
    return graph.getInteractionWeight(id1, id2);
}
