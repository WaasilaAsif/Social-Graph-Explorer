#ifndef MUTUALFRIENDS_H
#define MUTUALFRIENDS_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/LinkedList.h"

class MutualFriends {
private:
    Graph* graph;

public:
    MutualFriends(Graph* g);
    
    // Get list of mutual friends between two users
    LinkedList<int> getMutualFriends(int userId1, int userId2);
    
    // Get count of mutual friends
    int getMutualFriendsCount(int userId1, int userId2);
    
    // Check if two users have any mutual friends
    bool hasMutualFriends(int userId1, int userId2);
};

#endif // MUTUALFRIENDS_H