#include "MsgAPI.h"
#include <sstream>
#include "../../storage/JSONWriter.h"

MsgAPI::MsgAPI(UserManager* userManager,
               MessageStore* msgStore,
               MsgTrie* trie,
               ConversationGraph* graph)
    : userManager(userManager), store(msgStore), trie(trie), graph(graph) {}


// ---------------------------------------------------
// 1. SEND MESSAGE
// ---------------------------------------------------
std::string MsgAPI::handleSendMessage(const std::unordered_map<std::string, std::string>& params) {
    int sender = stoi(params.at("senderId"));
    int receiver = stoi(params.at("receiverId"));
    std::string text = params.at("text");

    int msgId = store->addMessage(sender, receiver, text);

    // Add to trie keywords
    auto words = store->extractWords(text);
    for (int i = 0; i < words.size(); i++) {
        trie->insert(words.get(i), msgId);
    }

    // Add to graph
    graph->addInteraction(sender, receiver);

    // Save to JSON database
    saveMessagesToJSON(*store, "storage/local_db/messages.json");

    std::ostringstream out;
    out << "{ \"status\": \"success\", \"messageId\": " << msgId << " }";
    return out.str();
}


// ---------------------------------------------------
// 2. FULL WORD SEARCH
// ---------------------------------------------------
std::string MsgAPI::handleSearchWord(const std::unordered_map<std::string, std::string>& params) {
    auto results = trie->search(params.at("query"));

    std::ostringstream out;
    out << "{ \"results\": [";
    for (int i = 0; i < results.size(); i++) {
        out << results.get(i);
        if (i + 1 < results.size()) out << ",";
    }
    out << "] }";
    return out.str();
}


// ---------------------------------------------------
// 3. PREFIX SEARCH
// ---------------------------------------------------
std::string MsgAPI::handleSearchPrefix(const std::unordered_map<std::string, std::string>& params) {
    auto results = trie->startsWith(params.at("query"));

    std::ostringstream out;
    out << "{ \"results\": [";
    for (int i = 0; i < results.size(); i++) {
        out << results.get(i);
        if (i + 1 < results.size()) out << ",";
    }
    out << "] }";
    return out.str();
}


// ---------------------------------------------------
// 4. TOP K MESSAGES
// ---------------------------------------------------
std::string MsgAPI::handleTopK(const std::unordered_map<std::string, std::string>& params) {
    int userId = stoi(params.at("user"));
    int k = stoi(params.at("k"));

    MsgTopKMessages algo(graph);
    auto result = algo.getTopKInteractions(userId, k);

    std::ostringstream out;
    out << "{ \"messages\": [";
    for (int i = 0; i < result.size(); i++) {
        out << "{ \"userId\": " << result.get(i).first 
            << ", \"weight\": " << result.get(i).second << " }";
        if (i + 1 < result.size()) out << ",";
    }
    out << "] }";

    return out.str();
}


// ---------------------------------------------------
// 5. FRIEND SUGGESTION
// ---------------------------------------------------
std::string MsgAPI::handleFriendSuggestion(const std::unordered_map<std::string, std::string>& params) {
    int userId = stoi(params.at("user"));
    int k = stoi(params.at("k"));

    MsgFriendSuggestion algo(graph);
    auto suggestions = algo.suggestFriends(userId, k);

    std::ostringstream out;
    out << "{ \"friends\": [";
    for (int i = 0; i < suggestions.size(); i++) {
        out << suggestions.get(i);
        if (i + 1 < suggestions.size()) out << ",";
    }
    out << "] }";

    return out.str();
}


// ---------------------------------------------------
// 6. MUTUAL INTERACTIONS
// ---------------------------------------------------
std::string MsgAPI::handleMutualInteractions(const std::unordered_map<std::string, std::string>& params) {
    int userId = stoi(params.at("user"));

    MsgMutualInteraction algo(graph);
    auto list = algo.findMutualInteractions(userId);

    std::ostringstream out;
    out << "{ \"mutual\": [ ";
    for (int i = 0; i < list.size(); i++) {
        out << "{ \"u1\": " << list.get(i).first << ", \"u2\": " << list.get(i).second << " }";
        if (i + 1 < list.size()) out << ",";
    }
    out << "] }";
    return out.str();
}


// ---------------------------------------------------
// 7. POPULARITY RANK
// ---------------------------------------------------
std::string MsgAPI::handleRank(const std::unordered_map<std::string, std::string>& params) {
    int top = stoi(params.at("top"));

    MsgPopularityRanker algo(graph);
    auto list = algo.rankUsersByMessagePopularity(top);

    std::ostringstream out;
    out << "{ \"rank\": [";
    for (int i = 0; i < list.size(); i++) {
        out << "{ \"userId\": " << list.get(i).first 
            << ", \"popularity\": " << list.get(i).second << " }";
        if (i + 1 < list.size()) out << ",";
    }
    out << "] }";

    return out.str();
}


// ---------------------------------------------------
// 8. SHORTEST PATH
// ---------------------------------------------------
std::string MsgAPI::handleShortestPath(const std::unordered_map<std::string, std::string>& params) {
    int src = stoi(params.at("src"));
    int dest = stoi(params.at("dest"));

    MsgShortestPath algo(graph);
    auto path = algo.findShortestPath(src, dest);

    std::ostringstream out;
    out << "{ \"path\": [";
    for (int i = 0; i < path.size(); i++) {
        out << path.get(i);
        if (i + 1 < path.size()) out << ",";
    }
    out << "] }";

    return out.str();
}
