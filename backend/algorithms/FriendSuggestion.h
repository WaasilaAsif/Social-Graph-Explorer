#ifndef FRIENDSUGGESTION_H
#define FRIENDSUGGESTION_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/containers/LinkedList.h"
#include "MutualFriends.h"

struct Suggestion {
    int userId;
    int mutualFriendsCount;
    int frequencyScore;
    
    Suggestion() : userId(-1), mutualFriendsCount(0), frequencyScore(0) {}
    Suggestion(int id, int mutual, int freq) 
        : userId(id), mutualFriendsCount(mutual), frequencyScore(freq) {}
};

class FriendSuggestion {
private:
    Graph* graph;
    MutualFriends* mutualFriends;
    
    // Calculate frequency score for 2-hop suggestions
    HashMap<int, int> calculateFrequencyScores(int userId);
    
    // Get friends of friends (2-hop)
    LinkedList<int> getFriendsOfFriends(int userId);

public:
    FriendSuggestion(Graph* g, MutualFriends* mf);
    
    // Get friend suggestions for a user (sorted by relevance)
    LinkedList<Suggestion> getSuggestions(int userId, int maxSuggestions = 10);
    
    // Get suggestions based only on mutual friends
    LinkedList<Suggestion> getSuggestionsByMutualFriends(int userId, int maxSuggestions = 10);
    
    // Get all 2-hop friends (friends of friends)
    LinkedList<int> getTwoHopFriends(int userId);
    
    // Calculate suggestion score (combination of mutual friends and frequency)
    int calculateSuggestionScore(int userId, int candidateId);
};

#endif // FRIENDSUGGESTION_H