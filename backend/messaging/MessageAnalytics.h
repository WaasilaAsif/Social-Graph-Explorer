#ifndef MESSAGEANALYTICS_H
#define MESSAGEANALYTICS_H

#include "ConversationGraph.h"
#include <string>
#include <vector>

class MessageAnalytics {
private:
    ConversationGraph graph;

public:
    MessageAnalytics();

    void addMessageInteraction(const std::string& senderId, const std::string& receiverId);
    std::vector<std::string> getMostActiveUsers(int k);
    int getInteractionCount(const std::string& userId1, const std::string& userId2);
};

#endif
