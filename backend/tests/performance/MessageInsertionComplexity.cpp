// MessageInsertionComplexity.cpp
// Test script for measuring message insertion complexity for 1000, 10000, and 100000 messages

#include "../../messaging/MessageStore.h"
#include <iostream>
#include <chrono>
#include <string>

using namespace std;
using namespace chrono;

void testInsertion(int numMessages) {
    MessageStore store;
    int senderId = 1;
    int receiverId = 2;
    string content = "Hello, this is a test message.";

    auto start = high_resolution_clock::now();
    for (int i = 0; i < numMessages; ++i) {
        store.addMessage(senderId, receiverId, content);
    }
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(end - start);
    cout << "Inserted " << numMessages << " messages in " << duration.count() << " ms." << endl;
}

int main() {
    cout << "Testing message insertion complexity..." << endl;
    testInsertion(1000);
    testInsertion(10000);
    testInsertion(100000);
    return 0;
}
