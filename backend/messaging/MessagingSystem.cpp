#include "MessagingSystem.h"
#include <iostream>
#include <sstream>
using namespace std;

MessagingSystem::MessagingSystem() {}

void MessagingSystem::addMessage(const Message& msg) {
    // Add to messages array
    messages.push_back(msg);
    
    // Insert into MsgTrie for searchability
    // Parse content into words and index each word
    stringstream ss(msg.content);
    string word;
    int messageId = messages.size() - 1; // Use index as message ID
    
    while (ss >> word) {
        // Convert to lowercase for case-insensitive search
        for (char& c : word) {
            c = tolower(c);
        }
        msgTrie.insert(word, messageId);
    }
    
    // Push to undo stack
    undoStack.push(msg);
}

DynamicArray<int> MessagingSystem::searchMessages(const string& keyword) {
    // Use MsgTrie to find message IDs containing the keyword
    string lowerKeyword = keyword;
    for (char& c : lowerKeyword) {
        c = tolower(c);
    }
    return msgTrie.search(lowerKeyword);
}

void MessagingSystem::undoLastAction() {
    // Pop from undo stack and revert last message addition
    if (!undoStack.isEmpty()) {
        Message removed;
        if (undoStack.pop(removed)) {
            // Remove the last message from messages array
            if (messages.size() > 0) {
                messages.pop_back();
                cout << "Undid last action: removed message " << removed.id << endl;
            }
        }
    } else {
        cout << "Nothing to undo" << endl;
    }
}

void MessagingSystem::scheduleMessage(const Message& msg, int priority) {
    // Add to scheduledHeap with priority
    // Higher priority = higher number
    scheduledHeap.push(priority);
    messages.push_back(msg);
}

void MessagingSystem::printScheduledMessages() {
    // Print messages in scheduled order (by priority)
    cout << "Scheduled Messages (by priority):" << endl;
    cout << "Total scheduled: " << scheduledHeap.size() << endl;
}
