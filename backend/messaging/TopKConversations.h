#ifndef TOPKCONVERSATIONS_H
#define TOPKCONVERSATIONS_H

#include "MsgHeap.h"
#include <vector>
#include <string>

class TopKConversations {
private:
    MsgHeap maxHeap;

public:
    TopKConversations();

    void addConversation(const std::string& userId, int interactionCount);
    std::vector<std::string> getTopK(int k);
};

#endif
