# Complete API Testing Guide

Comprehensive testing workflows for all 35+ endpoints in the SocialGraphExplorer API.

---

## 📋 Quick Links

- **Graph API**: [GRAPH_API_GUIDE.md](GRAPH_API_GUIDE.md) - 9 endpoints
- **User API**: [USER_API_GUIDE.md](USER_API_GUIDE.md) - 8 endpoints  
- **Messaging API**: [MESSAGING_API_GUIDE.md](MESSAGING_API_GUIDE.md) - 8 endpoints
- **Algorithm API**: [ALGORITHM_API_GUIDE.md](ALGORITHM_API_GUIDE.md) - 10 endpoints

---

## 🚀 Quick Start

### 1. Start the Server

```bash
cd backend
.\server.exe
```

**Expected Output**:
```
Loaded 320 users from database.
Loading data from JSON files...
✓ Loaded 61 friendships from storage/local_db/friendships.json
✓ Loaded 51 messages from storage/local_db/messages.json
Data loaded successfully!

========================================
 Social Network Graph API Server
Listening on: http://localhost:8081
Graph routes registered
Messaging routes registered
User routes registered
Algorithm routes registered
Server ready!
========================================
```

### 2. Verify Server is Running

```bash
curl http://localhost:8081/
```

You should see a JSON response with all 35+ endpoints listed.

---

## 🧪 Complete Test Suite

### Test 1: User Management Flow

**Scenario**: Register → Login → Create Post → Get Profile → Delete

```bash
# 1. Register new user
curl -X POST http://localhost:8081/api/users/register \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user_2024","password":"securepass123"}'
# Expected: {"success":true,"userId":321}

# 2. Login
curl -X POST http://localhost:8081/api/users/login \
  -H "Content-Type: application/json" \
  -d '{"username":"test_user_2024","password":"securepass123"}'
# Expected: {"success":true,"userId":321}

# 3. Create post
curl -X POST http://localhost:8081/api/users/321/posts \
  -H "Content-Type: application/json" \
  -d '{"content":"My first post on this platform!"}'
# Expected: {"success":true,"postId":0}

# 4. Get user profile
curl http://localhost:8081/api/users/321
# Expected: Full user object with posts array

# 5. Delete user
curl -X DELETE http://localhost:8081/api/users/321
# Expected: {"success":true,"message":"User deleted successfully"}
```

---

### Test 2: Friendship Management Flow

**Scenario**: Add Friend → Get Friends → Check Connection → Remove Friend

```bash
# 1. Get initial friends of user 1
curl http://localhost:8081/graph/friends/1
# Expected: {"success":true,"friends":[2,3,5,7,10],"count":5}

# 2. Add new friendship
curl -X POST http://localhost:8081/graph/addFriend \
  -H "Content-Type: application/json" \
  -d '{"u":1,"v":100}'
# Expected: {"success":true,"message":"Friendship added successfully"}

# 3. Verify friendship was added
curl http://localhost:8081/graph/friends/1
# Expected: {"success":true,"friends":[2,3,5,7,10,100],"count":6}

# 4. Check if users are connected
curl http://localhost:8081/graph/connected/1/100
# Expected: {"success":true,"connected":true}

# 5. Remove friendship
curl -X POST http://localhost:8081/graph/removeFriend \
  -H "Content-Type: application/json" \
  -d '{"u":1,"v":100}'
# Expected: {"success":true,"message":"Friendship removed successfully"}
```

---

### Test 3: Messaging Workflow

**Scenario**: Send Message → Search → Find Path → Get Top Conversations

```bash
# 1. Send a message
curl -X POST http://localhost:8081/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1,"receiverId":20,"text":"Hey! Want to collaborate on the project?"}'
# Expected: {"status":"success","messageId":52}

# 2. Search for keyword "project"
curl http://localhost:8081/msg/search/project
# Expected: {"results":[1,5,12,23,34,42,52]}

# 3. Search by prefix "coll"
curl http://localhost:8081/msg/prefix/coll
# Expected: {"results":[52]} (finds "collaborate")

# 4. Get top 5 conversations for user 1
curl http://localhost:8081/msg/topk/1/5
# Expected: {"messages":[{"userId":2,"weight":8},{"userId":3,"weight":6}...]}

# 5. Find messaging path between users
curl http://localhost:8081/msg/path/1/20
# Expected: {"path":[1,20]} (direct) or {"path":[1,5,15,20]} (indirect)
```

---

### Test 4: Network Traversal & Analysis

**Scenario**: BFS → DFS → Shortest Path → Statistics

