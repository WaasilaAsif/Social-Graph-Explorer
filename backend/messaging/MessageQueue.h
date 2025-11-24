#ifndef MESSAGEQUEUE_H
#define MESSAGEQUEUE_H

#include "Message.h"
#include <vector>

class MessageQueue {
private:
    std::vector<Message> queue;

public:
    MessageQueue();

    void enqueue(const Message& msg);
    Message dequeue();
    bool isEmpty() const;
    int size() const;
};

#endif
