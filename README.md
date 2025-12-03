# SocialGraphExplorer

**SocialGraphExplorer** is a modular backend framework for exploring and interacting with a social graph, designed as a **mini Instagram-like social network**. The system emphasizes **Data Structures and Algorithms (DSA)** while providing a fully functional prototype for managing users, friendships, posts, and analytics.

This project is both a **learning-focused DSA implementation** and a **practical social network backend prototype**.

---

## Table of Contents

1. [Problem Statement](#problem-statement)  
2. [Objectives](#objectives)  
3. [Quick Start](#quick-start)
4. [System Requirements](#system-requirements)  
5. [Design Considerations](#design-considerations)  
6. [Key Features & Abstract Implementation](#key-features--abstract-implementation)  
7. [Data Structures & Algorithm Mapping](#data-structures--algorithm-mapping)  
8. [Module Interaction & Flow](#module-interaction--flow)  
9. [Project Structure](#project-structure)  
10. [Team Responsibilities](#team-responsibilities)  
11. [Future Work / Extensions](#future-work--extensions)  
12. [Testing & Validation](#testing--validation)
13. [Basic UI & Design](#ui-baseline)

---

## Problem Statement

Modern social networks are complex systems with users, posts, friendships, and interactions. Navigating and analyzing such networks efficiently requires robust **graph representations and supporting data structures**.  

**Challenges addressed by SocialGraphExplorer:**
- Efficient representation of a **dynamic social graph** with users and friendships.
- Fast search for users and friend suggestions.
- Efficient storage and retrieval of posts.
- Analysis of relationships: mutual friends, shortest paths, recommendation ranking.
- Implementing all functionality using **custom DSA implementations** (no STL or built-ins).

---

## Objectives

1. **Educational Objective**: Demonstrate mastery of advanced **DSA concepts** in a practical project.  
2. **Functional Objective**: Provide a working prototype backend for social graph exploration.  
3. **Performance Objective**: Implement efficient algorithms for traversal, search, and ranking.  
4. **Modular Objective**: Ensure each component is modular, testable, and reusable.

---

## Quick Start

### Recent Updates (January 2024)

✅ **Full Database Integration Complete**
- All messaging APIs now read/write from local JSON database
- Server loads 20 users, 62 friendships, and 50+ messages at startup
- Automatic persistence on message send
- All data structures (MessageStore, MsgTrie, ConversationGraph) initialized from JSON
- **8 Messaging APIs** fully operational with search, analytics, and path-finding
- See [backend/MESSAGING_API_GUIDE.md](backend/MESSAGING_API_GUIDE.md) for complete API documentation

### Prerequisites
- C++17 or higher compiler (GCC 9.0+, Clang 10.0+, MSVC 2019+)
- Node.js v18.0.0 or higher
- npm v9.0.0 or higher

### Backend Setup & Compilation

#### Initial Setup
```bash
cd backend
```

#### Setup Dependencies (First Time Only)

1. **Create libs folder structure:**
```powershell
New-Item -ItemType Directory -Path "libs/crow", "libs/asio", "libs/project_headers" -Force
```

2. **Download ASIO library:**
```powershell
Invoke-WebRequest -Uri "https://github.com/chriskohlhoff/asio/archive/refs/tags/asio-1-30-2.zip" -OutFile "asio.zip"
Expand-Archive -Path "asio.zip" -DestinationPath "." -Force
Copy-Item -Path "asio-asio-1-30-2/asio/include/*" -Destination "libs/asio/" -Recurse -Force
Remove-Item "asio.zip", "asio-asio-1-30-2" -Recurse -Force
```

3. **Copy Crow framework headers:**
```powershell
# Assuming you have Crow headers in an include/ directory
Copy-Item -Path "include/crow_all.h" -Destination "libs/crow/" -Force
Copy-Item -Path "include/nlohmann" -Destination "libs/crow/" -Recurse -Force
```

4. **Copy project algorithm headers:**
```powershell
Copy-Item -Path "algorithms/*.h" -Destination "libs/project_headers/" -Force
```

#### Compile the Server
Whenever you make changes to any C++ files, recompile using:

```bash
g++ api/server.cpp api/routes/graphRoutes.cpp api/routes/MsgRoutes.cpp api/routes/MsgAPI.cpp dsa/user/UserManager.cpp dsa/user/user.cpp dsa/utils/idGenerator.cpp messaging/MessageStore.cpp dsa/messaging_ds/MsgTrie.cpp dsa/messaging_ds/ConversationGraph.cpp algorithms/MsgTopKMessage.cpp algorithms/MsgFriendSuggestion.cpp algorithms/MsgMutualInteractions.cpp algorithms/MsgPopularityRanker.cpp algorithms/MsgShortestPatch.cpp storage/JSONLoader.cpp storage/JSONWriter.cpp -I. -Ilibs -Ilibs/asio -std=c++17 -DASIO_STANDALONE -lws2_32 -lwsock32 -o server.exe
```

**Note**: This includes all messaging system files, database loaders/writers, and algorithm implementations.

#### Run the Server
After compilation, start the server:

```bash
# Run in current terminal
.\server.exe

# OR run in new window to see logs
Start-Process powershell -ArgumentList "-NoExit", "-Command", "cd $pwd; .\server.exe"
```

The API server will be available at `http://localhost:8081`

**Expected Startup Output:**
```
Loading data from JSON files...
✓ Loaded 20 users from storage/local_db/users.json
✓ Loaded 62 friendships from storage/local_db/friendships.json
✓ Loaded 50 messages from storage/local_db/messages.json
Data loaded successfully!

========================================
 Social Network Graph API Server
Listening on: http://localhost:8081
Graph routes registered
Messaging routes registered
User routes registered
Server ready!
========================================
```

#### Verify Server is Running

```bash
# Test health endpoint
curl http://localhost:8081/

# Test messaging search (should return message IDs)
curl http://localhost:8081/msg/search/project

# Test graph endpoint
curl http://localhost:8081/graph/friends/1
```

#### Quick Commands
```powershell
# Navigate to backend
cd backend

# Compile
g++ api/server.cpp api/routes/graphRoutes.cpp api/routes/MsgRoutes.cpp api/routes/MsgAPI.cpp dsa/user/UserManager.cpp dsa/user/user.cpp dsa/utils/idGenerator.cpp messaging/MessageStore.cpp dsa/messaging_ds/MsgTrie.cpp dsa/messaging_ds/ConversationGraph.cpp algorithms/MsgTopKMessage.cpp algorithms/MsgFriendSuggestion.cpp algorithms/MsgMutualInteractions.cpp algorithms/MsgPopularityRanker.cpp algorithms/MsgShortestPatch.cpp storage/JSONLoader.cpp storage/JSONWriter.cpp -I. -Ilibs -Ilibs/asio -std=c++17 -DASIO_STANDALONE -lws2_32 -lwsock32 -o server.exe

# Run
.\server.exe
```

### Troubleshooting Backend Setup

#### Compilation Errors

**Missing ASIO headers:**
```
fatal error: asio.hpp: No such file or directory
```
Solution: Re-run the ASIO download and setup commands from "Setup Dependencies" section.

**Multiple definition errors:**
```
multiple definition of `saveMessagesToJSON'
```
Solution: Ensure you're not including `.cpp` files in headers. Check that `#include "../../storage/JSONWriter.h"` (not `.cpp`) in all files.

**Linker errors (Windows):**
```
undefined reference to `WSAStartup'
```
Solution: Ensure `-lws2_32 -lwsock32` flags are included in the compile command.

#### Runtime Errors

**Port already in use:**
```
Failed to bind to port 8081
```
Solution: Stop any existing server instances or change the port in `api/server.cpp`.

**JSON file not found:**
```
Cannot open file: storage/local_db/users.json
```
Solution: Ensure you're running `server.exe` from the `backend/` directory, not the repository root.

**Missing database files:**
If `storage/local_db/` doesn't exist or is empty:
```powershell
New-Item -ItemType Directory -Path "storage/local_db" -Force
```
The initial JSON files should be committed in the repository. Check git status.

### Frontend Setup
```bash
cd frontend
npm install
npm run dev
```

Frontend will be available at `http://localhost:5173`

For detailed dependency information, see [DEPENDENCIES.md](DEPENDENCIES.md)

---

## System Requirements

**Hardware Requirements:**
- 8 GB RAM minimum
- 50 GB free storage for dataset and posts
- CPU supporting multi-threading (optional for future scaling)

**Software Requirements:**

**Backend:**
- C++ compiler supporting C++17 or higher (GCC 9.0+, Clang 10.0+, MSVC 2019+)
- CMake 3.15+ (optional, for build automation)
- No external libraries required for core functionality

**Frontend:**
- Node.js v18.0.0 or higher
- npm v9.0.0 or higher
- Modern web browser (Chrome 90+, Firefox 88+, Safari 14+)

**Key Dependencies:**
- React 19.2.0 with TypeScript 5.9.3
- Vite 7.2.5 (Rolldown) for fast builds
- Lucide React for icons
- React Router 7.9.6 for navigation
- Zustand 5.0.8 for state management
- Custom CSS (no CSS frameworks)

For complete dependency list, see [DEPENDENCIES.md](DEPENDENCIES.md)

---

## Design Considerations

1. **Modular Design:** Each DSA concept has its own module (Graph, Containers, Algorithms, Users, Utilities).  
2. **Custom Implementations:** All structures (linked lists, stacks, queues, graphs, hash maps) are implemented manually.  
3. **Data Persistence:** JSON files store users and friendships; loader/writer modules abstract file I/O.  
4. **Scalability:** Graph traversal and ranking algorithms are optimized for **time and space complexity**.  
5. **Extensibility:** New algorithms, post types, and analytics features can be integrated easily.

---

## Key Features & Abstract Implementation

### 1. User Management
- **Description:** Create, update, delete users; store profiles and posts.  
- **Implementation:**
  - `User.h`: Stores ID, name, bio, posts, friends list.
  - `UserManager.cpp`: In-memory user storage + Trie for username search.
- **DSA Concepts:** Trees, Trie, recursive search.

### 2. Social Graph
- **Description:** Manage user friendships as a graph.  
- **Implementation:**
  - `Graph.h/.cpp`: Adjacency list + matrix for friendships.
  - `Node.h`, `Edge.h`: Store user and edge metadata.
- **Algorithms:**
  - BFS / DFS for traversal and connected component detection.
  - Dijkstra / Bellman-Ford for shortest paths.
- **DSA Concepts:** Graph representation, traversal, shortest path.

### 3. Friend Analysis
- **Description:** Compute mutual friends and suggest new connections.  
- **Implementation:**
  - `MutualFriends.cpp`: Hash-set based mutual friends calculation.
  - `FriendSuggestion.cpp`: BFS + priority queue ranking for suggestions.
- **DSA Concepts:** Graph traversal, hash sets, priority queues.

### 4. Posts & Feeds
- **Description:** Manage user posts and feed generation.  
- **Implementation:**
  - `DynamicArray.h/.cpp` and `LinkedList.h/.cpp` store posts.
  - Queues manage feed ordering; priority queues rank trending posts.
- **DSA Concepts:** Linked lists, dynamic arrays, queues, heaps.

### 5. Utilities
- **Description:** Provide helper structures and error handling.  
- **Implementation:**
  - `Pair.h`: Generic pair for returning two values.
  - `Vector2.h`: Coordinates for graph layout visualization.
  - `Errors.h`: Custom exception classes.
- **DSA Concepts:** Utility structures for graphs and algorithms.

### 6. Messaging System
- **Description:** Complete messaging infrastructure with search, analytics, scheduling, and undo.
- **Implementation:**
  - `MessagingSystem`: Main coordinator integrating MsgTrie, MsgStack, MsgHeap.
  - `MessageQueue`: FIFO message queue using DynamicArray.
  - `MessageAnalytics`: User interaction tracking with ConversationGraph.
  - `ScheduledMessages`: Priority-based scheduling with MsgHeap.
  - `TopKConversations`: Extract top-K users by interaction count.
  - `UndoStack`: Undo functionality wrapper around MsgStack.
- **DSA Concepts:** Tries for search, heaps for priority, stacks for undo, graphs for analytics.

### 7. Data Persistence
- **Description:** Save/load users and friendships to/from JSON.  
- **Implementation:** `JSONLoader.cpp` and `JSONWriter.cpp`.

---

## Data Structures & Algorithm Mapping

| Module                  | Files                                           | DSA Concepts                                        |
|------------------------|------------------------------------------------|---------------------------------------------------|
| Graph                  | Graph.h/.cpp, Node.h, Edge.h                   | Graphs, adjacency list/matrix, node/edge metadata |
| Traversal              | BFS.h/.cpp, DFS.h/.cpp                         | BFS, DFS, connected components, path finding      |
| Shortest Paths         | ShortestPath.cpp                               | Dijkstra, Bellman-Ford                            |
| User Management        | User.h, UserManager.cpp                        | Trees, Trie, recursive search, CRUD               |
| Containers             | LinkedList, Stack, Queue, HashMap, DynamicArray, PriorityQueue, Trie | Linked lists, stacks, queues, heaps, hash tables |
| Messaging DS           | MsgHeap, MsgTrie, MsgStack, ConversationGraph, AVLTree | Priority heaps, tries, weighted graphs, balanced trees |
| Messaging System       | MessagingSystem, MessageQueue, MessageAnalytics, ScheduledMessages, TopKConversations, UndoStack | System integration, FIFO queues, analytics, scheduling |
| Msg Algorithms         | MsgFriendSuggestion, MsgMutualInteraction, MsgShortestPath, MsgTopKMessages | Friends-of-friends, mutual connections, BFS, top-K extraction |
| Graph Algorithms       | MutualFriends.cpp, FriendSuggestion.cpp        | Graph-based analytics, hash sets, priority queues |
| Utilities              | Pair.h, Vector2.h, Errors.h, IDGenerator       | Custom structures, graph layout, error handling   |

---

## Module Interaction & Flow

```text
[ UserManager ] <----> [ Graph ] <----> [ BFS/DFS/ShortestPath ]
       |                          |
       v                          v
 [ Containers: LinkedList/Stack/Queue/DynamicArray/HashMap/PriorityQueue/Trie ]
       |                          |
       v                          v
 [ Messaging DS: MsgHeap/MsgTrie/MsgStack/ConversationGraph/AVLTree ]
       |                          |
       v                          v
 [ MessagingSystem ] <----> [ MessageQueue/Analytics/Scheduling/TopK ]
       |                          |
       v                          v
 [ MutualFriends / FriendSuggestion / Msg Algorithms ] <- consume graph + containers
       |
       v
 [ main.cpp ] <----> [ JSONLoader / JSONWriter ] <- persistent storage
```
---
>Integration occurs in main.cpp which coordinates all modules.

Containers serve as shared structures for storing nodes, posts, feeds, and rankings.

Messaging system provides complete infrastructure for user interactions and analytics.

Algorithms consume graph and container data for social network analysis and recommendations.
---

## **Project Structure**
```
SocialGraphExplorer/
├── backend/
│   ├── libs/                   # External dependencies (ASIO, Crow, headers)
│   │   ├── asio/               # ASIO 1.30.2 standalone headers
│   │   ├── crow/               # Crow framework (crow_all.h, nlohmann/json)
│   │   └── project_headers/    # Project algorithm headers
│   ├── dsa/
│   │   ├── graph/              # Graph, Node, Edge
│   │   ├── containers/         # LinkedList, Stack, Queue, HashMap, DynamicArray, Pair, PriorityQueue, Trie
│   │   ├── messaging_ds/       # MsgHeap, MsgTrie, MsgStack, ConversationGraph, AVLTree
│   │   ├── user/               # User, UserManager
│   │   └── utils/              # Vector2, Errors, IDGenerator, Pair
│   ├── algorithms/             # BFS, DFS, ShortestPath, MutualFriends, FriendSuggestion
│   │   └── Msg*/               # Message-based algorithms (MsgFriendSuggestion, MsgShortestPath, etc.)
│   ├── messaging/              # Complete messaging system
│   │   ├── Message.h           # Message data structure
│   │   ├── MessageStore        # Message storage and retrieval
│   │   ├── MessagingSystem     # Main coordinator
│   │   ├── MessageQueue        # FIFO queue
│   │   ├── MessageAnalytics    # Interaction analytics
│   │   ├── ScheduledMessages   # Priority scheduling
│   │   ├── TopKConversations   # Top-K extraction
│   │   └── UndoStack           # Undo functionality
│   ├── analytics/              # GraphStats, PopularityRanker
│   ├── storage/                # JSONLoader, JSONWriter
│   │   └── local_db/           # JSON database
│   │       ├── users.json      # 20 users with posts
│   │       ├── friendships.json # 62 friendship connections
│   │       └── messages.json   # 50+ messages with full text
│   ├── api/                    # REST API routes and server (Crow framework)
│   │   ├── server.cpp          # Main server (port 8081)
│   │   └── routes/
│   │       ├── graphRoutes.cpp # 6 graph endpoints
│   │       ├── MsgRoutes.cpp   # 8 messaging endpoints
│   │       ├── MsgAPI.cpp      # Messaging API handlers
│   │       └── userRoutes.cpp  # User management endpoints
│   ├── tests/                  # Comprehensive test suite
│   │   ├── unit-tests/         # 28+ unit test files
│   │   │   ├── README_MESSAGING_TESTS.md
│   │   │   ├── README_MESSAGING_SYSTEM_TESTS.md
│   │   │   └── README_MSG_ALGORITHMS_TESTS.md
│   │   ├── integration/        # Integration tests
│   │   ├── run_all_messaging_tests.ps1
│   │   └── run_all_msg_algorithm_tests.ps1
│   ├── MESSAGING_API_GUIDE.md  # Complete messaging API documentation
│   ├── main.cpp
│   └── server.exe              # Compiled server binary
├── frontend/
│   ├── src/
│   │   ├── components/         # React components (Sidebar, GraphView, etc.)
│   │   ├── pages/              # Page components (MainUI)
│   │   ├── layouts/            # Layout components (AppLayout)
│   │   ├── data/               # Dummy data for development
│   │   └── styles/             # 12 custom CSS files (Obsidian theme)
│   ├── public/
│   ├── package.json
│   └── vite.config.ts
├── structure.md                # Complete file structure documentation
├── DEPENDENCIES.md             # Detailed dependency information
└── README.md                   # This file
```

## **Team Responsibilities**

| Team Member | Files                                                         | Focus                                                   |
| ----------- | ------------------------------------------------------------- | ------------------------------------------------------- |
| 1           | Graph, Node, Edge, BFS, DFS, ShortestPath                     | Graph structures, traversal, shortest paths             |
| 2           | User, UserManager, Trie                                       | User management, search, hierarchy                      |
| 3           | LinkedList, Stack, Queue, HashMap, DynamicArray               | Containers for posts, feeds, undo/redo                  |
| 4           | MutualFriends, FriendSuggestion, utils/*.h, Sorting/Searching | Graph analytics, friend suggestions, utility structures |


## Future Work / Extensions

While SocialGraphExplorer currently provides a robust backend framework and demonstrates a wide variety of DSA concepts, several **extensions and enhancements** can be implemented in future versions:

1. **Advanced Post Features**
   - Support for **images, videos, and multimedia posts**.  
   - Comments, likes, and shares for posts.  
   - Ranking of posts using **priority queues** or **timestamp-based sorting**.  

2. **Graph Visualization**
   - Interactive **frontend visualization** of the social network using **React + D3.js**.  
   - Dynamic layout with **Vector2 coordinates** to display user nodes and friendships.  

3. **Community Detection & Clustering**
   - Identify **communities** within the social graph using algorithms like **Louvain** or **modularity maximization**.  
   - Suggest groups or communities to users for enhanced engagement.  

4. **Recommendation Systems**
   - Advanced friend suggestion using **machine learning** or **graph embedding techniques** (Node2Vec, GraphSAGE).  
   - Personalized post recommendations based on user interactions and mutual friends.  

5. **Scalability & Performance**
   - Transition from **JSON storage to SQL or NoSQL databases** for large-scale social graphs.  
   - Optimize traversal and ranking algorithms for **high-volume datasets**.  

6. **Security & Access Control**
   - Implement **authentication and authorization** for users.  
   - Secure sensitive data with encryption and safe storage practices.  

7. **Analytics & Reporting**
   - User engagement metrics: top influencers, activity trends.  
   - Graph analytics: average shortest path, clustering coefficients, centrality measures.  

---

## API Documentation

### Available API Endpoints

The backend server exposes **32+ REST API endpoints** across three categories:

#### 1. Graph APIs (6 endpoints)
- `GET /graph/friends/:id` - Get all friends of a user
- `POST /graph/add-friend` - Create friendship between two users
- `DELETE /graph/remove-friend/:user1/:user2` - Remove friendship
- `GET /graph/bfs/:start` - Perform BFS traversal from a user
- `GET /graph/dfs/:start` - Perform DFS traversal from a user
- `GET /graph/shortest-path/:src/:dest` - Find shortest path between users

#### 2. Messaging APIs (8 endpoints)
- `POST /msg/send` - Send a new message (auto-saves to DB)
- `GET /msg/search/:word` - Search messages by exact word
- `GET /msg/prefix/:prefix` - Search messages by word prefix
- `GET /msg/topk/:userId/:k` - Get top K conversation partners
- `GET /msg/suggestions/:userId/:k` - Get friend suggestions based on messages
- `GET /msg/mutual/:userId` - Find mutual interactions
- `GET /msg/rank/:top` - Get top N most active users
- `GET /msg/path/:src/:dest` - Find shortest messaging path between users

#### 3. User Management APIs (8+ endpoints)
- User registration, login, profile management
- Post creation and retrieval
- User search and discovery

### Complete Messaging API Guide

For detailed documentation with examples, expected outputs, and testing instructions, see:

📖 **[backend/MESSAGING_API_GUIDE.md](backend/MESSAGING_API_GUIDE.md)**

The guide includes:
- Real cURL and PowerShell examples
- Expected JSON responses
- Sample data from the database
- Performance metrics
- Troubleshooting tips
- Testing workflows

### Quick API Test

```bash
# Get API menu
curl http://localhost:8081/

# Search for word "project" in messages
curl http://localhost:8081/msg/search/project
# Expected: {"results":[1,5,12,23,34,42]}

# Get top 5 conversations for user 1
curl http://localhost:8081/msg/topk/1/5
# Expected: {"messages":[{"userId":2,"weight":8},{"userId":3,"weight":6}...]}

# Send a new message
curl -X POST http://localhost:8081/msg/send \
  -H "Content-Type: application/json" \
  -d '{"senderId":1,"receiverId":3,"text":"Hello!"}'
# Expected: {"status":"success","messageId":51}
```

---

## Testing & Validation

A rigorous testing framework ensures **functionality, correctness, and performance** of SocialGraphExplorer.

###    Test Status: 79+ Tests Passing

| Test Suite | Tests | Status | Description |
|------------|-------|--------|-------------|
| **Messaging Integration** | 9/9 |    PASS | MessageStore, Trie, Graph, Algorithms |
| **Msg Algorithms** | 21/21 |    PASS | MutualInteraction, FriendSuggestion, ShortestPath, TopK |
| **Messaging DS** | 28/28 |    PASS | MsgHeap, MsgTrie, ConversationGraph, AVLTree, Stack |
| **Messaging System** | 21/21 |    PASS | MessagingSystem, Queue, Analytics, Scheduling |
| **TOTAL** | **79+** | **   ALL PASS** | Complete test coverage |

### Running Tests

```powershell
# From D:\SocialGraphExplorer
.\backend\tests\MsgAPI.exe
```

**Detailed Documentation:** See [TESTING_GUIDE.md](TESTING_GUIDE.md)

### Original Testing Strategy

1. **Unit Testing**
   - Test each module independently.  
   - Examples:
     - **Graph module:** verify adding/removing nodes and edges, BFS/DFS correctness.  
     - **UserManager:** test CRUD operations and Trie-based search.  
     - **Containers:** check push/pop, enqueue/dequeue, insert/remove correctness.  

2. **Integration Testing**
   - Verify **interactions between modules**.  
   - Examples:
     - Ensure `UserManager` correctly interacts with `Graph` for friendship operations.  
     - Friend suggestion algorithm correctly uses BFS traversal and containers.  
     - JSONLoader/Writer properly saves and loads all modules’ data.  

3. **Performance Testing**
   - Measure time and memory complexity for:
     - Graph traversals on large networks.  
     - Mutual friends and friend suggestion algorithms.  
     - Feed generation and post ranking.  

4. **Validation**
   - Check correctness of DSA implementations:
     - BFS/DFS visit orders match expected results.  
     - Shortest paths are optimal (Dijkstra/Bellman-Ford).  
     - Containers (LinkedList, Stack, Queue, HashMap, DynamicArray) maintain correct states.  

5. **Automated Testing Framework**
   - Implement a **unit and integration test suite** that can be run via **C++ testing frameworks** (e.g., Google Test).  
   - Ensure **continuous validation** after every code change.  

## **UI Baseline**

**Main page**
---
![Main Page](image.png)
---

**Posts Page**
---
![Posts Page](image-1.png)
---
 **Basic Graph Interface (Under work)**
---
![graph interface](image-2.png)
---
 