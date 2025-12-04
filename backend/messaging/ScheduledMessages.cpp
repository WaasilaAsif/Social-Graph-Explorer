#include "ScheduledMessages.h"
#include <iostream>
using namespace std;

ScheduledMessages::ScheduledMessages() {}

void ScheduledMessages::addScheduledMessage(const Message& msg, int priority) {
    // Add message to scheduled array
    scheduled.push_back(msg);
    
    // Add priority to heap (we'll use the index in scheduled array)
    // Store: priority * 1000 + index to encode both
    int index = scheduled.size() - 1;
    heap.push(priority * 1000 + index);
}

Message ScheduledMessages::getNextMessage() {
    // Pop highest priority message from heap
    if (heap.isEmpty()) {
        cout << "No scheduled messages" << endl;
        return Message();
    }
    
    int value;
    if (heap.pop(value)) {
        int index = value % 1000;
        if (index >= 0 && index < scheduled.size()) {
            return scheduled.get(index);
        }
    }
    
    return Message();
}

void ScheduledMessages::printAll() {
    // Print all scheduled messages
    cout << "All Scheduled Messages (" << scheduled.size() << " total):" << endl;
    for (int i = 0; i < scheduled.size(); i++) {
        Message msg = scheduled.get(i);
        cout << "[" << i << "] From: " << msg.senderId 
             << " To: " << msg.receiverId 
             << " - " << msg.content << endl;
    }
}
