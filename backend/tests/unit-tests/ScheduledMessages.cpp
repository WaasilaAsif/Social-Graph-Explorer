#include "../../messaging/ScheduledMessages.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testAddScheduledMessage() {
    cout << "Testing add scheduled message..." << endl;
    ScheduledMessages scheduler;
    
    Message msg1, msg2, msg3;
    msg1.id = "1";
    msg1.content = "Low priority";
    msg2.id = "2";
    msg2.content = "High priority";
    msg3.id = "3";
    msg3.content = "Medium priority";
    
    scheduler.addScheduledMessage(msg1, 10);
    scheduler.addScheduledMessage(msg2, 100);
    scheduler.addScheduledMessage(msg3, 50);
    
    // Verify messages were added (printAll shouldn't crash)
    scheduler.printAll();
    
    cout << "✓ Add scheduled message tests passed!" << endl;
}

void testGetNextMessage() {
    cout << "Testing get next message (priority order)..." << endl;
    ScheduledMessages scheduler;
    
    Message msg1, msg2, msg3;
    msg1.id = "1";
    msg1.senderId = "alice";
    msg1.content = "Priority 10";
    
    msg2.id = "2";
    msg2.senderId = "bob";
    msg2.content = "Priority 100";
    
    msg3.id = "3";
    msg3.senderId = "charlie";
    msg3.content = "Priority 50";
    
    scheduler.addScheduledMessage(msg1, 10);
    scheduler.addScheduledMessage(msg2, 100);
    scheduler.addScheduledMessage(msg3, 50);
    
    // Get next should return highest priority (100)
    Message next = scheduler.getNextMessage();
    assert(next.id == "2");
    assert(next.senderId == "bob");
    
    cout << "✓ Get next message tests passed!" << endl;
}

void testEmptyScheduler() {
    cout << "Testing empty scheduler..." << endl;
    ScheduledMessages scheduler;
    
    Message next = scheduler.getNextMessage();
    // Should return empty message without crashing
    assert(next.id == "");
    
    scheduler.printAll(); // Should print 0 messages
    
    cout << "✓ Empty scheduler tests passed!" << endl;
}

void testSamePriority() {
    cout << "Testing messages with same priority..." << endl;
    ScheduledMessages scheduler;
    
    Message msg1, msg2, msg3;
    msg1.id = "1";
    msg2.id = "2";
    msg3.id = "3";
    
    // All have same priority
    scheduler.addScheduledMessage(msg1, 50);
    scheduler.addScheduledMessage(msg2, 50);
    scheduler.addScheduledMessage(msg3, 50);
    
    // Should still return a valid message
    Message next = scheduler.getNextMessage();
    assert(next.id != "");
    
    cout << "✓ Same priority tests passed!" << endl;
}

void testMultipleRetrievals() {
    cout << "Testing multiple retrievals..." << endl;
    ScheduledMessages scheduler;
    
    for (int i = 0; i < 10; i++) {
        Message msg;
        msg.id = to_string(i);
        msg.content = "Message " + to_string(i);
        scheduler.addScheduledMessage(msg, i * 10);
    }
    
    // Get multiple messages
    for (int i = 0; i < 5; i++) {
        Message next = scheduler.getNextMessage();
        // Should get messages in descending priority order
        assert(next.id != "");
    }
    
    cout << "✓ Multiple retrievals tests passed!" << endl;
}

int main() {
    cout << "=== ScheduledMessages Unit Tests ===" << endl;
    
    try {
        testAddScheduledMessage();
        testGetNextMessage();
        testEmptyScheduler();
        testSamePriority();
        testMultipleRetrievals();
        
        cout << "\n✓ ALL SCHEDULEDMESSAGES TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
