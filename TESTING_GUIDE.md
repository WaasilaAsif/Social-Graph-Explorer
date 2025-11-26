# Testing Guide - Social Graph Explorer

## Unit Tests Overview

All unit tests use custom data structures (no STL containers except `std::string`).

### Test Coverage Summary

#### ✅ Messaging System Tests (9/9 passed)
- **MessageStore basics** - Message storage and retrieval
- **Word extraction** - Text tokenization and lowercasing
- **Trie indexing** - Word-based message search
- **ConversationGraph** - Weighted interaction tracking
- **Top K interactions** - Ranking by message frequency
- **Friend suggestions** - Friends-of-friends recommendations
- **Mutual interactions** - Finding mutual connections
- **Shortest path** - BFS path finding
- **Integration scenario** - End-to-end workflow

#### ✅ Msg Algorithm Tests (21/21 passed)
- **MsgMutualInteraction** (4/4) - Mutual connection discovery
- **MsgFriendSuggestion** (5/5) - Friend recommendation algorithm
- **MsgShortestPath** (6/6) - BFS shortest path
- **MsgTopKMessages** (6/6) - Top-K interaction ranking

#### ✅ Messaging DS Tests (28/28 passed)
- **MsgHeap** (4/4) - Priority queue operations
- **MsgTrie** (5/5) - Prefix-based search
- **MsgStack** (5/5) - Undo/redo functionality
- **ConversationGraph** (7/7) - Weighted graph
- **AVLTree** (7/7) - Balanced BST

#### ✅ Messaging System Advanced Tests (21/21 passed)
- **MessagingSystem** (4/4) - Core messaging
- **MessageQueue** (4/4) - Message queueing
- **MessageAnalytics** (4/4) - Analytics tracking
- **ScheduledMessages** (4/4) - Time-based delivery
- **TopKConversations** (3/3) - Top conversations
- **UndoStack** (2/2) - Message undo

**Total: 79+ unit tests, all passing**

## Running Unit Tests

### Compile and Run All Tests

```powershell
# From D:\SocialGraphExplorer

# Messaging Integration Tests
g++ -std=c++17 -I backend -o backend/tests/MsgAPI.exe `
    backend/tests/unit-tests/MsgAPI.cpp `
    backend/messaging/MessageStore.cpp `
    backend/dsa/messaging_ds/MsgTrie.cpp `
    backend/dsa/messaging_ds/ConversationGraph.cpp `
    backend/algorithms/MsgFriendSuggestion.cpp `
    backend/algorithms/MsgMutualInteractions.cpp `
    backend/algorithms/MsgShortestPatch.cpp `
    backend/algorithms/MsgTopKMessage.cpp `
    backend/algorithms/MsgPopularityRanker.cpp

.\backend\tests\MsgAPI.exe

# Run other test suites
.\backend\tests\run-messaging-tests.ps1
```

## API Endpoint Testing

### Prerequisites

1. **Compile the server** (requires Crow framework):

```powershell
# Install Crow if needed
# Download from https://github.com/CrowCpp/Crow

