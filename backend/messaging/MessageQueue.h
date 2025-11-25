#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "Message.h"
#include "../dsa/containers/DynamicArray.h"
//#include "../dsa/containers/Queue.h"

class MessageQueue {
private:
    DynamicArray<Message> queue;

public:
    MessageQueue();

    void enqueue(const Message& msg);
    Message dequeue();
    bool isEmpty() const;
    int size() const;
};

#endif
