#include "MsgStack.h"
#include "../../messaging/Message.h"
#include <iostream>

using namespace std;
//Ok so I did linked list implementation of message stack here
//Me ne apna custom stack banaya hai that deals with the handling of all the messages
//All its nodes have the Message struct defined in Message.h
MsgStack::MsgStack() : topNode(nullptr), count(0) {}

MsgStack::~MsgStack() {
    Message temp;
    while (pop(temp));
}

void MsgStack::push(const Message& msg) {
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

bool MsgStack::pop(Message& removed) {
    if (topNode == nullptr) {
        return false; 
    }
    Node *temp = topNode;
    removed = topNode->data;
    topNode = topNode->next;
    delete temp;
    cout << "Popped message with ID: " << removed.id << endl;
    count--;
    return true;
}

bool MsgStack::peek(Message& topMsg) const {
    if (topNode == nullptr) {
        return false;
    }
    topMsg = topNode->data;
    return true;
}

bool MsgStack::isEmpty() const {
    return count == 0;
}

int MsgStack::size() const {
    return count;
}