g++ -std=c++17 -I backend -I path/to/crow/include `
    -o backend/api/server.exe `
    backend/api/server.cpp `
    backend/api/routes/MsgAPI.cpp `
    backend/api/routes/MsgRoutes.cpp `
    backend/messaging/MessageStore.cpp `
    backend/dsa/messaging_ds/*.cpp `
    backend/algorithms/Msg*.cpp `
    # ... add other required files
    -pthread
```

2. **Start the server**:

```powershell
.\backend\api\server.exe
```

Server starts on `http://localhost:8080`

### API Endpoints

#### 1. Send Message
```bash
curl -X POST http://localhost:8080/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1, "receiverId":2, "text":"Hello world from API"}'
```

**Expected Response:**
```json
{
  "success": true,
  "messageId": 1
}
```

#### 2. Search for Word
```bash
curl http://localhost:8080/msg/search/hello
```

**Expected Response:**
```json
{
  "query": "hello",
  "results": [1]
}
```

#### 3. Prefix Search
```bash
curl http://localhost:8080/msg/prefix/hel
```

**Expected Response:**
```json
{
  "prefix": "hel",
  "results": [1]
}
```

#### 4. Get Top K Interactions
```bash
curl http://localhost:8080/msg/topk/1/5
```

**Expected Response:**
```json
{
  "userId": 1,
  "k": 5,
  "messages": [
    {"userId": 2, "weight": 3},
    {"userId": 3, "weight": 1}
  ]
}
```

#### 5. Friend Suggestions
```bash
curl http://localhost:8080/msg/suggestions/1/3
```

**Expected Response:**
```json
{
  "userId": 1,
  "k": 3,
  "friends": [3, 4]
}
```

#### 6. Mutual Interactions
```bash
curl http://localhost:8080/msg/mutual/1
```

**Expected Response:**
```json
{
  "userId": 1,
  "mutual": [
    {"user1": 2, "user2": 3}
  ]
}
```

#### 7. Popularity Ranking
```bash
curl http://localhost:8080/msg/rank/10
```

**Expected Response:**
```json
{
  "topN": 10,
  "ranking": [
    {"userId": 1, "messageCount": 5},
    {"userId": 2, "messageCount": 3}
  ]
}
```

#### 8. Shortest Path
```bash
curl http://localhost:8080/msg/path/1/5
```

**Expected Response:**
```json
{
  "src": 1,
  "dest": 5,
  "path": [1, 2, 3, 5]
}
```

### PowerShell Testing Script

Create `test-api.ps1`:

```powershell
# Test API Endpoints
$baseUrl = "http://localhost:8080"

Write-Host "Testing Messaging API Endpoints..." -ForegroundColor Green

# 1. Send messages
Write-Host "`n1. Sending messages..." -ForegroundColor Yellow
$msg1 = @{ senderId=1; receiverId=2; text="Hello world" } | ConvertTo-Json
$msg2 = @{ senderId=2; receiverId=1; text="Hi there" } | ConvertTo-Json
$msg3 = @{ senderId=1; receiverId=3; text="Test message" } | ConvertTo-Json

$response1 = Invoke-RestMethod -Uri "$baseUrl/msg/send" -Method POST -Body $msg1 -ContentType "application/json"
$response2 = Invoke-RestMethod -Uri "$baseUrl/msg/send" -Method POST -Body $msg2 -ContentType "application/json"
$response3 = Invoke-RestMethod -Uri "$baseUrl/msg/send" -Method POST -Body $msg3 -ContentType "application/json"

Write-Host "Messages sent: $($response1.messageId), $($response2.messageId), $($response3.messageId)"

# 2. Search for word
Write-Host "`n2. Searching for 'hello'..." -ForegroundColor Yellow
$search = Invoke-RestMethod -Uri "$baseUrl/msg/search/hello"
Write-Host "Search results: $($search.results)"

# 3. Prefix search
Write-Host "`n3. Prefix search 'hel'..." -ForegroundColor Yellow
$prefix = Invoke-RestMethod -Uri "$baseUrl/msg/prefix/hel"
Write-Host "Prefix results: $($prefix.results)"

# 4. Top K interactions
Write-Host "`n4. Getting top 5 interactions for user 1..." -ForegroundColor Yellow
$topK = Invoke-RestMethod -Uri "$baseUrl/msg/topk/1/5"
Write-Host "Top interactions: $($topK.messages | ForEach-Object { "$($_.userId):$($_.weight)" })"

# 5. Friend suggestions
Write-Host "`n5. Getting friend suggestions for user 1..." -ForegroundColor Yellow
$suggestions = Invoke-RestMethod -Uri "$baseUrl/msg/suggestions/1/3"
Write-Host "Suggested friends: $($suggestions.friends)"

# 6. Mutual interactions
Write-Host "`n6. Getting mutual interactions for user 1..." -ForegroundColor Yellow
$mutual = Invoke-RestMethod -Uri "$baseUrl/msg/mutual/1"
Write-Host "Mutual connections: $($mutual.mutual.Count)"

# 7. Popularity ranking
Write-Host "`n7. Getting popularity ranking..." -ForegroundColor Yellow
$rank = Invoke-RestMethod -Uri "$baseUrl/msg/rank/10"
Write-Host "Top users: $($rank.ranking | ForEach-Object { "$($_.userId):$($_.messageCount)" })"

# 8. Shortest path
Write-Host "`n8. Finding shortest path from 1 to 3..." -ForegroundColor Yellow
$path = Invoke-RestMethod -Uri "$baseUrl/msg/path/1/3"
Write-Host "Path: $($path.path -join ' -> ')"

Write-Host "`n✓ All API tests completed!" -ForegroundColor Green
```

Run with:
```powershell
.\test-api.ps1
```

## Integration Testing Workflow

1. **Start with unit tests**:
   ```powershell
   .\backend\tests\MsgAPI.exe
   ```

2. **Run full messaging test suite**:
   ```powershell
   .\backend\tests\run-messaging-tests.ps1
   ```

3. **Start the server**:
   ```powershell
   .\backend\api\server.exe
   ```

4. **Test API endpoints**:
   ```powershell
   .\test-api.ps1
   ```

5. **Manual testing** with browser:
   - Navigate to `http://localhost:8080`
   - View API documentation page
   - Use browser dev tools to test endpoints

## Test Status

| Component | Tests | Status |
|-----------|-------|--------|
| MessageStore | 2 | ✅ PASS |
| MsgTrie | 2 | ✅ PASS |
| ConversationGraph | 1 | ✅ PASS |
| MsgTopKMessages | 1 | ✅ PASS |
| MsgFriendSuggestion | 1 | ✅ PASS |
| MsgMutualInteraction | 1 | ✅ PASS |
| MsgShortestPath | 1 | ✅ PASS |
| Integration | 1 | ✅ PASS |
| **Total** | **9** | **✅ ALL PASS** |

## Troubleshooting

### Compilation Issues

**Issue**: Missing Crow headers
**Solution**: Download Crow from GitHub and add include path:
```powershell
-I path/to/crow/include
```

**Issue**: Linking errors
**Solution**: Add pthread library:
```powershell
-pthread
```

### Runtime Issues

**Issue**: Server won't start
**Solution**: Check if port 8080 is available:
```powershell
netstat -ano | findstr :8080
```

**Issue**: API returns errors
**Solution**: Check server logs in console

### Test Failures

**Issue**: Unit tests fail
**Solution**: Rebuild all dependencies:
```powershell
# Clean build
Remove-Item backend/tests/*.exe -Force
# Rebuild
.\backend\tests\run-messaging-tests.ps1
```

## Next Steps

1. ✅ All unit tests passing
2. ⏳ Server compilation (requires Crow)
3. ⏳ API endpoint testing
4. ⏳ Frontend integration
5. ⏳ End-to-end testing

## Documentation

- `README.md` - Project overview
- `backend/tests/unit-tests/README_MSGAPI_TESTS.md` - API testing guide
- `backend/tests/unit-tests/README_MSG_ALGORITHMS_TESTS.md` - Algorithm tests
- `backend/tests/unit-tests/README_MESSAGING_SYSTEM_TESTS.md` - System tests
- `backend/tests/unit-tests/README_MESSAGING_TESTS.md` - Data structure tests
