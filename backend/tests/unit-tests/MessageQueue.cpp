#include "../../messaging/MessageQueue.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testEnqueueDequeue() {
    cout << "Testing enqueue and dequeue..." << endl;
    MessageQueue queue;
    
    Message msg1;
    msg1.id = "1";
    msg1.senderId = "user1";
    msg1.receiverId = "user2";
    msg1.content = "Hello";
    msg1.timestamp = 1000;
    
    Message msg2;
    msg2.id = "2";
    msg2.senderId = "user2";
    msg2.receiverId = "user1";
    msg2.content = "Hi there";
    msg2.timestamp = 2000;
    
    Message msg3;
    msg3.id = "3";
    msg3.senderId = "user1";
    msg3.receiverId = "user2";
    msg3.content = "How are you?";
    msg3.timestamp = 3000;
    
    // Test enqueue
    queue.enqueue(msg1);
    queue.enqueue(msg2);
    queue.enqueue(msg3);
    
    assert(queue.size() == 3);
    assert(!queue.isEmpty());
    
    // Test FIFO order
    Message dequeued = queue.dequeue();
    assert(dequeued.id == "1");
    assert(queue.size() == 2);
    
    dequeued = queue.dequeue();
    assert(dequeued.id == "2");
    assert(queue.size() == 1);
    
    dequeued = queue.dequeue();
    assert(dequeued.id == "3");
    assert(queue.size() == 0);
    assert(queue.isEmpty());
    
    cout << " Enqueue/Dequeue tests passed!" << endl;
}

void testEmptyQueue() {
    cout << "Testing empty queue operations..." << endl;
    MessageQueue queue;
    
    assert(queue.isEmpty());
    assert(queue.size() == 0);
    
    // Test dequeue on empty queue throws exception
    bool exceptionThrown = false;
    try {
        queue.dequeue();
    } catch (const runtime_error& e) {
        exceptionThrown = true;
    }
    assert(exceptionThrown);
    
    cout << " Empty queue tests passed!" << endl;
}

void testLargeQueue() {
    cout << "Testing large queue..." << endl;
    MessageQueue queue;
    
    // Enqueue 100 messages
    for (int i = 0; i < 100; i++) {
        Message msg;
        msg.id = to_string(i);
        msg.senderId = "sender" + to_string(i);
        msg.receiverId = "receiver" + to_string(i);
        msg.content = "Message " + to_string(i);
        msg.timestamp = i * 1000;
        queue.enqueue(msg);
    }
    
    assert(queue.size() == 100);
    
    // Dequeue all and verify order
    for (int i = 0; i < 100; i++) {
        Message msg = queue.dequeue();
        assert(msg.id == to_string(i));
    }
    
    assert(queue.isEmpty());
    
    cout << " Large queue tests passed!" << endl;
}

int main() {
    cout << "=== MessageQueue Unit Tests ===" << endl;
    
    try {
        testEnqueueDequeue();
        testEmptyQueue();
        testLargeQueue();
        
        cout << "\n ALL MESSAGEQUEUE TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
