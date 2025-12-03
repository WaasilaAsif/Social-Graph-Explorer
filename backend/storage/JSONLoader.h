#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <string>

class UserManager;
class Graph;
class MessageStore;
class MsgTrie;
class ConversationGraph;

void loadUsersFromJSON(UserManager& userManager, const std::string& filepath);
void loadFriendshipsFromJSON(Graph& graph, const std::string& filepath);
void loadMessagesFromJSON(MessageStore& msgStore, MsgTrie& msgTrie, ConversationGraph& convGraph, const std::string& filepath);

#endif
