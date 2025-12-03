#ifndef JSONWRITER_H
#define JSONWRITER_H

#include <string>

class UserManager;
class Graph;
class MessageStore;

void saveUsersToJSON(const UserManager& userManager, const std::string& filepath);
void saveFriendshipsToJSON(const Graph& graph, const std::string& filepath);
void saveMessagesToJSON(const MessageStore& msgStore, const std::string& filepath);

#endif
