#ifndef UNDOSTACK_H
#define UNDOSTACK_H

#include "./dsa/messaging_ds/MsgStack.h"
#include "Message.h"

class UndoStack {
private:
    MsgStack stack;

public:
    UndoStack();
    void pushAction(const Message& msg);
    Message popAction();
    bool isEmpty() const;
};

#endif
