#pragma once
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/user/User.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/Queue.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/utils/Pair.h"

class MsgShortestPath {
public:
    MsgShortestPath(ConversationGraph* graph);
    DynamicArray<int> findShortestPath(int srcId, int destId);

private:
    ConversationGraph* convGraph;
};
