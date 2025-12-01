# Postman API Testing Guide

Complete guide for testing all API endpoints in the Social Graph Explorer backend.

## Server Configuration

**Base URL:** `http://localhost:8080`

**Server Port:** 8080

**Start Server:** Compile and run `server.cpp` from `backend/api/`

---

## Table of Contents

1. [Health Check](#health-check)
2. [User Management](#user-management)
3. [Graph Operations](#graph-operations)
4. [Messaging System](#messaging-system)

---

## Health Check

### 1. Server Health Check

**Endpoint:** `GET /health`

**URL:** `http://localhost:8080/health`

**Expected Response:**
```json
{
  "status": "ok",
  "message": "Server is running"
}
```

---

## User Management

### 1. Register New User

**Endpoint:** `POST /api/users/register`

**URL:** `http://localhost:8080/api/users/register`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "username": "alice",
  "password": "alice123"
}
```

**Expected Response (201):**
```json
{
  "success": true,
  "message": "User registered successfully"
}
```

**Error Response (400):**
```json
{
  "success": false,
  "error": "Username and password required"
}
```

---

### 2. User Login

**Endpoint:** `POST /api/users/login`

**URL:** `http://localhost:8080/api/users/login`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "username": "alice",
  "password": "alice123"
}
```

**Expected Response (200):**
```json
{
  "success": true,
  "message": "Login successful",
  "user": {
    "id": 1,
    "username": "alice"
  }
}
```

**Error Response (401):**
```json
{
  "success": false,
  "error": "Invalid username or password"
}
```

---

### 3. Search Users by Prefix

**Endpoint:** `GET /api/users/search`

**URL:** `http://localhost:8080/api/users/search?prefix=ali`

**Query Parameters:**
- `prefix` (string): Search prefix for usernames

**Expected Response:**
```json
{
  "success": true,
  "users": ["alice", "alicia", "alison"],
  "count": 3
}
```

---

### 4. Get User by ID

**Endpoint:** `GET /api/users/:id`

**URL:** `http://localhost:8080/api/users/1`

**Expected Response:**
```json
{
  "success": true,
  "user": {
    "id": 1,
    "username": "alice",
    "posts": [
      {"index": 0, "content": "Hello world!"},
      {"index": 1, "content": "My first post"}
    ],
    "postCount": 2
  }
}
```

**Error Response (404):**
```json
{
  "success": false,
  "error": "User not found"
}
```

---

### 5. Delete User

**Endpoint:** `DELETE /api/users/:id`

**URL:** `http://localhost:8080/api/users/1`

**Expected Response (200):**
```json
{
  "success": true,
  "message": "User deleted successfully"
}
```

---

### 6. Create Post

**Endpoint:** `POST /api/users/:id/posts`

**URL:** `http://localhost:8080/api/users/1/posts`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "content": "This is my new post!"
}
```

**Expected Response (201):**
```json
{
  "success": true,
  "message": "Post created successfully"
}
```

---

### 7. Get User Posts

**Endpoint:** `GET /api/users/:id/posts`

**URL:** `http://localhost:8080/api/users/1/posts`

**Expected Response:**
```json
{
  "success": true,
  "posts": [
    {"index": 0, "content": "Hello world!"},
    {"index": 1, "content": "My first post"}
  ],
  "count": 2
}
```

---

### 8. Delete Post

**Endpoint:** `DELETE /api/users/:id/posts/:postIndex`

**URL:** `http://localhost:8080/api/users/1/posts/0`

**Expected Response (200):**
```json
{
  "success": true,
  "message": "Post deleted successfully"
}
```

---

## Graph Operations

### 1. Get User Friends

**Endpoint:** `GET /graph/friends/:id`

**URL:** `http://localhost:8080/graph/friends/1`

**Expected Response:**
```json
{
  "success": true,
  "userId": 1,
  "friends": [
    {"id": 2},
    {"id": 3},
    {"id": 5}
  ],
  "count": 3
}
```

---

### 2. Add Friendship

**Endpoint:** `POST /graph/addFriend`

**URL:** `http://localhost:8080/graph/addFriend`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "u": 1,
  "v": 2
}
```

**Expected Response:**
```json
{
  "success": true,
  "message": "Friendship created"
}
```

**Note:** Creates bidirectional friendship (both u→v and v→u)

---

### 3. Remove Friendship

**Endpoint:** `POST /graph/removeFriend`

**URL:** `http://localhost:8080/graph/removeFriend`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "u": 1,
  "v": 2
}
```

**Expected Response:**
```json
{
  "success": true,
  "message": "Friendship removed"
}
```

**Error Response:**
```json
{
  "success": false,
  "error": "Friendship does not exist"
}
```

---

### 4. Get Graph Statistics

**Endpoint:** `GET /graph/stats`

**URL:** `http://localhost:8080/graph/stats`

