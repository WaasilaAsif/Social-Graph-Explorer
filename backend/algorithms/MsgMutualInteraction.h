#pragma once
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/user/User.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/utils/Pair.h"

class MsgMutualInteraction {
public:
    MsgMutualInteraction(ConversationGraph* graph);
    DynamicArray<Pair<int, int>> findMutualInteractions(int userId);

private:
    ConversationGraph* convGraph;
};
