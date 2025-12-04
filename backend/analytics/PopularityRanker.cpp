#include "PopularityRanker.h"

PopularityRanker::PopularityRanker(Graph* g) : graph(g) {}

int PopularityRanker::calculatePopularityScore(int userId) {
    // Basic popularity = number of friends
    return graph->getNeighbors(userId).size();
}

LinkedList<UserScore> PopularityRanker::getTopNPopularUsers(int n) {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    PriorityQueue<UserScore> maxHeap;
    
    // Insert all users into max-heap
    for (int i = 0; i < allUsers.size(); i++) {
        int score = calculatePopularityScore(allUsers[i]);
        maxHeap.insert(UserScore(allUsers[i], score));
    }
    
    // Extract top N
    LinkedList<UserScore> topUsers;
    int count = (n < allUsers.size()) ? n : allUsers.size();
    
    for (int i = 0; i < count && !maxHeap.isEmpty(); i++) {
        topUsers.append(maxHeap.extractMax());
    }
    
    return topUsers;
}

LinkedList<UserScore> PopularityRanker::getAllUsersRanked() {
    LinkedList<int> allUsers = graph->getAllNodeIDs();
    PriorityQueue<UserScore> maxHeap;
    
    for (int i = 0; i < allUsers.size(); i++) {
        int score = calculatePopularityScore(allUsers[i]);
        maxHeap.insert(UserScore(allUsers[i], score));
    }
    
    LinkedList<UserScore> rankedUsers;
    while (!maxHeap.isEmpty()) {
        rankedUsers.append(maxHeap.extractMax());
    }
    
    return rankedUsers;
}

int PopularityRanker::getUserRank(int userId) {
    LinkedList<UserScore> allRanked = getAllUsersRanked();
    
    for (int i = 0; i < allRanked.size(); i++) {
        if (allRanked[i].userId == userId) {
            return i + 1; // Rank starts at 1
        }
    }
    
    return -1; // User not found
}

int PopularityRanker::getPopularityScore(int userId) {
    return calculatePopularityScore(userId);
}

double PopularityRanker::getPercentileRank(int userId) {
    int rank = getUserRank(userId);
    if (rank == -1) return -1.0;
    
    int totalUsers = graph->nodeCount();
    if (totalUsers == 0) return 0.0;
    
    // Higher percentile = more popular
    return ((double)(totalUsers - rank + 1) / totalUsers) * 100.0;
}