**Expected Response:**
```json
{
  "success": true,
  "nodeCount": 10,
  "edgeCount": 15,
  "components": 2,
  "isConnected": false,
  "density": 0.3333,
  "averageDegree": 3.0
}
```

---

### 5. Check if Users Connected

**Endpoint:** `GET /graph/connected/:u/:v`

**URL:** `http://localhost:8080/graph/connected/1/5`

**Expected Response:**
```json
{
  "success": true,
  "u": 1,
  "v": 5,
  "connected": true
}
```

---

### 6. Get Connected Components Count

**Endpoint:** `GET /graph/components`

**URL:** `http://localhost:8080/graph/components`

**Expected Response:**
```json
{
  "success": true,
  "components": 2
}
```

---

## Messaging System

### 1. Send Message

**Endpoint:** `POST /msg/send`

**URL:** `http://localhost:8080/msg/send`

**Headers:**
- `Content-Type: application/json`

**Request Body:**
```json
{
  "senderId": 1,
  "receiverId": 2,
  "text": "Hello! How are you doing today?"
}
```

**Expected Response:**
```json
{
  "success": true,
  "message": "Message sent successfully",
  "messageId": 1,
  "wordsIndexed": 6
}
```

**Description:**
- Stores message in MessageStore
- Extracts and indexes words in MsgTrie
- Updates ConversationGraph with interaction weight

---

### 2. Search Messages by Exact Word

**Endpoint:** `GET /msg/search/:word`

**URL:** `http://localhost:8080/msg/search/hello`

**Expected Response:**
```json
{
  "success": true,
  "query": "hello",
  "messages": [
    {
      "id": 1,
      "senderId": 1,
      "receiverId": 2,
      "text": "Hello! How are you doing today?",
      "timestamp": 1701234567
    }
  ],
  "count": 1
}
```

---

### 3. Search Messages by Prefix

**Endpoint:** `GET /msg/prefix/:prefix`

**URL:** `http://localhost:8080/msg/prefix/hel`

**Expected Response:**
```json
{
  "success": true,
  "prefix": "hel",
  "messages": [
    {
      "id": 1,
      "senderId": 1,
      "receiverId": 2,
      "text": "Hello! How are you doing today?"
    },
    {
      "id": 5,
      "senderId": 3,
      "receiverId": 1,
      "text": "Can you help me with this?"
    }
  ],
  "count": 2
}
```

**Description:** Finds all messages containing words starting with the given prefix

---

### 4. Get Top K Interactions

**Endpoint:** `GET /msg/topk/:userId/:k`

**URL:** `http://localhost:8080/msg/topk/1/5`

**URL Parameters:**
- `userId` (int): User ID
- `k` (int): Number of top interactions to return

**Expected Response:**
```json
{
  "success": true,
  "userId": 1,
  "k": 5,
  "topInteractions": [
    {"userId": 2, "weight": 15},
    {"userId": 3, "weight": 12},
    {"userId": 5, "weight": 8},
    {"userId": 7, "weight": 5},
    {"userId": 9, "weight": 3}
  ],
  "count": 5
}
```

**Description:** Returns users with highest message interaction weights (using MsgHeap)

---

### 5. Get Friend Suggestions

**Endpoint:** `GET /msg/suggestions/:userId/:k`

**URL:** `http://localhost:8080/msg/suggestions/1/3`

**URL Parameters:**
- `userId` (int): User ID to get suggestions for
- `k` (int): Number of suggestions to return

**Expected Response:**
```json
{
  "success": true,
  "userId": 1,
  "suggestions": [
    {
      "userId": 7,
      "mutualInteractions": 3,
      "score": 8.5
    },
    {
      "userId": 9,
      "mutualInteractions": 2,
      "score": 6.2
    },
    {
      "userId": 4,
      "mutualInteractions": 2,
      "score": 5.8
    }
  ],
  "count": 3
}
```

**Description:** Suggests friends based on mutual message interactions and frequency

---

### 6. Get Mutual Interactions

**Endpoint:** `GET /msg/mutual/:userId`

**URL:** `http://localhost:8080/msg/mutual/1`

