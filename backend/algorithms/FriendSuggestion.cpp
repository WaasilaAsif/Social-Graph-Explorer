#include "FriendSuggestion.h"

FriendSuggestion::FriendSuggestion(Graph* g, MutualFriends* mf) 
    : graph(g), mutualFriends(mf) {}

LinkedList<int> FriendSuggestion::getFriendsOfFriends(int userId) {
    LinkedList<int> friendsOfFriends;
    HashMap<int, bool> seen;
    
    // Mark user and their direct friends
    seen.put(userId, true);
    LinkedList<Edge>& directFriends = graph->getNeighbors(userId);
    
    for (int i = 0; i < directFriends.size(); i++) {
        seen.put(directFriends[i].to, true);
    }
    
    // Get friends of each friend
    for (int i = 0; i < directFriends.size(); i++) {
        int friendId = directFriends[i].to;
        LinkedList<Edge>& secondHop = graph->getNeighbors(friendId);
        
        for (int j = 0; j < secondHop.size(); j++) {
            int potentialFriend = secondHop[j].to;
            if (!seen.contains(potentialFriend)) {
                friendsOfFriends.append(potentialFriend);
                seen.put(potentialFriend, true);
            }
        }
    }
    
    return friendsOfFriends;
}

HashMap<int, int> FriendSuggestion::calculateFrequencyScores(int userId) {
    HashMap<int, int> frequencyMap;
    
    LinkedList<Edge>& directFriends = graph->getNeighbors(userId);
    
    // Count how many mutual friends each candidate has
    for (int i = 0; i < directFriends.size(); i++) {
        int friendId = directFriends[i].to;
        LinkedList<Edge>& secondHop = graph->getNeighbors(friendId);
        
        for (int j = 0; j < secondHop.size(); j++) {
            int candidate = secondHop[j].to;
            
            // Skip if it's the user or already a friend
            if (candidate == userId) continue;
            
            bool isDirectFriend = false;
            for (int k = 0; k < directFriends.size(); k++) {
                if (directFriends[k].to == candidate) {
                    isDirectFriend = true;
                    break;
                }
            }
            
            if (!isDirectFriend) {
                if (frequencyMap.contains(candidate)) {
                    int current = frequencyMap.get(candidate);
                    frequencyMap.put(candidate, current + 1);
                } else {
                    frequencyMap.put(candidate, 1);
                }
            }
        }
    }
    
    return frequencyMap;
}

LinkedList<Suggestion> FriendSuggestion::getSuggestions(int userId, int maxSuggestions) {
    HashMap<int, int> frequencyScores = calculateFrequencyScores(userId);
    LinkedList<Suggestion> suggestions;
    
    // Get all candidates from frequency map
    LinkedList<int> candidates = getFriendsOfFriends(userId);
    
    for (int i = 0; i < candidates.size(); i++) {
        int candidateId = candidates[i];
        if (frequencyScores.contains(candidateId)) {
            int frequency = frequencyScores.get(candidateId);
            int mutualCount = mutualFriends->getMutualFriendsCount(userId, candidateId);
            
            suggestions.append(Suggestion(candidateId, mutualCount, frequency));
        }
    }
    
    // Simple selection sort by frequency score (descending)
    for (int i = 0; i < suggestions.size() - 1; i++) {
        int maxIdx = i;
        for (int j = i + 1; j < suggestions.size(); j++) {
            if (suggestions[j].frequencyScore > suggestions[maxIdx].frequencyScore ||
                (suggestions[j].frequencyScore == suggestions[maxIdx].frequencyScore &&
                 suggestions[j].mutualFriendsCount > suggestions[maxIdx].mutualFriendsCount)) {
                maxIdx = j;
            }
        }
        
        // Swap
        Suggestion temp = suggestions[i];
        suggestions[i] = suggestions[maxIdx];
        suggestions[maxIdx] = temp;
    }
    
    // Return top N suggestions
    if (suggestions.size() > maxSuggestions) {
        LinkedList<Suggestion> topSuggestions;
        for (int i = 0; i < maxSuggestions; i++) {
            topSuggestions.append(suggestions[i]);
        }
        return topSuggestions;
    }
    
    return suggestions;
}

LinkedList<int> FriendSuggestion::getTwoHopFriends(int userId) {
    return getFriendsOfFriends(userId);
}

int FriendSuggestion::calculateSuggestionScore(int userId, int candidateId) {
    int mutualCount = mutualFriends->getMutualFriendsCount(userId, candidateId);
    HashMap<int, int> frequencyScores = calculateFrequencyScores(userId);
    
    int frequency = 0;
    if (frequencyScores.contains(candidateId)) {
        frequency = frequencyScores.get(candidateId);
    }
    
    // Weighted score: mutual friends weighted higher
    return (mutualCount * 3) + frequency;
}