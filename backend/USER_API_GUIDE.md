# User API Documentation

Complete guide to all user management endpoints with real examples, expected outputs, and data persistence.

---

## 📋 Table of Contents

1. [Overview](#overview)
2. [Data Structures](#data-structures)
3. [API Endpoints](#api-endpoints)
   - [Register User](#1-register-user)
   - [Login User](#2-login-user)
   - [Search Users](#3-search-users)
   - [Get User](#4-get-user)
   - [Delete User](#5-delete-user)
   - [Create Post](#6-create-post)
   - [Get Posts](#7-get-posts)
   - [Delete Post](#8-delete-post)
4. [Database Structure](#database-structure)
5. [Testing Guide](#testing-guide)

---

## Overview

The user management system provides 8 comprehensive APIs for user authentication, profiles, and posts. All data is persisted in `storage/local_db/users.json` and managed through the UserManager class.

**Base URL**: `http://localhost:8081`

**Current Database**: 320 users with various posts and profiles.

---

## Data Structures

### UserManager
- **Purpose**: Manages all user operations and in-memory storage
- **Key Methods**: `registerUser()`, `authenticate()`, `addPost()`, `deletePost()`, `saveToFile()`
- **Features**: Automatic persistence, Trie-based search, password validation

### User
- **Fields**: id, username, password (hashed), bio, posts[], createdAt
- **Operations**: Create, Read, Update, Delete
- **Persistence**: Automatic save after all modifications

---

## API Endpoints

### 1. Register User

Create a new user account with username and password. Automatically persists to database.

**Endpoint**: `POST /api/users/register`

**Request Body**:
```json
{
  "username": "alice_wonderland",
  "password": "securepass123"
}
```

**Example cURL**:
```bash
curl -X POST http://localhost:8081/api/users/register \
  -H "Content-Type: application/json" \
  -d '{"username":"alice_wonderland","password":"securepass123"}'
```

**Expected Response (Success)**:
```json
{
  "success": true,
  "message": "User registered successfully",
  "userId": 321
}
```

**What Happens**:
1. Validates username (not empty, no duplicates)
2. Validates password (minimum length)
3. Creates user with unique ID
4. Adds to UserManager
5. **Automatically saved to users.json**

**Error Cases**:

**Username already taken**:
```json
{
  "success": false,
  "error": "Username already exists"
}
```

**Invalid username**:
```json
{
  "success": false,
  "error": "Username cannot be empty"
}
```

**Weak password**:
```json
{
  "success": false,
  "error": "Password must be at least 6 characters"
}
```

**Missing fields**:
```json
{
  "success": false,
  "error": "Username and password are required"
}
```

---

### 2. Login User

Authenticate a user with username and password.

**Endpoint**: `POST /api/users/login`

**Request Body**:
```json
{
  "username": "alice_wonderland",
  "password": "securepass123"
}
```

**Example cURL**:
```bash
curl -X POST http://localhost:8081/api/users/login \
  -H "Content-Type: application/json" \
  -d '{"username":"alice_wonderland","password":"securepass123"}'
```

**Expected Response (Success)**:
```json
{
  "success": true,
  "message": "Login successful",
  "userId": 321,
  "username": "alice_wonderland"
}
```

**Error Cases**:

**Invalid credentials**:
```json
{
  "success": false,
  "error": "Invalid username or password"
}
```

**User not found**:
```json
{
  "success": false,
  "error": "User not found"
}
```

**How It Works**:
- Looks up user by username
- Validates password match
- Returns user ID on success
- No session/token (stateless)

---

### 3. Search Users

Search for users by username prefix using Trie-based autocomplete.

**Endpoint**: `GET /api/users/search?prefix=...`

**Example 1 - Search for "ali"**:
```bash
curl "http://localhost:8081/api/users/search?prefix=ali"
```

**Expected Response**:
```json
{
  "success": true,
  "results": [
    {
      "id": 1,
      "username": "alice_smith"
    },
    {
      "id": 15,
      "username": "alicia_keys"
    },
    {
      "id": 42,
      "username": "ali_muhammad"
    }
  ],
  "count": 3
}
```

**Example 2 - Search for "john"**:
```bash
curl "http://localhost:8081/api/users/search?prefix=john"
```

**Expected Response**:
```json
{
  "success": true,
  "results": [
    {
      "id": 5,
      "username": "john_doe"
    },
    {
      "id": 23,
      "username": "johnny_bravo"
    }
  ],
  "count": 2
}
```

**Example 3 - No results**:
```bash
curl "http://localhost:8081/api/users/search?prefix=xyz"
```

**Expected Response**:
```json
{
  "success": true,
  "results": [],
  "count": 0
}
```

**Example 4 - Single letter**:
```bash
curl "http://localhost:8081/api/users/search?prefix=a"
```

**Expected Response**:
```json
{
  "success": true,
  "results": [
    {"id": 1, "username": "alice_smith"},
    {"id": 8, "username": "anna_jones"},
    {"id": 15, "username": "alicia_keys"},
    {"id": 22, "username": "andrew_wilson"},
    {"id": 42, "username": "ali_muhammad"}
    // ... more users starting with 'a'
  ],
  "count": 15
}
```

**How It Works**:
- **Algorithm**: Trie prefix traversal
- **Complexity**: O(prefix length + results)
- **Case-sensitive**: "Ali" ≠ "ali"
- **Real-time**: Perfect for autocomplete

**Use Cases**:
- User search/autocomplete
- Friend finder
- Mention suggestions (@username)
- User directory

---

### 4. Get User

Get complete user profile including all posts.

**Endpoint**: `GET /api/users/:id`

**Example Request**:
```bash
curl http://localhost:8081/api/users/1
```

**Expected Response**:
```json
{
  "success": true,
  "user": {
    "id": 1,
    "username": "alice_smith",
    "bio": "Software engineer passionate about graphs",
    "posts": [
      {
        "id": 0,
        "content": "Just implemented BFS traversal! 🎉",
        "timestamp": 1702123456,
        "likes": 0
      },
      {
        "id": 1,
        "content": "Working on the social graph project",
        "timestamp": 1702234567,
        "likes": 0
      },
      {
        "id": 2,
        "content": "Anyone want to grab coffee?",
        "timestamp": 1702345678,
        "likes": 0
      }
    ],
    "postCount": 3,
    "friendCount": 5,
    "createdAt": 1701000000
  }
}
```

**Example - User with no posts**:
```bash
curl http://localhost:8081/api/users/100
```

**Expected Response**:
```json
{
  "success": true,
  "user": {
    "id": 100,
    "username": "new_user",
    "bio": "",
    "posts": [],
    "postCount": 0,
    "friendCount": 2,
    "createdAt": 1702500000
  }
}
```

**Error Case - User not found**:
```bash
curl http://localhost:8081/api/users/9999
```

**Expected Response**:
```json
{
  "success": false,
  "error": "User not found"
}
```

**How It Works**:
- O(1) lookup by user ID
- Includes all user data and posts
- Real-time friend count from graph

**Use Cases**:
- User profile page
- Feed generation
- User analytics
- Profile display

---

### 5. Delete User

Permanently delete a user and all their data. Automatically persists to database.

**Endpoint**: `DELETE /api/users/:id`

**Example Request**:
```bash
curl -X DELETE http://localhost:8081/api/users/321
```

**Expected Response (Success)**:
```json
{
  "success": true,
  "message": "User deleted successfully"
}
```

**What Happens**:
1. Removes user from UserManager
2. Removes from search Trie
3. **Does NOT remove friendships** (handled separately in graph)
4. **Automatically saved to users.json**

**Error Case**:
```json
{
  "success": false,
  "error": "User not found"
}
```

**⚠️ Warning**: This operation is permanent and cannot be undone!

**Best Practice**: 
- Remove friendships first using `/graph/removeFriend`
- Then delete user account
- Or implement soft delete (mark as deleted, don't remove)

---

### 6. Create Post

Create a new post for a user. Automatically persists to database.

**Endpoint**: `POST /api/users/:id/posts`

**Request Body**:
```json
{
  "content": "Just finished the algorithm module! Time to celebrate 🎊"
}
```

**Example cURL**:
```bash
curl -X POST http://localhost:8081/api/users/1/posts \
  -H "Content-Type: application/json" \
  -d '{"content":"Just finished the algorithm module! Time to celebrate 🎊"}'
```

**Expected Response (Success)**:
```json
{
  "success": true,
  "message": "Post created successfully",
  "postId": 3
}
```

**What Happens**:
1. Validates user exists
2. Validates content (not empty, max length)
3. Creates post with unique ID and timestamp
4. Adds to user's post array
5. **Automatically saved to users.json**

**Error Cases**:

**User not found**:
```json
{
  "success": false,
  "error": "User not found"
}
```

**Empty content**:
```json
{
  "success": false,
  "error": "Post content cannot be empty"
}
```

**Content too long**:
```json
{
  "success": false,
  "error": "Post content exceeds maximum length (500 characters)"
}
```

**Example - Long post**:
```bash
curl -X POST http://localhost:8081/api/users/1/posts \
  -H "Content-Type: application/json" \
  -d '{"content":"This is a really long post that contains a lot of information about my day..."}'
```

---

### 7. Get Posts

Get all posts for a specific user.

**Endpoint**: `GET /api/users/:id/posts`

**Example Request**:
```bash
curl http://localhost:8081/api/users/1/posts
```

**Expected Response**:
```json
{
  "success": true,
  "userId": 1,
  "posts": [
    {
      "id": 0,
      "content": "Just implemented BFS traversal! 🎉",
      "timestamp": 1702123456,
      "likes": 0
    },
    {
      "id": 1,
      "content": "Working on the social graph project",
      "timestamp": 1702234567,
      "likes": 0
    },
    {
      "id": 2,
      "content": "Anyone want to grab coffee?",
      "timestamp": 1702345678,
      "likes": 0
    }
  ],
  "count": 3
}
```

**Example - User with no posts**:
```bash
curl http://localhost:8081/api/users/100/posts
```

**Expected Response**:
```json
{
  "success": true,
  "userId": 100,
  "posts": [],
  "count": 0
}
```

**How It Works**:
- O(1) lookup by user ID
- Returns all posts in chronological order
- Includes metadata (timestamp, likes)

**Use Cases**:
- User timeline/feed
- Profile post list
- Post analytics
- Content moderation

---

### 8. Delete Post

Delete a specific post by index. Automatically persists to database.

**Endpoint**: `DELETE /api/users/:id/posts/:postIndex`

**Example Request** (Delete post at index 1):
```bash
curl -X DELETE http://localhost:8081/api/users/1/posts/1
```

**Expected Response (Success)**:
```json
{
  "success": true,
  "message": "Post deleted successfully"
}
```

**What Happens**:
1. Validates user exists
2. Validates post index is valid
3. Removes post from user's post array
4. **Automatically saved to users.json**

**Error Cases**:

**User not found**:
```json
{
  "success": false,
  "error": "User not found"
}
```

**Invalid post index**:
```bash
curl -X DELETE http://localhost:8081/api/users/1/posts/999
```

**Expected Response**:
```json
{
  "success": false,
  "error": "Post not found"
}
```

**Post Indexing**:
```
User has posts:
  Index 0: "First post"
  Index 1: "Second post"
  Index 2: "Third post"

Delete index 1 →

User now has posts:
  Index 0: "First post"
  Index 1: "Third post"  ← Indices shift down
```

**⚠️ Warning**: Deleting a post shifts all subsequent indices down by 1!

---

## Database Structure

### users.json Format

```json
{
  "users": [
    {
      "id": 1,
      "username": "alice_smith",
      "password": "$hashed_password$",
      "bio": "Software engineer passionate about graphs",
      "posts": [
        {
          "id": 0,
          "content": "Just implemented BFS traversal! 🎉",
          "timestamp": 1702123456,
          "likes": 0
        }
      ],
      "createdAt": 1701000000
    },
    {
      "id": 2,
      "username": "bob_jones",
      "password": "$hashed_password$",
      "bio": "Data structures enthusiast",
      "posts": [],
      "createdAt": 1701100000
    }
    // ... more users
  ]
}
```

### Current Database Stats

- **Total Users**: 320
- **Active Users**: Users with posts (150+)
- **Average Posts**: 2-3 per user
- **Usernames**: Unique, lowercase with underscores

---

## Testing Guide

### Quick Test Suite

#### 1. Test Registration & Login
```bash
# Register new user
curl -X POST http://localhost:8081/api/users/register \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user","password":"test123"}'

# Login
curl -X POST http://localhost:8081/api/users/login \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user","password":"test123"}'

# Try invalid login
curl -X POST http://localhost:8081/api/users/login \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user","password":"wrong"}'
```

#### 2. Test User Search
```bash
# Search for "test"
curl "http://localhost:8081/api/users/search?prefix=test"

# Search for "ali"
curl "http://localhost:8081/api/users/search?prefix=ali"

# Search for single letter
curl "http://localhost:8081/api/users/search?prefix=a"
```

#### 3. Test Post Operations
```bash
# Create post
curl -X POST http://localhost:8081/api/users/1/posts \
  -H "Content-Type: application/json" \
  -d '{"content":"Testing the API!"}'

# Get all posts
curl http://localhost:8081/api/users/1/posts

# Get user with posts
curl http://localhost:8081/api/users/1

# Delete post (index 0)
curl -X DELETE http://localhost:8081/api/users/1/posts/0
```

#### 4. Test User Deletion
```bash
# Get user first
curl http://localhost:8081/api/users/321

# Delete user
curl -X DELETE http://localhost:8081/api/users/321

# Verify deletion
curl http://localhost:8081/api/users/321
```

### Testing with PowerShell

```powershell
# Register user
$body = @{
    username = "powershell_user"
    password = "secure123"
} | ConvertTo-Json

Invoke-RestMethod -Uri "http://localhost:8081/api/users/register" `
  -Method Post `
  -Body $body `
  -ContentType "application/json"

# Search users
Invoke-RestMethod -Uri "http://localhost:8081/api/users/search?prefix=pow" | ConvertTo-Json

# Create post
$post = @{
    content = "Posted from PowerShell!"
} | ConvertTo-Json

Invoke-RestMethod -Uri "http://localhost:8081/api/users/1/posts" `
  -Method Post `
  -Body $post `
  -ContentType "application/json"

# Get user
Invoke-RestMethod -Uri "http://localhost:8081/api/users/1" | ConvertTo-Json
```

### Expected Performance

| Operation | Complexity | Typical Response Time |
|-----------|------------|----------------------|
| Register User | O(1) | < 15ms (includes file save) |
| Login User | O(1) | < 5ms |
| Search Users | O(prefix + results) | < 10ms |
| Get User | O(1) | < 5ms |
| Delete User | O(1) | < 15ms (includes file save) |
| Create Post | O(1) | < 15ms (includes file save) |
| Get Posts | O(1) | < 5ms |
| Delete Post | O(posts) | < 15ms (includes file save) |

---

## Error Handling

### HTTP Status Codes

- **200 OK**: Successful operation
- **400 Bad Request**: Invalid input (missing fields, validation errors)
- **401 Unauthorized**: Invalid credentials (login)
- **404 Not Found**: User not found
- **500 Internal Server Error**: Server error

### Common Errors

**Registration Errors**:
- Username already exists
- Username cannot be empty
- Password too short
- Missing required fields

**Login Errors**:
- Invalid username or password
- User not found
- Missing credentials

**Post Errors**:
- Post content empty
- Content exceeds max length
- User not found
- Invalid post index

---

## Tips & Best Practices

### Password Security
- Minimum 6 characters (configurable)
- Stored hashed (never plain text)
- Use strong passwords in production

### Username Guidelines
- Lowercase recommended
- Use underscores for spaces
- Must be unique
- Keep under 30 characters

### Post Management
- Posts indexed from 0
- Deleting shifts indices
- Consider soft delete for posts
- Max content: 500 characters

### Data Persistence
- All operations auto-save to users.json
- Server loads all users on startup
- No manual save needed
- Atomic operations

---

## Integration Examples

### Frontend React Component

```javascript
// User Registration
const registerUser = async (username, password) => {
  const response = await fetch('http://localhost:8081/api/users/register', {
    method: 'POST',
    headers: { 'Content-Type': 'application/json' },
    body: JSON.stringify({ username, password })
  });
  return await response.json();
};

// User Search (Autocomplete)
const searchUsers = async (prefix) => {
  const response = await fetch(
    `http://localhost:8081/api/users/search?prefix=${prefix}`
  );
  const data = await response.json();
  return data.results;
};

// Create Post
const createPost = async (userId, content) => {
  const response = await fetch(
    `http://localhost:8081/api/users/${userId}/posts`,
    {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ content })
    }
  );
  return await response.json();
};

// Get User Profile
const getUserProfile = async (userId) => {
  const response = await fetch(`http://localhost:8081/api/users/${userId}`);
  return await response.json();
};
```

---

## Architecture Overview

```
┌─────────────────┐
│ User Operations │
│ (CRUD + Auth)   │
└────────┬────────┘
         │
         ▼
┌─────────────────┐      ┌──────────────┐
│  UserManager    │◄─────┤     Trie     │
│  (320 users)    │      │   (Search)   │
└────────┬────────┘      └──────────────┘
         │
         ▼
┌─────────────────┐
│   users.json    │
│  (Persistent)   │
└─────────────────┘
```

---

## Additional Resources

- **Graph API**: See [GRAPH_API_GUIDE.md](GRAPH_API_GUIDE.md) for friendship management
- **Messaging API**: See [MESSAGING_API_GUIDE.md](MESSAGING_API_GUIDE.md) for user messages
- **Algorithm API**: See [ALGORITHM_API_GUIDE.md](ALGORITHM_API_GUIDE.md) for user analytics

---

**Last Updated**: December 2024  
**Version**: 1.0  
**Server Port**: 8081  
**Database**: `storage/local_db/users.json`
