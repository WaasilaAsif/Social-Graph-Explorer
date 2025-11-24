#include "MessageAnalytics.h"

MessageAnalytics::MessageAnalytics() {}

void MessageAnalytics::addMessageInteraction(const std::string& senderId, const std::string& receiverId) {
    // TODO: update ConversationGraph edges
}

std::vector<std::string> MessageAnalytics::getMostActiveUsers(int k) {
    // TODO: use BFS/DFS or heap to return top-k active users
    return {};
}

int MessageAnalytics::getInteractionCount(const std::string& userId1, const std::string& userId2) {
    // TODO: return the weight of edge in ConversationGraph
    return 0;
}
