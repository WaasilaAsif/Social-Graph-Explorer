#include "MutualFriends.h"

MutualFriends::MutualFriends(Graph* g) : graph(g) {}

LinkedList<int> MutualFriends::getMutualFriends(int userId1, int userId2) {
    LinkedList<int> mutualFriends;
    
    // Get friends of both users
    LinkedList<Edge>& friends1 = graph->getNeighbors(userId1);
    LinkedList<Edge>& friends2 = graph->getNeighbors(userId2);
    
    // Use HashMap for O(1) lookup
    HashMap<int, bool> friends2Map;
    for (int i = 0; i < friends2.size(); i++) {
        friends2Map.put(friends2[i].to, true);
    }
    
    // Find intersection
    for (int i = 0; i < friends1.size(); i++) {
        int friendId = friends1[i].to;
        if (friends2Map.contains(friendId)) {
            mutualFriends.append(friendId);
        }
    }
    
    return mutualFriends;
}

int MutualFriends::getMutualFriendsCount(int userId1, int userId2) {
    LinkedList<int> mutuals = getMutualFriends(userId1, userId2);
    return mutuals.size();
}

bool MutualFriends::hasMutualFriends(int userId1, int userId2) {
    LinkedList<Edge>& friends1 = graph->getNeighbors(userId1);
    LinkedList<Edge>& friends2 = graph->getNeighbors(userId2);
    
    // Use HashMap for efficient lookup
    HashMap<int, bool> friends2Map;
    for (int i = 0; i < friends2.size(); i++) {
        friends2Map.put(friends2[i].to, true);
    }
    
    // Check if any friend from user1 exists in user2's friends
    for (int i = 0; i < friends1.size(); i++) {
        if (friends2Map.contains(friends1[i].to)) {
            return true;
        }
    }
    
    return false;
}