# Messaging Data Structures Tests

This folder contains comprehensive unit tests for all messaging_ds modules.

## Test Files

1. **MsgHeap.cpp** - Priority queue (min/max heap) for message IDs
2. **MsgTrie.cpp** - Trie for word search in messages
3. **MsgStack.cpp** - Stack for message history (LIFO)
4. **ConversationGraph.cpp** - Weighted graph for user interactions
5. **AVLTree_messaging.cpp** - Self-balancing BST for sorted data

## Compilation & Execution

From the `D:\SocialGraphExplorer` directory:

```powershell
# Compile all tests
g++ -std=c++17 -I backend -o backend/tests/MsgHeap.exe backend/tests/unit-tests/MsgHeap.cpp backend/dsa/messaging_ds/MsgHeap.cpp

g++ -std=c++17 -I backend -o backend/tests/MsgTrie.exe backend/tests/unit-tests/MsgTrie.cpp backend/dsa/messaging_ds/MsgTrie.cpp

g++ -std=c++17 -o backend/tests/MsgStack.exe backend/tests/unit-tests/MsgStack.cpp

g++ -std=c++17 -I backend -o backend/tests/ConversationGraph.exe backend/tests/unit-tests/ConversationGraph.cpp backend/dsa/messaging_ds/ConversationGraph.cpp

g++ -std=c++17 -I backend -o backend/tests/AVLTree_messaging.exe backend/tests/unit-tests/AVLTree_messaging.cpp backend/dsa/messaging_ds/AVLTree.cpp

# Run all tests
.\backend\tests\MsgHeap.exe
.\backend\tests\MsgTrie.exe
.\backend\tests\MsgStack.exe
.\backend\tests\ConversationGraph.exe
.\backend\tests\AVLTree_messaging.exe
```

## Run All Tests at Once

```powershell
# Compile and run all in one command
g++ -std=c++17 -I backend -o backend/tests/MsgHeap.exe backend/tests/unit-tests/MsgHeap.cpp backend/dsa/messaging_ds/MsgHeap.cpp; .\backend\tests\MsgHeap.exe

g++ -std=c++17 -I backend -o backend/tests/MsgTrie.exe backend/tests/unit-tests/MsgTrie.cpp backend/dsa/messaging_ds/MsgTrie.cpp; .\backend\tests\MsgTrie.exe

g++ -std=c++17 -o backend/tests/MsgStack.exe backend/tests/unit-tests/MsgStack.cpp; .\backend\tests\MsgStack.exe

g++ -std=c++17 -I backend -o backend/tests/ConversationGraph.exe backend/tests/unit-tests/ConversationGraph.cpp backend/dsa/messaging_ds/ConversationGraph.cpp; .\backend\tests\ConversationGraph.exe

g++ -std=c++17 -I backend -o backend/tests/AVLTree_messaging.exe backend/tests/unit-tests/AVLTree_messaging.cpp backend/dsa/messaging_ds/AVLTree.cpp; .\backend\tests\AVLTree_messaging.exe
```

## Test Coverage

### MsgHeap
-    Min heap operations
-    Max heap operations
-    Push, pop, peek
-    Empty heap edge cases

### MsgTrie
-    Insert and exact word search
-    Prefix search
-    Multiple messages indexing
-    Empty trie handling

### MsgStack
-    Push/pop with Message objects
-    Peek without removal
-    LIFO ordering
-    Empty stack operations

### ConversationGraph
-    Add bidirectional interactions
-    Incremental weight updates
-    Get neighbors
-    Complex network scenarios

### AVLTree
-    Insert/remove/search
-    Inorder traversal (sorted)
-    Auto-balancing
-    Duplicate handling
-    Large tree performance (1000 elements)

## All Tests Status

   **ALL TESTS PASSING**
