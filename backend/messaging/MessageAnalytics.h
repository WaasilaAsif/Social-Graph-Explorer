#ifndef MESSAGEANALYTICS_H
#define MESSAGEANALYTICS_H

#include "ConversationGraph.h"
#include "../dsa/containers/DynamicArray.h"
#include <string>

class MessageAnalytics {
private:
    ConversationGraph graph;

public:
    MessageAnalytics();

    void addMessageInteraction(const std::string& senderId, const std::string& receiverId);
    DynamicArray<std::string> getMostActiveUsers(int k);
    int getInteractionCount(const std::string& userId1, const std::string& userId2);
};

#endif
