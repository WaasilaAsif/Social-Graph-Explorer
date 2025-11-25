#ifndef TOPKCONVERSATIONS_H
#define TOPKCONVERSATIONS_H

#include "MsgHeap.h"
#include "../dsa/containers/DynamicArray.h"
#include <string>

class TopKConversations {
private:
    MsgHeap maxHeap;

public:
    TopKConversations();

    void addConversation(const std::string& userId, int interactionCount);
    DynamicArray<std::string> getTopK(int k);
};

#endif
