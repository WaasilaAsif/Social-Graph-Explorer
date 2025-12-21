// TopKConversationsLiveSimulation.cpp
// Test script for measuring Top K conversations retrieval under live updates

#include "../../messaging/TopKConversations.h"
#include <iostream>
#include <chrono>
#include <string>
#include <vector>
#include <random>

using namespace std;
using namespace chrono;

// Generate random user ID
string randomUserId(int length) {
    static const char charset[] = "abcdefghijklmnopqrstuvwxyz0123456789";
    static random_device rd;
    static mt19937 gen(rd());
    static uniform_int_distribution<> dis(0, 35);
    string userId;
    for (int i = 0; i < length; ++i) {
        userId += charset[dis(gen)];
    }
    return userId;
}

void simulateLiveTopK(int numUsers, int k, int numQueries) {
    TopKConversations topK;
    vector<string> userIds;

    // Step 1: Add initial users with random interaction counts
    for (int i = 0; i < numUsers; ++i) {
        string userId = randomUserId(8);
        userIds.push_back(userId);
        int interactionCount = rand() % 10000;
        topK.addConversation(userId, interactionCount);
    }

    cout << "\nSimulating Top-" << k << " queries for " << numUsers << " users:\n";

    // Step 2: Perform multiple live Top-K queries
    for (int q = 0; q < numQueries; ++q) {
        // Optionally, update random user's interaction count
        int randomIndex = rand() % numUsers;
        int additionalInteractions = rand() % 1000;
        topK.addConversation(userIds[randomIndex], additionalInteractions);

        // Measure Top-K retrieval
        auto start = high_resolution_clock::now();
        auto result = topK.getTopK(k);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(end - start);

        cout << "Query " << (q + 1) << ": Top-" << k
             << " retrieved in " << duration.count() << " ms." << endl;
    }
}

int main() {
    cout << "Testing live Top-K conversations complexity...\n";

    simulateLiveTopK(1000, 10, 5);     // 5 live queries
    simulateLiveTopK(10000, 10, 5);    // 5 live queries
    simulateLiveTopK(100000, 10, 5);   // 5 live queries

    return 0;
}
