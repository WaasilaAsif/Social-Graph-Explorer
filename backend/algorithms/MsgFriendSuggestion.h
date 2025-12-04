#pragma once
#include "../messaging/Message.h"
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/user/User.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/utils/Pair.h"

class MsgFriendSuggestion {
public:
    MsgFriendSuggestion(ConversationGraph* graph);
    DynamicArray<int> suggestFriends(int userId, int k);

private:
    ConversationGraph* convGraph;
};
