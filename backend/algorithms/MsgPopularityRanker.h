#pragma once
#include "../dsa/messaging_ds/ConversationGraph.h"
#include "../dsa/user/User.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/HashMap.h"
#include "../dsa/utils/Pair.h"

class MsgPopularityRanker {
public:
    MsgPopularityRanker(ConversationGraph* graph);
    DynamicArray<Pair<int, int>> rankUsersByMessagePopularity(int topN);

private:
    ConversationGraph* convGraph;
};