**Expected Response:**
```json
{
  "success": true,
  "userId": 1,
  "mutualInteractions": [
    {
      "userId": 2,
      "mutualWith": [3, 5, 7],
      "count": 3
    },
    {
      "userId": 3,
      "mutualWith": [2, 5],
      "count": 2
    }
  ],
  "totalMutual": 2
}
```

**Description:** Finds users who have mutual message connections with the given user

---

### 7. Get Popularity Ranking

**Endpoint:** `GET /msg/rank/:topN`

**URL:** `http://localhost:8080/msg/rank/10`

**URL Parameters:**
- `topN` (int): Number of top users to return

**Expected Response:**
```json
{
  "success": true,
  "topN": 10,
  "ranking": [
    {"rank": 1, "userId": 5, "score": 42},
    {"rank": 2, "userId": 2, "score": 38},
    {"rank": 3, "userId": 1, "score": 35},
    {"rank": 4, "userId": 7, "score": 28},
    {"rank": 5, "userId": 3, "score": 25}
  ],
  "count": 5
}
```

**Description:** Returns most popular users based on total message interaction weights

---

### 8. Find Shortest Message Path

**Endpoint:** `GET /msg/path/:src/:dest`

**URL:** `http://localhost:8080/msg/path/1/7`

**URL Parameters:**
- `src` (int): Source user ID
- `dest` (int): Destination user ID

**Expected Response:**
```json
{
  "success": true,
  "source": 1,
  "destination": 7,
  "path": [1, 2, 5, 7],
  "distance": 3,
  "exists": true
}
```

**No Path Response:**
```json
{
  "success": true,
  "source": 1,
  "destination": 99,
  "path": [],
  "distance": -1,
  "exists": false
}
```

**Description:** Uses BFS to find shortest path through message interaction network

---

## Testing Workflow

### Basic Testing Sequence

1. **Start Server**
   ```
   GET /health
   ```

2. **Register Users**
   ```
   POST /api/users/register (alice)
   POST /api/users/register (bob)
   POST /api/users/register (charlie)
   ```

3. **Create Friendships**
   ```
   POST /graph/addFriend (alice ↔ bob)
   POST /graph/addFriend (bob ↔ charlie)
   ```

4. **Send Messages**
   ```
   POST /msg/send (alice → bob: "Hello")
   POST /msg/send (bob → alice: "Hi there")
   POST /msg/send (bob → charlie: "Hey")
   ```

5. **Test Queries**
   ```
   GET /msg/search/hello
   GET /msg/topk/1/5
   GET /msg/suggestions/1/3
   GET /graph/stats
   ```

---

## Error Handling

All endpoints return appropriate HTTP status codes:

- **200 OK** - Successful GET request
- **201 Created** - Successful POST request (resource created)
- **400 Bad Request** - Invalid parameters or missing fields
- **401 Unauthorized** - Authentication failed
- **404 Not Found** - Resource not found
- **500 Internal Server Error** - Server error

**Standard Error Response:**
```json
{
  "success": false,
  "error": "Error description here"
}
```

---

## Postman Collection Setup

### 1. Create Environment Variables

- `base_url`: `http://localhost:8080`
- `user_id`: `1` (set after user creation)

### 2. Pre-request Scripts

For authentication endpoints, you can store tokens:
```javascript
pm.environment.set("userId", pm.response.json().user.id);
```

### 3. Test Scripts

Add validation tests:
```javascript
pm.test("Status code is 200", function () {
    pm.response.to.have.status(200);
});

pm.test("Response has success field", function () {
    var jsonData = pm.response.json();
    pm.expect(jsonData).to.have.property('success');
});
```

---

## Tips for Testing

1. **Use Variables** - Store IDs in Postman environment variables
2. **Test Ordering** - Run user creation before graph operations
3. **Clear State** - Restart server to reset all data
4. **Check Logs** - Server console shows registered routes on startup
5. **CORS** - All endpoints support CORS for frontend integration

---

## Common Issues

### Connection Refused
- Check if server is running on port 8080
- Verify firewall settings

### Invalid JSON
- Ensure `Content-Type: application/json` header is set
- Validate JSON syntax in request body

### 404 Not Found
- Check URL spelling and parameters
- Verify route is registered (check server startup logs)

### Empty Responses
- Create test data first (users, friendships, messages)
- Check if IDs exist in the system

---

## Additional Notes

- All POST endpoints require `Content-Type: application/json` header
- Server uses custom data structures (no STL containers except strings)
- Graph is bidirectional - adding friendship creates edge in both directions
- Message search is case-insensitive
- User IDs are auto-generated starting from 1

---

**Last Updated:** December 2, 2025

**Server Version:** 1.0

**API Version:** 1.0
