#ifndef MSGSTACK_H
#define MSGSTACK_H

#include <string>

// Forward declaration to avoid dependency
struct Message;

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
    MsgStack();
    ~MsgStack();

    void push(const Message& msg);
    bool pop(Message& removed);
    bool peek(Message& topMsg) const;
    bool isEmpty() const;
    int size() const;
};

#endif
