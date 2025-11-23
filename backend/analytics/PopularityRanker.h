#ifndef POPULARITYRANKER_H
#define POPULARITYRANKER_H

#include "../dsa/graph/Graph.h"
#include "../dsa/containers/PriorityQueue.h"
#include "../dsa/containers/LinkedList.h"

struct UserScore {
    int userId;
    int score;
    
    // Constructor
    UserScore() : userId(-1), score(0) {}
    UserScore(int id, int s) : userId(id), score(s) {}
    
    // Comparison operators for max-heap
    bool operator>(const UserScore& other) const {
        return score > other.score;
    }
    
    bool operator<(const UserScore& other) const {
        return score < other.score;
    }
};

class PopularityRanker {
private:
    Graph* graph;
    
    // Calculate popularity score for a user
    int calculatePopularityScore(int userId);

public:
    PopularityRanker(Graph* g);
    
    // Get top N most popular users
    LinkedList<UserScore> getTopNPopularUsers(int n);
    
    // Get all users ranked by popularity
    LinkedList<UserScore> getAllUsersRanked();
    
    // Get popularity rank of specific user (1 = most popular)
    int getUserRank(int userId);
    
    // Get popularity score of user
    int getPopularityScore(int userId);
    
    // Get percentile rank (0-100)
    double getPercentileRank(int userId);
};

#endif // POPULARITYRANKER_H