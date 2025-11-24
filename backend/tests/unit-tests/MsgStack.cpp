// Standalone MsgStack test with inline implementation
#include <iostream>
#include <cassert>
#include <string>

using namespace std;

// Message struct for testing
struct Message {
    string id;
    string senderId;
    string receiverId;
    string content;
    long long timestamp;
    bool delivered = false;
    bool read = false;
};

// MsgStack implementation
class MsgStack {
private:
    struct Node {
        Message data;
        Node* next;
        Node(const Message& m) : data(m), next(nullptr) {}
    };

    Node* topNode;
    int count;

public:
    MsgStack() : topNode(nullptr), count(0) {}

    ~MsgStack() {
        Message temp;
        while (pop(temp));
    }

    void push(const Message& msg) {
        if(topNode == nullptr) {
            topNode = new Node(msg);
            count++;
            return;
        }
        Node *newNode = new Node(msg);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    bool pop(Message& removed) {
        if (topNode == nullptr) {
            return false; 
        }
        Node *temp = topNode;
        removed = topNode->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return true;
    }

    bool peek(Message& topMsg) const {
        if (topNode == nullptr) {
            return false;
        }
        topMsg = topNode->data;
        return true;
    }

    bool isEmpty() const {
        return count == 0;
    }

    int size() const {
        return count;
    }
};

Message createTestMessage(string id, string sender, string receiver, string content) {
    Message msg;
    msg.id = id;
    msg.senderId = sender;
    msg.receiverId = receiver;
    msg.content = content;
    msg.timestamp = 1234567890;
    msg.delivered = false;
    msg.read = false;
    return msg;
}

void testPushPop() {
    cout << "Testing push and pop operations..." << endl;
    MsgStack stack;
    
    Message msg1 = createTestMessage("1", "user1", "user2", "Hello");
    Message msg2 = createTestMessage("2", "user2", "user1", "Hi there");
    Message msg3 = createTestMessage("3", "user1", "user2", "How are you?");
    
    stack.push(msg1);
    stack.push(msg2);
    stack.push(msg3);
    
    assert(stack.size() == 3);
    assert(!stack.isEmpty());
    
    Message popped;
    assert(stack.pop(popped));
    assert(popped.id == "3"); // LIFO - last in first out
    
    assert(stack.pop(popped));
    assert(popped.id == "2");
    
    assert(stack.pop(popped));
    assert(popped.id == "1");
    
    assert(stack.isEmpty());
    assert(stack.size() == 0);
    
    cout << "✓ Push/Pop tests passed!" << endl;
}

void testPeek() {
    cout << "Testing peek operation..." << endl;
    MsgStack stack;
    
    Message msg1 = createTestMessage("1", "user1", "user2", "First");
    Message msg2 = createTestMessage("2", "user2", "user1", "Second");
    
    stack.push(msg1);
    stack.push(msg2);
    
    Message peeked;
    assert(stack.peek(peeked));
    assert(peeked.id == "2"); // Should see top without removing
    assert(stack.size() == 2); // Size unchanged
    
    assert(stack.peek(peeked));
    assert(peeked.id == "2"); // Still the same
    
    cout << "✓ Peek tests passed!" << endl;
}

void testEmptyStack() {
    cout << "Testing empty stack operations..." << endl;
    MsgStack stack;
    
    assert(stack.isEmpty());
    assert(stack.size() == 0);
    
    Message msg;
    assert(!stack.pop(msg)); // Can't pop from empty
    assert(!stack.peek(msg)); // Can't peek empty
    
    cout << "✓ Empty stack tests passed!" << endl;
}

int main() {
    cout << "=== MsgStack Unit Tests ===" << endl;
    
    try {
        testPushPop();
        testPeek();
        testEmptyStack();
        
        cout << "\n✓ ALL MSGSTACK TESTS PASSED!" << endl;
        return 0;
    } catch (const exception& e) {
        cout << "\n✗ Test failed: " << e.what() << endl;
        return 1;
    }
}
