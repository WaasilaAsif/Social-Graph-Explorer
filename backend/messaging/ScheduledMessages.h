#ifndef SCHEDULEDMESSAGES_H
#define SCHEDULEDMESSAGES_H

#include "../dsa/messaging_ds/MsgHeap.h"
#include "Message.h"
#include "../dsa/containers/DynamicArray.h"

class ScheduledMessages {
private:
    MsgHeap heap; // Can be replaced with AVL/M-ary tree
    DynamicArray<Message> scheduled;

public:
    ScheduledMessages();

    void addScheduledMessage(const Message& msg, int priority);
    Message getNextMessage();
    void printAll();
};

#endif
