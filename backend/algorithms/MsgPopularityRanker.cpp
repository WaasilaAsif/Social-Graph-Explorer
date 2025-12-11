#include "MsgPopularityRanker.h"

MsgPopularityRanker::MsgPopularityRanker(ConversationGraph* graph)
    : convGraph(graph) {}

DynamicArray<Pair<int, int>> MsgPopularityRanker::rankUsersByMessagePopularity(int topN) {
    DynamicArray<Pair<int, int>> rankings; // (userId, totalInteractions)
    
    // Get all users from the conversation graph
    DynamicArray<int> allUsers = convGraph->getAllUsers();
    
    // Build a list of (userId, totalInteractions)
    DynamicArray<Pair<int, int>> userScores;
    for (int i = 0; i < allUsers.size(); i++) {
        int userId = allUsers.get(i);
        int totalInteractions = convGraph->getTotalInteractions(userId);
        userScores.push_back(Pair<int, int>(userId, totalInteractions));
    }
    
    // Sort by interactions (descending) using simple bubble sort
    for (int i = 0; i < userScores.size() - 1; i++) {
        for (int j = 0; j < userScores.size() - i - 1; j++) {
            if (userScores.get(j).second < userScores.get(j + 1).second) {
                // Swap
                Pair<int, int> temp = userScores.get(j);
                userScores.get(j) = userScores.get(j + 1);
                userScores.get(j + 1) = temp;
            }
        }
    }
    
    // Take top N
    int count = (topN < userScores.size()) ? topN : userScores.size();
    for (int i = 0; i < count; i++) {
        rankings.push_back(userScores.get(i));
    }
    
    return rankings;
}
