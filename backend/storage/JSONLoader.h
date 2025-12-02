#ifndef JSONLOADER_H
#define JSONLOADER_H

#include <string>

class UserManager;
class Graph;
class MessageStore;

void loadUsersFromJSON(UserManager& userManager, const std::string& filepath);
void loadFriendshipsFromJSON(Graph& graph, const std::string& filepath);
void loadMessagesFromJSON(MessageStore& msgStore, const std::string& filepath);

#endif
