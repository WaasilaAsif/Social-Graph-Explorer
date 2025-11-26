# MsgAPI Tests

Integration tests for the messaging API endpoints.

## Test File

**MsgAPI.cpp** - Complete API integration testing

## Compilation

From the `D:\SocialGraphExplorer` directory:

```powershell
g++ -std=c++17 -I backend -o backend/tests/MsgAPI.exe `
    backend/tests/unit-tests/MsgAPI.cpp `
    backend/api/routes/MsgAPI.cpp `
    backend/messaging/MessageStore.cpp `
    backend/dsa/messaging_ds/MsgTrie.cpp `
    backend/dsa/messaging_ds/ConversationGraph.cpp
```

## Run Tests

```powershell
.\backend\tests\MsgAPI.exe
```

## Test Coverage

### API Endpoint Tests
- ✅ **handleSendMessage** - Send message, word extraction, trie indexing, graph update
- ✅ **handleSearchWord** - Full word search in messages
- ✅ **handleSearchPrefix** - Prefix-based message search
- ✅ **handleTopK** - Top-K interactions by weight
- ✅ **handleFriendSuggestion** - Friend recommendations based on messages
- ✅ **handleMutualInteractions** - Find mutual message connections
- ✅ **handleShortestPath** - Shortest path through message network
- ✅ **Integration Scenario** - Multi-user messaging workflow

### Components Tested
- MessageStore integration
- MsgTrie word indexing
- ConversationGraph interaction tracking
- JSON response formatting
- Parameter parsing

## API Endpoints (Server)

Once the server is running (`backend/api/server.cpp`), test with:

### 1. Send Message
```bash
curl -X POST http://localhost:8080/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1, "receiverId":2, "text":"Hello world"}'
```

### 2. Search Word
```bash
curl http://localhost:8080/msg/search/hello
```

### 3. Search Prefix
```bash
curl http://localhost:8080/msg/prefix/hel
```

### 4. Top K Interactions
```bash
curl http://localhost:8080/msg/topk/1/5
```

### 5. Friend Suggestions
```bash
curl http://localhost:8080/msg/suggestions/1/3
```

### 6. Mutual Interactions
```bash
curl http://localhost:8080/msg/mutual/1
```

### 7. Popularity Ranking
```bash
curl http://localhost:8080/msg/rank/10
```

### 8. Shortest Path
```bash
curl http://localhost:8080/msg/path/1/5
```

## Integration with Server

The MsgAPI is integrated into the main server (`backend/api/server.cpp`) via MsgRoutes:

```cpp
// Server initialization
MessageStore msgStore;
MsgTrie msgTrie;
ConversationGraph convGraph;
UserManager userManager;

MsgAPI msgApi(&userManager, &msgStore, &msgTrie, &convGraph);
MsgRoutes msgRoutes(&msgApi);
msgRoutes.registerRoutes(app);
```

All routes are registered with CORS support and return JSON responses.
