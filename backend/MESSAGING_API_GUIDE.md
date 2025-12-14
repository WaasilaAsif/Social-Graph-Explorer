# Messaging API Documentation

Complete guide to all messaging endpoints with real examples, expected outputs, and data structures.

---

##  Table of Contents

1. [Overview](#overview)
2. [Data Structures](#data-structures)
3. [API Endpoints](#api-endpoints)
   - [Send Message](#1-send-message)
   - [Search Word](#2-search-word)
   - [Search Prefix](#3-search-prefix)
   - [Top K Messages](#4-top-k-messages)
   - [Friend Suggestions](#5-friend-suggestions)
   - [Mutual Interactions](#6-mutual-interactions)
   - [Popularity Ranking](#7-popularity-ranking)
   - [Shortest Path](#8-shortest-path)
4. [Database Structure](#database-structure)
5. [Testing Guide](#testing-guide)

---

## Overview

The messaging system provides 8 powerful APIs for sending, searching, and analyzing messages between users. All data is persisted in `storage/local_db/messages.json` and loaded into three specialized data structures at startup.

**Base URL**: `http://localhost:8081`

**Current Database**: 50+ messages between users 1-20 covering topics like projects, meetings, code reviews, and casual conversations.

---

## Data Structures

### 1. MessageStore
- **Purpose**: Stores all message objects with metadata
- **Key Methods**: `addMessage()`, `getMessage()`, `extractWords()`
- **Used By**: All messaging APIs

### 2. MsgTrie (Prefix Tree)
- **Purpose**: Indexes message words for fast search
- **Key Methods**: `insert()`, `search()`, `startsWith()`
- **Used By**: Word Search, Prefix Search APIs

### 3. ConversationGraph
- **Purpose**: Tracks user interactions as a weighted graph
- **Key Methods**: `addInteraction()`, `getInteractions()`
- **Used By**: Top-K, Friend Suggestions, Mutual Interactions, Popularity, Shortest Path APIs

---

## API Endpoints

### 1. Send Message

Send a new message from one user to another. Message is automatically saved to database.

**Endpoint**: `POST /msg/send`

**Request Body**:
```json
{
  "senderId": 1,
  "receiverId": 3,
  "text": "Hey Charlie! Ready for the demo tomorrow?"
}
```

**Example cURL**:
```bash
curl -X POST http://localhost:8081/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1,"receiverId":3,"text":"Hey Charlie! Ready for the demo tomorrow?"}'
```

**Expected Response**:
```json
{
  "status": "success",
  "messageId": 51
}
```

**What Happens**:
1. Message added to MessageStore
2. Words extracted and indexed in MsgTrie: ["Hey", "Charlie", "Ready", "for", "the", "demo", "tomorrow"]
3. Interaction recorded in ConversationGraph (sender 1 → receiver 3)
4. **Automatically saved to messages.json**

**Status Codes**:
- `200`: Success
- `400`: Invalid JSON or missing fields

---

### 2. Search Word

Find all messages containing an exact word match.

**Endpoint**: `GET /msg/search/:word`

**Example 1 - Search for "project"**:
```bash
curl http://localhost:8081/msg/search/project
```

**Expected Response**:
```json
{
  "results": [1, 5, 12, 23, 34, 42]
}
```
*Returns message IDs that contain the word "project"*

**Example 2 - Search for "meeting"**:
```bash
curl http://localhost:8081/msg/search/meeting
```

**Expected Response**:
```json
{
  "results": [8, 15, 27, 38]
}
```

**Example 3 - Word not found**:
```bash
curl http://localhost:8081/msg/search/xyz123
```

**Expected Response**:
```json
{
  "results": []
}
```

**How It Works**:
- Uses MsgTrie to perform O(word length) lookup
- Returns all message IDs where the exact word appears
- Case-sensitive matching
- Words are pre-indexed when messages are loaded/sent

**Common Search Terms** (from current database):
- `project` → Multiple messages about project work
- `code` → Messages about code reviews
- `meeting` → Messages about scheduled meetings
- `lunch` → Messages about lunch plans
- `demo` → Messages about demonstrations

---

### 3. Search Prefix

Find all messages containing words that START with a given prefix.

**Endpoint**: `GET /msg/prefix/:prefix`

**Example 1 - Search prefix "pro"**:
```bash
curl http://localhost:8081/msg/prefix/pro
```

**Expected Response**:
```json
{
  "results": [1, 5, 12, 23, 34, 42, 45, 48]
}
```
*Finds messages with words like: "project", "progress", "problem", "productive"*

**Example 2 - Search prefix "me"**:
```bash
curl http://localhost:8081/msg/prefix/me
```

**Expected Response**:
```json
{
  "results": [8, 15, 27, 38, 40]
}
```
*Finds messages with words like: "meeting", "message", "me"*

**Example 3 - Single letter prefix**:
```bash
curl http://localhost:8081/msg/prefix/t
```

**Expected Response**:
```json
{
  "results": [1, 2, 3, 5, 7, 9, 11, 13, 15, 18, 20, 22, 25, 28, 30, 33, 35, 38, 40, 42, 45, 48, 50]
}
```
*Finds messages with words starting with "t": "the", "to", "tomorrow", "today", "thanks", "testing"*

**How It Works**:
- Uses MsgTrie's prefix traversal for O(prefix length) lookup
- Returns all messages containing ANY word starting with the prefix
- More flexible than exact word search
- Useful for autocomplete and fuzzy search

**Common Prefixes to Try**:
- `co` → code, could, come, collaboration
- `tes` → test, testing
- `wor` → work, working, workflow
- `re` → review, ready, result

---

### 4. Top K Messages

Get the top K users that a given user has messaged most frequently.

**Endpoint**: `GET /msg/topk/:userId/:k`

**Example 1 - Top 5 conversations for user 1**:
```bash
curl http://localhost:8081/msg/topk/1/5
```

**Expected Response**:
```json
{
  "messages": [
    { "userId": 2, "weight": 8 },
    { "userId": 3, "weight": 6 },
    { "userId": 5, "weight": 5 },
    { "userId": 7, "weight": 4 },
    { "userId": 4, "weight": 3 }
  ]
}
```
*User 1 has messaged user 2 most (8 times), then user 3 (6 times), etc.*

**Example 2 - Top 3 conversations for user 5**:
```bash
curl http://localhost:8081/msg/topk/5/3
```

**Expected Response**:
```json
{
  "messages": [
    { "userId": 1, "weight": 5 },
    { "userId": 8, "weight": 4 },
    { "userId": 10, "weight": 3 }
  ]
}
```

**Example 3 - User with few interactions**:
```bash
curl http://localhost:8081/msg/topk/20/5
```

**Expected Response**:
```json
{
  "messages": [
    { "userId": 1, "weight": 2 },
    { "userId": 15, "weight": 1 }
  ]
}
```
*If user has fewer than K interactions, returns all available*

**How It Works**:
- Uses ConversationGraph to count interactions
- Implements heap-based Top-K algorithm
- Weight = number of messages exchanged (sent + received)
- Sorted in descending order by weight

**Use Cases**:
- Identify closest contacts
- Suggest conversation resumption
- Analytics dashboard showing most active chats

---

### 5. Friend Suggestions

Suggest new friends based on messaging patterns (mutual contacts in conversation graph).

**Endpoint**: `GET /msg/suggestions/:userId/:k`

**Example 1 - Get 5 friend suggestions for user 1**:
```bash
curl http://localhost:8081/msg/suggestions/1/5
```

**Expected Response**:
```json
{
  "friends": [6, 9, 11, 14, 16]
}
```
*Users that user 1's contacts frequently message, but user 1 hasn't messaged yet*

**Example 2 - Get 3 suggestions for user 10**:
```bash
curl http://localhost:8081/msg/suggestions/10/3
```

**Expected Response**:
```json
{
  "friends": [7, 13, 18]
}
```

**Example 3 - User with extensive network**:
```bash
curl http://localhost:8081/msg/suggestions/5/10
```

**Expected Response**:
```json
{
  "friends": [2, 4, 9, 12, 15, 17, 19]
}
```
*May return fewer than K if fewer suggestions are available*

**How It Works**:
- Analyzes ConversationGraph connections
- Finds friends-of-friends (2nd degree connections)
- Excludes users already in direct contact
- Ranks by number of mutual connections
- Uses graph traversal algorithms

**Algorithm Logic**:
1. Get all users that `:userId` has messaged (1st degree)
2. Find users that those contacts have messaged (2nd degree)
3. Filter out `:userId` and existing connections
4. Return top K by connection strength

**Use Cases**:
- "People you may know" feature
- Network expansion recommendations
- Community discovery

---

### 6. Mutual Interactions

Find all pairs of users that have mutual messaging interactions with a given user.

**Endpoint**: `GET /msg/mutual/:userId`

**Example 1 - Mutual interactions for user 1**:
```bash
curl http://localhost:8081/msg/mutual/1
```

**Expected Response**:
```json
{
  "mutual": [
    { "u1": 2, "u2": 3 },
    { "u1": 2, "u2": 5 },
    { "u1": 3, "u2": 7 },
    { "u1": 5, "u2": 7 }
  ]
}
```
*Shows pairs of user 1's contacts who also message each other*

**Example 2 - User with fewer connections**:
```bash
curl http://localhost:8081/msg/mutual/15
```

**Expected Response**:
```json
{
  "mutual": [
    { "u1": 1, "u2": 20 }
  ]
}
```

**Example 3 - User with no mutual interactions**:
```bash
curl http://localhost:8081/msg/mutual/19
```

**Expected Response**:
```json
{
  "mutual": []
}
```

**How It Works**:
- Gets all neighbors of `:userId` from ConversationGraph
- For each pair of neighbors, checks if they message each other
- Returns all such triangular relationships
- Useful for identifying tight-knit communities

**Visual Representation**:
```
User 1 ←→ User 2
   ↓         ↓
User 3 ←→ User 5

Mutual interactions for User 1:
- (2, 3) - Users 2 and 3 message each other
- (2, 5) - Users 2 and 5 message each other
- (3, 5) - Users 3 and 5 message each other
```

**Use Cases**:
- Find user's social circles
- Identify group chat candidates
- Analyze network cohesion

---

### 7. Popularity Ranking

Rank users by their messaging activity (total incoming and outgoing messages).

**Endpoint**: `GET /msg/rank/:top`

**Example 1 - Top 5 most active users**:
```bash
curl http://localhost:8081/msg/rank/5
```

**Expected Response**:
```json
{
  "rank": [
    { "userId": 1, "popularity": 24 },
    { "userId": 5, "popularity": 18 },
    { "userId": 2, "popularity": 16 },
    { "userId": 7, "popularity": 14 },
    { "userId": 3, "popularity": 12 }
  ]
}
```
*User 1 is most active with 24 total messages (sent + received)*

**Example 2 - Top 10 users**:
```bash
curl http://localhost:8081/msg/rank/10
```

**Expected Response**:
```json
{
  "rank": [
    { "userId": 1, "popularity": 24 },
    { "userId": 5, "popularity": 18 },
    { "userId": 2, "popularity": 16 },
    { "userId": 7, "popularity": 14 },
    { "userId": 3, "popularity": 12 },
    { "userId": 8, "popularity": 11 },
    { "userId": 10, "popularity": 9 },
    { "userId": 4, "popularity": 8 },
    { "userId": 6, "popularity": 7 },
    { "userId": 12, "popularity": 6 }
  ]
}
```

**Example 3 - Top 3 (minimum)**:
```bash
curl http://localhost:8081/msg/rank/3
```

**Expected Response**:
```json
{
  "rank": [
    { "userId": 1, "popularity": 24 },
    { "userId": 5, "popularity": 18 },
    { "userId": 2, "popularity": 16 }
  ]
}
```

**How It Works**:
- Aggregates all interactions from ConversationGraph
- Popularity score = total edges (sent messages + received messages)
- Uses heap sort to get top N efficiently
- O(n log k) complexity where k is the number requested

**Popularity Calculation**:
```
User 1:
- Sent messages to: 2, 3, 5, 7 (multiple times)
- Received messages from: 2, 3, 5, 7 (multiple times)
- Total interactions counted: 24

User 20:
- Sent messages to: 1 (once)
- Received messages from: 1 (once)
- Total interactions counted: 2
```

**Use Cases**:
- Identify influencers and super-users
- Leaderboards for engagement
- Network analysis and insights
- Moderation prioritization

---

### 8. Shortest Path

Find the shortest messaging chain between two users.

**Endpoint**: `GET /msg/path/:src/:dest`

**Example 1 - Path from user 1 to user 10**:
```bash
curl http://localhost:8081/msg/path/1/10
```

**Expected Response**:
```json
{
  "path": [1, 5, 10]
}
```
*User 1 → User 5 → User 10 (2 hops)*

**Example 2 - Direct connection**:
```bash
curl http://localhost:8081/msg/path/1/2
```

**Expected Response**:
```json
{
  "path": [1, 2]
}
```
*User 1 → User 2 (direct, 1 hop)*

**Example 3 - Longer path**:
```bash
curl http://localhost:8081/msg/path/1/20
```

**Expected Response**:
```json
{
  "path": [1, 3, 15, 20]
}
```
*User 1 → User 3 → User 15 → User 20 (3 hops)*

**Example 4 - No path exists**:
```bash
curl http://localhost:8081/msg/path/1/999
```

**Expected Response**:
```json
{
  "path": []
}
```
*Empty array means no messaging connection exists*

**Example 5 - Same user**:
```bash
curl http://localhost:8081/msg/path/5/5
```

**Expected Response**:
```json
{
  "path": [5]
}
```
*Path to self contains only the user*

**How It Works**:
- Uses BFS (Breadth-First Search) on ConversationGraph
- Finds shortest path in unweighted graph
- O(V + E) complexity where V = users, E = message interactions
- Returns array of user IDs from source to destination

**Path Interpretation**:
```
Path: [1, 5, 10]

Meaning:
- User 1 has messaged User 5
- User 5 has messaged User 10
- Therefore, introduction chain exists: 1 → 5 → 10
```

**Use Cases**:
- "How are you connected?" feature
- Six degrees of separation analysis
- Message routing in chat systems
- Network distance metrics

---

## Database Structure

### messages.json Format

```json
{
  "messages": [
    {
      "id": 1,
      "senderId": 1,
      "receiverId": 2,
      "text": "Hey Bob! How's the graph project going?",
      "timestamp": 1
    },
    {
      "id": 2,
      "senderId": 2,
      "receiverId": 1,
      "text": "Great! Just implemented BFS. You?",
      "timestamp": 2
    }
    // ... more messages
  ]
}
```

### Current Database Stats

- **Total Messages**: 50+
- **Active Users**: 20 (users 1-20)
- **Topics Covered**: 
  - Project discussions
  - Code reviews
  - Meeting coordination
  - Technical questions
  - Casual conversations

### Sample Messages You Can Search:

| Message ID | Sender | Receiver | Text Snippet | Searchable Words |
|------------|--------|----------|--------------|------------------|
| 1 | 1 | 2 | "How's the graph project going?" | graph, project, going |
| 2 | 2 | 1 | "Just implemented BFS" | implemented, BFS |
| 5 | 1 | 3 | "want to work on the API" | work, API |
| 8 | 3 | 5 | "meeting at 3pm tomorrow" | meeting, tomorrow |
| 15 | 5 | 8 | "code review session" | code, review, session |

---

## Testing Guide

### Quick Test Suite

#### 1. Test Word Search
```bash
# Should find multiple messages about projects
curl http://localhost:8081/msg/search/project

# Should find messages about code
curl http://localhost:8081/msg/search/code

# Should return empty array
curl http://localhost:8081/msg/search/nonexistentword
```

#### 2. Test Prefix Search
```bash
# Find all words starting with "pro"
curl http://localhost:8081/msg/prefix/pro

# Find all words starting with "co"
curl http://localhost:8081/msg/prefix/co
```

#### 3. Test Analytics
```bash
# Get top 5 conversations for user 1
curl http://localhost:8081/msg/topk/1/5

# Get friend suggestions for user 1
curl http://localhost:8081/msg/suggestions/1/5

# Get top 10 most active users
curl http://localhost:8081/msg/rank/10
```

#### 4. Test Path Finding
```bash
# Find path from user 1 to user 10
curl http://localhost:8081/msg/path/1/10

# Find path between users 5 and 15
curl http://localhost:8081/msg/path/5/15
```

#### 5. Test Message Sending
```bash
# Send a new message
curl -X POST http://localhost:8081/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1,"receiverId":20,"text":"Testing the messaging API!"}'

# Verify it's searchable
curl http://localhost:8081/msg/search/Testing

# Check messages.json file - should have new message
```

### Testing with PowerShell

```powershell
# Test word search
Invoke-RestMethod -Uri "http://localhost:8081/msg/search/project" | ConvertTo-Json

# Test top K
Invoke-RestMethod -Uri "http://localhost:8081/msg/topk/1/5" | ConvertTo-Json

# Send message
$body = @{
    senderId = 1
    receiverId = 3
    text = "Hello from PowerShell!"
} | ConvertTo-Json

Invoke-RestMethod -Uri "http://localhost:8081/msg/send" `
  -Method Post `
  -Body $body `
  -ContentType "application/json"
```

### Expected Performance

| Operation | Complexity | Typical Response Time |
|-----------|------------|----------------------|
| Send Message | O(words in message) | < 10ms |
| Search Word | O(word length) | < 5ms |
| Search Prefix | O(prefix length + results) | < 10ms |
| Top K Messages | O(neighbors + k log k) | < 20ms |
| Friend Suggestions | O(2nd degree neighbors) | < 30ms |
| Mutual Interactions | O(neighbors²) | < 50ms |
| Popularity Ranking | O(users + k log k) | < 30ms |
| Shortest Path | O(users + messages) | < 40ms |

---

## Error Handling

### Common Errors

**400 Bad Request**
```json
"Invalid JSON"
```
*Fix*: Check request body format for POST requests

**404 Not Found**
- User doesn't exist in system
- Invalid endpoint URL
*Fix*: Verify user IDs and endpoint paths

**Empty Results**
```json
{ "results": [] }
{ "path": [] }
{ "friends": [] }
```
*Not an error* - indicates no data found for query

---

## Tips & Best Practices

### Optimizing Searches

1. **Use Prefix Search for Flexibility**: If exact word search returns nothing, try prefix search
2. **Start with Shorter Prefixes**: Prefix "c" will return more results than "cod"
3. **Check Case Sensitivity**: Searches are case-sensitive, so "Project" ≠ "project"

### Understanding Weights

- **Top K Weights**: Higher = more messages exchanged
- **Popularity Scores**: Combines both sent and received messages
- **Path Length**: Fewer nodes = closer connection

### Data Persistence

- Messages automatically save on send
- Server loads all messages on startup
- No need to manually trigger saves
- Check `storage/local_db/messages.json` to verify persistence

---

## Architecture Overview

```
┌─────────────────┐
│   POST /send    │
└────────┬────────┘
         │
         ▼
┌─────────────────┐      ┌──────────────┐
│  MessageStore   │◄─────┤   MsgTrie    │
│  (All Messages) │      │ (Word Index) │
└────────┬────────┘      └──────────────┘
         │                      ▲
         │                      │
         ▼                      │
┌─────────────────┐             │
│ ConversationGrph│─────────────┘
│  (Interactions) │
└────────┬────────┘
         │
         ▼
┌─────────────────┐
│  messages.json  │
│   (Persistent)  │
└─────────────────┘
```

**Data Flow**:
1. Message received via API
2. Stored in MessageStore
3. Words extracted and indexed in MsgTrie
4. Interaction recorded in ConversationGraph
5. All data saved to messages.json
6. All 8 APIs query these structures

---

## Troubleshooting

### Server Not Responding
```bash
# Check if server is running
curl http://localhost:8081

# Restart server
cd backend
./server.exe
```

### Messages Not Persisting
- Verify `storage/local_db/messages.json` exists
- Check file permissions (read/write)
- Ensure no JSON syntax errors

### Search Returns No Results
- Verify spelling (case-sensitive)
- Try prefix search instead
- Check if messages were loaded: look for "  Loaded X messages" on startup

### Invalid JSON Error
- Use proper JSON format in POST body
- Include Content-Type header
- Validate JSON syntax before sending

---

## Additional Resources

- **Full API List**: `GET http://localhost:8081/` - Returns all available endpoints
- **Graph APIs**: See main README for friendship and social graph APIs
- **User APIs**: See main README for user management endpoints

---

**Last Updated**: January 2024  
**Version**: 1.0  
**Server Port**: 8081  
**Database**: `storage/local_db/messages.json`
