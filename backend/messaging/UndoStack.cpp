#include "UndoStack.h"

UndoStack::UndoStack() {}

void UndoStack::pushAction(const Message& msg) {
    // Push message to MsgStack for undo tracking
    stack.push(msg);
}

Message UndoStack::popAction() {
    // Pop from MsgStack and return Message
    Message msg;
    if (stack.pop(msg)) {
        return msg;
    }
    // Return empty message if stack is empty
    return Message();
}

bool UndoStack::isEmpty() const {
    // Return if stack is empty
    return stack.isEmpty();
}