```bash
# 1. BFS traversal from user 1
curl http://localhost:8081/graph/bfs/1
# Expected: {"success":true,"traversal":[1,2,3,5,7,10...],"levels":{...}}

# 2. DFS traversal from user 1
curl http://localhost:8081/graph/dfs/1
# Expected: {"success":true,"traversal":[1,2,7,20,35...],"count":12}

# 3. Find shortest path
curl http://localhost:8081/graph/shortest-path/1/50
# Expected: {"success":true,"path":[1,5,25,50],"distance":3}

# 4. Get graph statistics
curl http://localhost:8081/graph/stats
# Expected: {"nodes":320,"edges":61,"density":0.0012,"components":15...}

# 5. Count components
curl http://localhost:8081/graph/components
# Expected: {"success":true,"components":15}
```

---

### Test 5: Advanced Algorithms

**Scenario**: Mutual Friends → Friend Suggestions → Popularity → Network Metrics

```bash
# 1. Find mutual friends
curl "http://localhost:8081/api/algo/mutual-friends?user1=1&user2=5"
# Expected: {"user1":1,"user2":5,"mutualFriends":[2,3,7],"count":3}

# 2. Get friend suggestions
curl "http://localhost:8081/api/algo/friend-suggestions?userId=1&limit=10"
# Expected: {"suggestions":[{"userId":42,"mutualFriends":8}...],"count":10}

# 3. Get top 10 popular users
curl "http://localhost:8081/api/algo/top-popular?n=10"
# Expected: {"topUsers":[{"userId":5,"score":45}...],"count":10}

# 4. Get user rank
curl "http://localhost:8081/api/algo/user-rank?userId=1"
# Expected: {"userId":1,"rank":5,"score":24,"percentile":98.5}

# 5. Find users within 2 hops
curl "http://localhost:8081/api/algo/users-within-distance?userId=1&distance=2"
# Expected: {"userId":1,"users":[2,3,5,7,10,15,18,22...],"count":15}

# 6. Get complete network statistics
curl http://localhost:8081/api/algo/graph-stats
# Expected: Detailed metrics including clustering coefficient, diameter, etc.
```

---

### Test 6: Search & Discovery

**Scenario**: User Search → Two-Hop Friends → Message Suggestions

```bash
# 1. Search users by prefix
curl "http://localhost:8081/api/users/search?prefix=ali"
# Expected: {"results":[{"id":1,"username":"alice_smith"}...],"count":3}

# 2. Find friends of friends
curl "http://localhost:8081/api/algo/two-hop-friends?userId=1"
# Expected: {"userId":1,"twoHopFriends":[15,18,22,25,30...],"count":12}

# 3. Get messaging-based friend suggestions
curl "http://localhost:8081/msg/suggestions/1/5"
# Expected: {"friends":[42,55,67,89,101]}

# 4. Find mutual messaging interactions
curl http://localhost:8081/msg/mutual/1
# Expected: {"mutual":[{"u1":2,"u2":3},{"u1":2,"u2":5}...]}
```

---

## 🔬 Automated Test Scripts

### PowerShell Full Test Suite

Save as `test-all-apis.ps1`:

```powershell
# SocialGraphExplorer API Test Suite
Write-Host "🚀 Starting API Test Suite..." -ForegroundColor Cyan

$baseUrl = "http://localhost:8081"
$testResults = @{
    Passed = 0
    Failed = 0
    Errors = @()
}

function Test-Endpoint {
    param(
        [string]$Name,
        [string]$Method,
        [string]$Endpoint,
        [object]$Body = $null
    )
    
    Write-Host "`n📝 Testing: $Name" -ForegroundColor Yellow
    
    try {
        $params = @{
            Uri = "$baseUrl$Endpoint"
            Method = $Method
            ErrorAction = 'Stop'
        }
        
        if ($Body) {
            $params.Body = ($Body | ConvertTo-Json)
            $params.ContentType = 'application/json'
        }
        
        $response = Invoke-RestMethod @params
        Write-Host "✅ PASS: $Name" -ForegroundColor Green
        $testResults.Passed++
        return $response
    }
    catch {
        Write-Host "❌ FAIL: $Name" -ForegroundColor Red
        Write-Host "   Error: $($_.Exception.Message)" -ForegroundColor Red
        $testResults.Failed++
        $testResults.Errors += $Name
        return $null
    }
}

# Test 1: Health Check
Test-Endpoint -Name "Server Health" -Method Get -Endpoint "/health"

# Test 2: Graph Operations
Test-Endpoint -Name "Get Friends" -Method Get -Endpoint "/graph/friends/1"
Test-Endpoint -Name "Graph Statistics" -Method Get -Endpoint "/graph/stats"
Test-Endpoint -Name "BFS Traversal" -Method Get -Endpoint "/graph/bfs/1"
Test-Endpoint -Name "Shortest Path" -Method Get -Endpoint "/graph/shortest-path/1/10"

