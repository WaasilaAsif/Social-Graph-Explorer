#ifndef TOPKCONVERSATIONS_H
#define TOPKCONVERSATIONS_H

#include "../dsa/messaging_ds/MsgHeap.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/HashMap.h"
#include <string>

class TopKConversations {
private:
    MsgHeap maxHeap;
    HashMap<int, std::string> idToUser;  // Map encoded value to userId
    int nextId;

public:
    TopKConversations();

    void addConversation(const std::string& userId, int interactionCount);
    DynamicArray<std::string> getTopK(int k);
};

#endif
