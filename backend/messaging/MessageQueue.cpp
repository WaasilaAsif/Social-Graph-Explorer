#include "MessageQueue.h"

MessageQueue::MessageQueue() {}

void MessageQueue::enqueue(const Message& msg) {
    // TODO: add message to the end of the queue
}

Message MessageQueue::dequeue() {
    // TODO: remove message from front of queue and return
    return Message();
}

bool MessageQueue::isEmpty() const {
    return queue.empty();
}

int MessageQueue::size() const {
    return queue.size();
}
