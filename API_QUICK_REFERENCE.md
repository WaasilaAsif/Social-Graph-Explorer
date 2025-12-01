# API Quick Reference

Quick reference for all API endpoints in Social Graph Explorer.

**Base URL:** `http://localhost:8080`

---

## Health Check

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | `/health` | Server health check |

---

## User Management

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| POST | `/api/users/register` | `{username, password}` | Register new user |
| POST | `/api/users/login` | `{username, password}` | User login |
| GET | `/api/users/search?prefix=X` | - | Search users by prefix |
| GET | `/api/users/:id` | - | Get user by ID |
| DELETE | `/api/users/:id` | - | Delete user |
| POST | `/api/users/:id/posts` | `{content}` | Create post |
| GET | `/api/users/:id/posts` | - | Get user posts |
| DELETE | `/api/users/:id/posts/:index` | - | Delete post |

---

## Graph Operations

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| GET | `/graph/friends/:id` | - | Get user's friends |
| POST | `/graph/addFriend` | `{u, v}` | Add friendship |
| POST | `/graph/removeFriend` | `{u, v}` | Remove friendship |
| GET | `/graph/stats` | - | Get graph statistics |
| GET | `/graph/connected/:u/:v` | - | Check if users connected |
| GET | `/graph/components` | - | Get connected components count |

---

## Messaging System

| Method | Endpoint | Body | Description |
|--------|----------|------|-------------|
| POST | `/msg/send` | `{senderId, receiverId, text}` | Send message |
| GET | `/msg/search/:word` | - | Search by exact word |
| GET | `/msg/prefix/:prefix` | - | Search by word prefix |
| GET | `/msg/topk/:userId/:k` | - | Top K interactions |
| GET | `/msg/suggestions/:userId/:k` | - | Friend suggestions |
| GET | `/msg/mutual/:userId` | - | Mutual interactions |
| GET | `/msg/rank/:topN` | - | Popularity ranking |
| GET | `/msg/path/:src/:dest` | - | Shortest message path |

---

## Quick Test Examples

### Register User
```bash
curl -X POST http://localhost:8080/api/users/register \
  -H "Content-Type: application/json" \
  -d '{"username":"alice","password":"pass123"}'
```

### Add Friendship
```bash
curl -X POST http://localhost:8080/graph/addFriend \
  -H "Content-Type: application/json" \
  -d '{"u":1,"v":2}'
```

### Send Message
```bash
curl -X POST http://localhost:8080/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1,"receiverId":2,"text":"Hello!"}'
```

### Get Graph Stats
```bash
curl http://localhost:8080/graph/stats
```

### Search Messages
```bash
curl http://localhost:8080/msg/search/hello
```

---

## Response Format

**Success Response:**
```json
{
  "success": true,
  "data": {...}
}
```

**Error Response:**
```json
{
  "success": false,
  "error": "Error message"
}
```

---

## HTTP Status Codes

- `200` - OK (successful GET)
- `201` - Created (successful POST)
- `400` - Bad Request
- `401` - Unauthorized
- `404` - Not Found
- `500` - Internal Server Error

---

For detailed documentation, see **POSTMAN_API_GUIDE.md**
