# Msg Algorithms Tests

Comprehensive unit tests for message-based graph algorithms.

## Test Files

### Algorithm Tests
1. **MsgMutualInteraction.cpp** - Find mutual connections between users
2. **MsgFriendSuggestion.cpp** - Suggest friends based on mutual connections
3. **MsgShortestPath.cpp** - BFS-based shortest path in conversation network
4. **MsgTopKMessages.cpp** - Top-K users by interaction weight

## Compilation & Execution

From the `D:\SocialGraphExplorer` directory:

### Compile Tests
```powershell
# MsgMutualInteraction
g++ -std=c++17 -I backend -o backend/tests/MsgMutualInteraction.exe backend/tests/unit-tests/MsgMutualInteraction.cpp backend/algorithms/MsgMutualInteractions.cpp backend/dsa/messaging_ds/ConversationGraph.cpp

# MsgFriendSuggestion
g++ -std=c++17 -I backend -o backend/tests/MsgFriendSuggestion.exe backend/tests/unit-tests/MsgFriendSuggestion.cpp backend/algorithms/MsgFriendSuggestion.cpp backend/dsa/messaging_ds/ConversationGraph.cpp

# MsgShortestPath
g++ -std=c++17 -I backend -o backend/tests/MsgShortestPath.exe backend/tests/unit-tests/MsgShortestPath.cpp backend/algorithms/MsgShortestPatch.cpp backend/dsa/messaging_ds/ConversationGraph.cpp

# MsgTopKMessages
g++ -std=c++17 -I backend -o backend/tests/MsgTopKMessages.exe backend/tests/unit-tests/MsgTopKMessages.cpp backend/algorithms/MsgTopKMessage.cpp backend/dsa/messaging_ds/ConversationGraph.cpp
```

### Run All Tests
```powershell
.\backend\tests\MsgMutualInteraction.exe
.\backend\tests\MsgFriendSuggestion.exe
.\backend\tests\MsgShortestPath.exe
.\backend\tests\MsgTopKMessages.exe
```

## Test Coverage

### MsgMutualInteraction
-    Find mutual connections in conversation network
-    Non-existent user handling
-    User with no mutual connections
-    Complex network scenarios

### MsgFriendSuggestion
-    Suggest friends based on mutual connections
-    No suggestions available
-    Non-existent user handling
-    K limit enforcement
-    Mutual connections priority (most mutual first)

### MsgShortestPath
-    Direct connection (1 hop)
-    Multi-hop paths
-    No path exists (disconnected components)
-    Same source and destination
-    Complex graph with multiple paths
-    Non-existent users handling

### MsgTopKMessages
-    Get top-K interactions by weight
-    User with no interactions
-    K larger than available interactions
-    Sorting by interaction weight (descending)
-    Non-existent user handling
-    Invalid k values (0, negative)

## Algorithm Details

### MsgMutualInteraction
**Algorithm**: For each neighbor of user, find neighbors that are also connected to user's other neighbors.
**Complexity**: O(N * M) where N is neighbors, M is their neighbors

### MsgFriendSuggestion
**Algorithm**: Friends-of-friends with mutual connection counting and top-K selection.
**Complexity**: O(N * M + K log K) for sorting top K suggestions

### MsgShortestPath
**Algorithm**: Breadth-First Search (BFS) with parent tracking for path reconstruction.
**Complexity**: O(V + E) where V is vertices, E is edges

### MsgTopKMessages
**Algorithm**: Extract all interactions, sort by weight, return top-K.
**Complexity**: O(N log N) for sorting N interactions

## All Tests Status

   **ALL MSG ALGORITHM TESTS IMPLEMENTED**
- 4 test files created
- Complete coverage of message-based graph algorithms
- All using custom data structures (no STL)
