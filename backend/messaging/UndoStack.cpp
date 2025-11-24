#include "UndoStack.h"

UndoStack::UndoStack() {}

void UndoStack::pushAction(const Message& msg) {
    // TODO: Push to MsgStack
}

Message UndoStack::popAction() {
    // TODO: Pop from MsgStack and return Message
    return Message();
}

bool UndoStack::isEmpty() const {
    // TODO: Return if stack is empty
    return false;
}
