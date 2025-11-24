#ifndef SCHEDULEDMESSAGES_H
#define SCHEDULEDMESSAGES_H

#include "./dsa/messaging_ds/MsgHeap.h"
#include "Message.h"
#include <vector>

class ScheduledMessages {
private:
    MsgHeap heap; // Can be replaced with AVL/M-ary tree
    std::vector<Message> scheduled;

public:
    ScheduledMessages();

    void addScheduledMessage(const Message& msg, int priority);
    Message getNextMessage();
    void printAll();
};

#endif
