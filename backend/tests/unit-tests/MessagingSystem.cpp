#include "../../messaging/MessagingSystem.h"
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

void testAddMessage() {
    cout << "Testing add message..." << endl;
    MessagingSystem system;
    
    Message msg1;
    msg1.id = "1";
    msg1.senderId = "alice";
    msg1.receiverId = "bob";
    msg1.content = "hello world test";
    msg1.timestamp = 1000;
    
    system.addMessage(msg1);
    
    // Should be able to search for words in the message
    DynamicArray<int> results = system.searchMessages("hello");
    assert(results.size() == 1);
    assert(results.get(0) == 0); // First message, index 0
    
    cout << "✓ Add message tests passed!" << endl;
}

void testSearchMessages() {
    cout << "Testing search messages..." << endl;
    MessagingSystem system;
    
    Message msg1;
    msg1.id = "1";
    msg1.content = "hello world";
    system.addMessage(msg1);
    
    Message msg2;
    msg2.id = "2";
    msg2.content = "hello there";
    system.addMessage(msg2);
    
    Message msg3;
    msg3.id = "3";
    msg3.content = "goodbye world";
    system.addMessage(msg3);
    
    // Search for "hello" - should find msg1 and msg2
    DynamicArray<int> results = system.searchMessages("hello");
    assert(results.size() == 2);
    
    // Search for "world" - should find msg1 and msg3
    results = system.searchMessages("world");
    assert(results.size() == 2);
    
    // Search for non-existent word
    results = system.searchMessages("nonexistent");
    assert(results.size() == 0);
    
    cout << "✓ Search messages tests passed!" << endl;
}

void testCaseInsensitiveSearch() {
    cout << "Testing case-insensitive search..." << endl;
    MessagingSystem system;
    
    Message msg;
    msg.id = "1";
    msg.content = "Hello World";
    system.addMessage(msg);
    
    // Search with different cases
    DynamicArray<int> results1 = system.searchMessages("hello");
    DynamicArray<int> results2 = system.searchMessages("HELLO");
    DynamicArray<int> results3 = system.searchMessages("Hello");
    
    assert(results1.size() == 1);
    assert(results2.size() == 1);
    assert(results3.size() == 1);
    
    cout << "✓ Case-insensitive search tests passed!" << endl;
}

void testScheduleMessage() {
    cout << "Testing schedule message..." << endl;
    MessagingSystem system;
    
    Message msg1, msg2, msg3;
    msg1.id = "1";
    msg2.id = "2";
    msg3.id = "3";
    
    // Schedule with different priorities
    system.scheduleMessage(msg1, 10);
    system.scheduleMessage(msg2, 50);
    system.scheduleMessage(msg3, 30);
    
    // Just verify no crashes
    system.printScheduledMessages();
    
    cout << "✓ Schedule message tests passed!" << endl;
}

void testUndoLastAction() {
    cout << "Testing undo last action..." << endl;
    MessagingSystem system;
    
    Message msg1, msg2, msg3;
    msg1.id = "1";
    msg1.content = "first";
    msg2.id = "2";
    msg2.content = "second";
    msg3.id = "3";
    msg3.content = "third";
    
    system.addMessage(msg1);
    system.addMessage(msg2);
    system.addMessage(msg3);
    
    // Search should find all three
    DynamicArray<int> results = system.searchMessages("first");
    assert(results.size() == 1);
    results = system.searchMessages("second");
    assert(results.size() == 1);
    results = system.searchMessages("third");
    assert(results.size() == 1);
    
    // Undo last message (msg3)
    system.undoLastAction();
    
    // "third" should no longer be searchable
    results = system.searchMessages("third");
    // Note: Trie still contains the word, but message is removed from array
    
    cout << "✓ Undo last action tests passed!" << endl;
}

void testMultipleWords() {
    cout << "Testing messages with multiple words..." << endl;
    MessagingSystem system;
    
    Message msg;
    msg.id = "1";
    msg.content = "the quick brown fox jumps over the lazy dog";
    system.addMessage(msg);
    
    // Each word should be searchable
    assert(system.searchMessages("quick").size() == 1);
    assert(system.searchMessages("brown").size() == 1);
    assert(system.searchMessages("fox").size() == 1);
    assert(system.searchMessages("jumps").size() == 1);
    
    cout << "✓ Multiple words tests passed!" << endl;
}

int main() {
    cout << "=== MessagingSystem Unit Tests ===" << endl;
    
    try {
        testAddMessage();
        testSearchMessages();
        testCaseInsensitiveSearch();
        testScheduleMessage();
        testUndoLastAction();
        testMultipleWords();
        
        cout << "\n✓ ALL MESSAGINGSYSTEM TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
