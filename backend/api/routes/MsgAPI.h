#pragma once

#include "../../dsa/user/UserManager.h"
#include "../../messaging/MessageStore.h"
#include "../../dsa/messaging_ds/MsgTrie.h"
#include "../../dsa/messaging_ds/ConversationGraph.h"
#include "../../libs/project_headers/MsgTopKMessages.h"
#include "../../libs/project_headers/MsgFriendSuggestion.h"
#include "../../libs/project_headers/MsgMutualInteraction.h"
#include "../../libs/project_headers/MsgPopularityRanker.h"
#include "../../libs/project_headers/MsgShortestPath.h"

#include <string>
#include <unordered_map>

class MsgAPI {
public:
    MsgAPI(
        UserManager* userManager,
        MessageStore* msgStore,
        MsgTrie* trie,
        ConversationGraph* graph
    );

    std::string handleSendMessage(const std::unordered_map<std::string, std::string>& params);
    std::string handleSearchWord(const std::unordered_map<std::string, std::string>& params);
    std::string handleSearchPrefix(const std::unordered_map<std::string, std::string>& params);
    std::string handleTopK(const std::unordered_map<std::string, std::string>& params);
    std::string handleFriendSuggestion(const std::unordered_map<std::string, std::string>& params);
    std::string handleMutualInteractions(const std::unordered_map<std::string, std::string>& params);
    std::string handleRank(const std::unordered_map<std::string, std::string>& params);
    std::string handleShortestPath(const std::unordered_map<std::string, std::string>& params);

private:
    UserManager* userManager;
    MessageStore* store;
    MsgTrie* trie;
    ConversationGraph* graph;
};
