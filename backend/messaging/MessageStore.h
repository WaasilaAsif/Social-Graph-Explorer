#ifndef MESSAGESTORE_H
#define MESSAGESTORE_H

#include "Message.h"
#include "../dsa/containers/DynamicArray.h"
#include "../dsa/containers/HashMap.h"
#include <string>
#include <sstream>
#include <cctype>

class MessageStore {
private:
    DynamicArray<Message> messages;
    int nextId;

public:
    MessageStore();

    // Add a message and return its ID
    int addMessage(int senderId, int receiverId, const std::string& content);

    // Get a message by ID
    Message* getMessage(int messageId);

    // Extract words from text for indexing
    DynamicArray<std::string> extractWords(const std::string& text);

    // Get all messages
    const DynamicArray<Message>& getAllMessages() const;

    // Get messages count
    int getMessageCount() const;
};

#endif
