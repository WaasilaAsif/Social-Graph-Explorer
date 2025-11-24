#ifndef MESSAGINGSYSTEM_H
#define MESSAGINGSYSTEM_H

#include "./dsa/messaging_ds/MsgTrie.h"
#include "./dsa/messaging_ds/MsgStack.h"
#include "./dsa/messaging_ds/MsgHeap.h"
#include "./messaging/Message.h"
#include <vector>

class MessagingSystem {
private:
    MsgTrie msgTrie;
    MsgStack undoStack;
    MsgHeap scheduledHeap; // Or AVL/Tree for scheduling
    std::vector<Message> messages;

public:
    MessagingSystem();

    void addMessage(const Message& msg);
    std::vector<int> searchMessages(const std::string& keyword);
    void undoLastAction();
    void scheduleMessage(const Message& msg, int priority);

    // Optional tree-based feature
    void printScheduledMessages();
};

#endif