# Test 3: User Operations
Test-Endpoint -Name "User Search" -Method Get -Endpoint "/api/users/search?prefix=ali"
Test-Endpoint -Name "Get User" -Method Get -Endpoint "/api/users/1"
Test-Endpoint -Name "Get User Posts" -Method Get -Endpoint "/api/users/1/posts"

# Test 4: Messaging Operations
Test-Endpoint -Name "Message Search" -Method Get -Endpoint "/msg/search/project"
Test-Endpoint -Name "Prefix Search" -Method Get -Endpoint "/msg/prefix/pro"
Test-Endpoint -Name "Top K Conversations" -Method Get -Endpoint "/msg/topk/1/5"
Test-Endpoint -Name "Messaging Path" -Method Get -Endpoint "/msg/path/1/10"

# Test 5: Algorithm Operations
Test-Endpoint -Name "Mutual Friends" -Method Get -Endpoint "/api/algo/mutual-friends?user1=1&user2=5"
Test-Endpoint -Name "Friend Suggestions" -Method Get -Endpoint "/api/algo/friend-suggestions?userId=1&limit=5"
Test-Endpoint -Name "Top Popular Users" -Method Get -Endpoint "/api/algo/top-popular?n=10"
Test-Endpoint -Name "User Rank" -Method Get -Endpoint "/api/algo/user-rank?userId=1"
Test-Endpoint -Name "Network Stats" -Method Get -Endpoint "/api/algo/graph-stats"

# Test 6: Write Operations (Comment out if you don't want to modify data)
# $registerBody = @{username="test_$(Get-Date -Format 'yyyyMMddHHmmss')"; password="test123"}
# Test-Endpoint -Name "User Registration" -Method Post -Endpoint "/api/users/register" -Body $registerBody

# Print Summary
Write-Host "`n" + "="*50 -ForegroundColor Cyan
Write-Host "📊 TEST SUMMARY" -ForegroundColor Cyan
Write-Host "="*50 -ForegroundColor Cyan
Write-Host "✅ Passed: $($testResults.Passed)" -ForegroundColor Green
Write-Host "❌ Failed: $($testResults.Failed)" -ForegroundColor Red
Write-Host "📈 Success Rate: $([math]::Round(($testResults.Passed / ($testResults.Passed + $testResults.Failed)) * 100, 2))%" -ForegroundColor Cyan

if ($testResults.Failed -gt 0) {
    Write-Host "`n Failed Tests:" -ForegroundColor Red
    $testResults.Errors | ForEach-Object {
        Write-Host "   - $_" -ForegroundColor Red
    }
}

Write-Host "`n🎉 Test suite complete!`n" -ForegroundColor Cyan
```

**Run it:**
```powershell
.\test-all-apis.ps1
```

---

### Bash Test Suite

Save as `test-all-apis.sh`:

```bash
#!/bin/bash

BASE_URL="http://localhost:8081"
PASS=0
FAIL=0

test_endpoint() {
    local name=$1
    local method=$2
    local endpoint=$3
    local data=$4
    
    echo ""
    echo "📝 Testing: $name"
    
    if [ "$method" = "POST" ]; then
        response=$(curl -s -w "\n%{http_code}" -X POST "$BASE_URL$endpoint" \
            -H "Content-Type: application/json" \
            -d "$data")
    else
        response=$(curl -s -w "\n%{http_code}" "$BASE_URL$endpoint")
    fi
    
    http_code=$(echo "$response" | tail -n1)
    
    if [ "$http_code" = "200" ]; then
        echo "✅ PASS: $name"
        ((PASS++))
    else
        echo "❌ FAIL: $name (HTTP $http_code)"
        ((FAIL++))
    fi
}

echo "🚀 Starting API Test Suite..."

# Graph Tests
test_endpoint "Get Friends" "GET" "/graph/friends/1"
test_endpoint "Graph Stats" "GET" "/graph/stats"
test_endpoint "BFS Traversal" "GET" "/graph/bfs/1"

# User Tests
test_endpoint "User Search" "GET" "/api/users/search?prefix=ali"
test_endpoint "Get User" "GET" "/api/users/1"

# Messaging Tests
test_endpoint "Message Search" "GET" "/msg/search/project"
test_endpoint "Top K" "GET" "/msg/topk/1/5"

# Algorithm Tests
test_endpoint "Mutual Friends" "GET" "/api/algo/mutual-friends?user1=1&user2=5"
test_endpoint "Friend Suggestions" "GET" "/api/algo/friend-suggestions?userId=1&limit=5"
test_endpoint "Top Popular" "GET" "/api/algo/top-popular?n=10"

# Summary
TOTAL=$((PASS + FAIL))
SUCCESS_RATE=$(echo "scale=2; $PASS * 100 / $TOTAL" | bc)

