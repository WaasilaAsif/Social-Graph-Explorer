#include "MessageStore.h"
#include <algorithm>

MessageStore::MessageStore() : nextId(1) {}

int MessageStore::addMessage(int senderId, int receiverId, const std::string& content) {
    Message msg;
    msg.id = std::to_string(nextId);
    msg.senderId = std::to_string(senderId);
    msg.receiverId = std::to_string(receiverId);
    msg.content = content;
    msg.timestamp = nextId; // Simple timestamp using ID
    msg.delivered = true;
    msg.read = false;

    messages.push_back(msg);
    return nextId++;
}

Message* MessageStore::getMessage(int messageId) {
    for (int i = 0; i < messages.size(); i++) {
        if (std::stoi(messages.get(i).id) == messageId) {
            // Return pointer to the message in the array
            // Note: This is unsafe if array resizes, but works for demonstration
            return const_cast<Message*>(&messages.get(i));
        }
    }
    return nullptr;
}

DynamicArray<std::string> MessageStore::extractWords(const std::string& text) {
    DynamicArray<std::string> words;
    std::stringstream ss(text);
    std::string word;

    while (ss >> word) {
        // Convert to lowercase and remove punctuation
        std::string cleanWord;
        for (char c : word) {
            if (std::isalnum(c)) {
                cleanWord += std::tolower(c);
            }
        }
        
        if (!cleanWord.empty()) {
            words.push_back(cleanWord);
        }
    }

    return words;
}

const DynamicArray<Message>& MessageStore::getAllMessages() const {
    return messages;
}

int MessageStore::getMessageCount() const {
    return messages.size();
}
