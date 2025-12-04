#pragma once
#include "../messaging/Message.h"
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/user/User.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/utils/Pair.h"

class MsgTopKMessages {
public:
    MsgTopKMessages(ConversationGraph* graph);
    DynamicArray<Pair<int, int>> getTopKInteractions(int userId, int k);

private:
    ConversationGraph* convGraph;
};
