#include "MessagingSystem.h"
#include <iostream>
#include "./dsa/messaging_ds/MsgTrie.h"
MessagingSystem::MessagingSystem() {}

void MessagingSystem::addMessage(const Message& msg) {
    // TODO: Add to messages vector
    // TODO: Insert into MsgTrie
    // TODO: Push to undo stack
}

std::vector<int> MessagingSystem::searchMessages(const std::string& keyword) {
    // TODO: Use MsgTrie to find message IDs
    return msgTrie.search(keyword);
}

void MessagingSystem::undoLastAction() {
    // TODO: Pop from undo stack and revert changes
}

void MessagingSystem::scheduleMessage(const Message& msg, int priority) {
    // TODO: Add to scheduledHeap or AVL tree
}

void MessagingSystem::printScheduledMessages() {
    // TODO: Print messages in scheduled order
}
