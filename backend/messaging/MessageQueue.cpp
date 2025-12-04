#include "MessageQueue.h"

MessageQueue::MessageQueue() {}

void MessageQueue::enqueue(const Message& msg) {
    // Add message to the end of the queue
    queue.push_back(msg);
}

Message MessageQueue::dequeue() {
    // Remove message from front of queue and return
    if (isEmpty()) {
        throw std::runtime_error("Cannot dequeue from empty queue");
    }
    
    // Get the first message
    Message frontMsg = queue.get(0);
    
    // Remove the first element by shifting all elements left
    queue.removeAt(0);
    
    return frontMsg;
}

bool MessageQueue::isEmpty() const {
    return queue.size() == 0;
}

int MessageQueue::size() const {
    return queue.size();
}
