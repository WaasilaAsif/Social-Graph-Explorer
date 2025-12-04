#ifndef MESSAGEANALYTICS_H
#define MESSAGEANALYTICS_H
using namespace std;
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/utils/Pair.h"
#include <string>

class MessageAnalytics {
private:
    ConversationGraph graph;
    HashMap<string, int> userIdMap;  // Map string userIds to integer IDs
    HashMap<int, string> reverseMap;  // Map integer IDs back to string userIds
    int nextUserId;

    int getUserId(const string& userId);  // Helper to get or create user ID

public:
    MessageAnalytics();

    void addMessageInteraction(const string& senderId, const string& receiverId);
    DynamicArray<string> getMostActiveUsers(int k);
    int getInteractionCount(const string& userId1, const string& userId2);
};

#endif