echo ""
echo "=================================================="
echo "📊 TEST SUMMARY"
echo "=================================================="
echo "✅ Passed: $PASS"
echo "❌ Failed: $FAIL"
echo "📈 Success Rate: ${SUCCESS_RATE}%"
echo ""
echo "🎉 Test suite complete!"
```

**Run it:**
```bash
chmod +x test-all-apis.sh
./test-all-apis.sh
```

---

## 📊 Performance Benchmarking

### Test Response Times

```bash
# Graph operations
time curl http://localhost:8081/graph/stats
time curl http://localhost:8081/graph/bfs/1
time curl http://localhost:8081/graph/shortest-path/1/50

# Messaging operations
time curl http://localhost:8081/msg/search/project
time curl http://localhost:8081/msg/topk/1/10

# Algorithm operations
time curl "http://localhost:8081/api/algo/graph-stats"
time curl "http://localhost:8081/api/algo/friend-suggestions?userId=1&limit=10"
```

### Expected Performance Benchmarks

| Category | Endpoint | Expected Time | Complexity |
|----------|----------|---------------|------------|
| Graph | Get Friends | < 5ms | O(1) |
| Graph | Add/Remove Friend | < 10ms | O(1) + file I/O |
| Graph | BFS/DFS | < 40ms | O(V + E) |
| Graph | Shortest Path | < 40ms | O(V + E) |
| Graph | Statistics | < 50ms | O(V + E) |
| User | Register/Login | < 15ms | O(1) + file I/O |
| User | Search | < 10ms | O(prefix + results) |
| User | Get/Update | < 5ms | O(1) |
| Messaging | Send | < 10ms | O(words) + file I/O |
| Messaging | Search Word | < 5ms | O(word length) |
| Messaging | Search Prefix | < 10ms | O(prefix + results) |
| Messaging | Top-K | < 20ms | O(neighbors + k log k) |
| Messaging | Path | < 40ms | O(V + E) |
| Algorithm | Mutual Friends | < 20ms | O(n + m) |
| Algorithm | Friend Suggestions | < 30ms | O(d² × V) |
| Algorithm | Top Popular | < 30ms | O(V log V) |
| Algorithm | Graph Stats | < 50ms | O(V²) for diameter |

---

## 🐛 Troubleshooting

### Server Not Responding

```bash
# Check if server is running
curl http://localhost:8081/health

# If not, start server
cd backend
.\server.exe
```

### CORS Errors (Frontend)

All endpoints support CORS with `Access-Control-Allow-Origin: *`

### Empty Results

- **Graph operations**: Check if users exist and have friends
- **Messaging**: Check if messages are loaded (look for "Loaded X messages" on startup)
- **Search**: Try prefix search instead of exact match

### Persistence Issues

Check file permissions on:
- `storage/local_db/users.json`
- `storage/local_db/friendships.json`
- `storage/local_db/messages.json`

---

## 🎯 Test Scenarios by Use Case

### Social Network Simulation

```bash
# 1. Create 3 users
curl -X POST http://localhost:8081/api/users/register -H "Content-Type: application/json" -d '{"username":"alice","password":"pass123"}'
curl -X POST http://localhost:8081/api/users/register -H "Content-Type: application/json" -d '{"username":"bob","password":"pass123"}'
curl -X POST http://localhost:8081/api/users/register -H "Content-Type: application/json" -d '{"username":"charlie","password":"pass123"}'

# 2. Create friendships
curl -X POST http://localhost:8081/graph/addFriend -H "Content-Type: application/json" -d '{"u":321,"v":322}'
curl -X POST http://localhost:8081/graph/addFriend -H "Content-Type: application/json" -d '{"u":322,"v":323}'

# 3. Send messages
curl -X POST http://localhost:8081/msg/send -H "Content-Type: application/json" -d '{"senderId":321,"receiverId":322,"text":"Hi Bob!"}'
curl -X POST http://localhost:8081/msg/send -H "Content-Type: application/json" -d '{"senderId":322,"receiverId":323,"text":"Hey Charlie!"}'

# 4. Verify social graph
curl http://localhost:8081/graph/shortest-path/321/323
curl "http://localhost:8081/api/algo/mutual-friends?user1=321&user2=323"
```

---

## 📚 Additional Resources

- **Individual API Guides**: See detailed documentation for each category
- **Algorithm Explanations**: [ALGORITHM_API_GUIDE.md](ALGORITHM_API_GUIDE.md)
- **Database Schema**: Check each guide for JSON structure
- **Integration Examples**: React components in algorithm guide

---

**Last Updated**: December 2024  
**API Version**: 1.0  
**Total Endpoints**: 35+  
**Server**: http://localhost:8081
