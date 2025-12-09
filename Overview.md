# SocialGraphExplorer – Team Task & DSA Assignment

This document defines **file/module ownership** for each team member and **what DSA concepts** are implemented in each part of the project. It ensures fair workload distribution and maximizes the use of **custom data structures and algorithms**.

---

## **Project Structure Reference**

```
SocialGraphExplorer/
│
├── backend/
│   ├── dsa/                         # All custom data structures (NO STL, NO built-ins)
│   │   ├── graph/
│   │   │   ├── Graph.h
│   │   │   ├── Graph.cpp
│   │   │   ├── Node.h
│   │   │   └── Edge.h
│   │   ├── containers/
│   │   │   ├── LinkedList.h
│   │   │   ├── LinkedList.cpp
│   │   │   ├── Queue.h
│   │   │   ├── Queue.cpp
│   │   │   ├── Stack.h
│   │   │   ├── Stack.cpp
│   │   │   ├── HashMap.h
│   │   │   ├── HashMap.cpp
│   │   │   └── DynamicArray.h / .cpp
│   │   ├── user/
│   │   │   ├── User.h
│   │   │   └── UserManager.cpp
│   │   └── utils/
│   │       ├── Pair.h
│   │       ├── Vector2.h (for graph layout)
│   │       └── Errors.h
│   │
│   ├── algorithms/
│   │   ├── BFS.h
│   │   ├── BFS.cpp
│   │   ├── DFS.h
│   │   ├── DFS.cpp
│   │   ├── ShortestPath.cpp
│   │   ├── MutualFriends.cpp
│   │   └── FriendSuggestion.cpp
│   │
│   ├── storage/
│   │   ├── JSONLoader.cpp
│   │   ├── JSONWriter.cpp
│   │   └── local_db/
│   │       ├── users.json
│   │       └── friendships.json
│   │
│   ├── api/
│   │   ├── server.cpp (if C++)
│   │   └── routes/
│   │       ├── userRoutes.cpp
│   │       ├── graphRoutes.cpp
│   │       ├── algoRoutes.cpp
│   │       └── messageRoutes.cpp
│   │
│   └── main.cpp
│
├── frontend/ (React)
│   ├── src/
│   │   ├── components/
│   │   ├── pages/
│   │   ├── graph/
│   │   │   ├── GraphVisualizer.jsx
│   │   │   └── GraphStyles.css
│   │   ├── api/
│   │   └── App.jsx
│
├── tests/
│   ├── unit/
│   ├── integration/
│   └── performance/
│
└── README.md
```
---

## **Team Member Assignments**

### ** Team Member 1 – Graph & Traversals**

**Responsibilities:**
- Implement the core **Graph structure**.
- Implement graph **traversal and shortest path algorithms**.

**Files:**
- `Graph.h / Graph.cpp`: Graph class (adjacency list + matrix), add/remove nodes/edges, graph properties.
- `Node.h / Edge.h`: Node (user) and edge structures with metadata.
- `BFS.h / BFS.cpp`: Breadth-First Search, level tracking, path retrieval.
- `DFS.h / DFS.cpp`: Depth-First Search (recursive + iterative), cycle detection, connected components.
- `ShortestPath.cpp`: Dijkstra’s algorithm, Bellman-Ford, optional Floyd-Warshall.

**DSA Concepts:**
- Graph representation (adjacency list & matrix)
- BFS / DFS traversal
- Shortest path algorithms
- Connected components & cycles

---

### **Team Member 2 – Trees & User Hierarchy**

**Responsibilities:**
- Implement **user management** with tree/trie support.
- Handle **user search and hierarchical structures**.

**Files:**
- `User.h`: User profile (ID, name, bio, posts, friends list), CRUD methods.
- `UserManager.cpp`: In-memory user management, load/save JSON, trie for fast username search/autocomplete.

**Optional Enhancements:**
- Prefix-based friend suggestions using Trie.

**DSA Concepts:**
- Binary search tree / Trie
- Recursive search & traversal
- Hierarchical data structures

---

### **Team Member 3 – Containers: Lists, Stacks, Queues, Heaps**

**Responsibilities:**
- Implement **core container data structures** used across the project.

**Files:**
- `LinkedList.h / LinkedList.cpp`: Singly, doubly, circular lists with insert/delete/search/reverse.
- `Stack.h / Stack.cpp`: LIFO stack, undo/redo stack functionality.
- `Queue.h / Queue.cpp`: FIFO queue, circular queue, optional priority queue for ranking.
- `HashMap.h / HashMap.cpp`: Hash table (chaining/open addressing) for fast lookups.
- `DynamicArray.h / DynamicArray.cpp`: Resizable arrays for feeds/posts.

**DSA Concepts:**
- Linked lists (all variants)
- Stack & queue implementations
- Priority queues / heaps
- Hashing & dynamic arrays

---

### **Team Member 4 – Algorithms & Utilities**

**Responsibilities:**
- Implement **supporting algorithms** and utility functions.
- Handle **sorting, searching, and analytics**.

**Files:**
- `MutualFriends.cpp`: Compute mutual friends, hash/set-based optimization.
- `FriendSuggestion.cpp`: Suggest friends based on graph traversal & ranking (2-hop algorithm).
- `ShortestPath.cpp`: BFS-based shortest path with parent tracking.
- `PopularityRanker.cpp`: Rank users by degree centrality using max-heap (PriorityQueue).
- `GraphStats.cpp`: Network analysis metrics (density, diameter, clustering coefficient).
- `utils/Pair.h`: Simple pair class for function returns.
- `utils/Vector2.h`: Graph layout, coordinates, and distance calculations.
- `utils/Errors.h`: Custom error handling (InvalidNode, DuplicateEdge, etc.).
- Sorting & Searching algorithms (add to `algorithms/` as needed): bubble, selection, insertion, merge, quick, heap sort; linear, binary search.
- `api/routes/algoRoutes.cpp`: REST API endpoints exposing all algorithm functionality.

**Algorithm API Endpoints (10 routes):**
1. `/api/algo/mutual-friends?user1=X&user2=Y` - Hash-set intersection for common friends
2. `/api/algo/shortest-path?start=X&end=Y` - BFS shortest path with distance
3. `/api/algo/users-within-distance?userId=X&distance=N` - BFS with hop limiting
4. `/api/algo/user-degree?userId=X` - Adjacency list size (friend count)
5. `/api/algo/graph-stats` - Complete network metrics (traversal-based)
6. `/api/algo/top-popular?n=10` - Max-heap extraction of top N users
7. `/api/algo/user-rank?userId=X` - Popularity ranking & percentile
8. `/api/algo/friend-suggestions?userId=X&limit=10` - 2-hop + mutual friends scoring
9. `/api/algo/two-hop-friends?userId=X` - Friends of friends (BFS 2-level)
10. `/api/algo/unit-tests` - Automated test suite for all algorithms

**Use Cases:**
- **Mutual Friends**: "You and Alice have 12 friends in common" - Social proof feature
- **Shortest Path**: "You are connected to Bob through 3 mutual friends" - Connection degrees
- **Users Within Distance**: "Discover 45 people 2 connections away" - Network expansion
- **Top Popular**: Influencer leaderboards, trending users dashboard
- **Friend Suggestions**: AI-powered "People you may know" recommendations
- **Graph Stats**: Admin analytics, network health monitoring, engagement metrics
- **User Rank**: "You're more connected than 85% of users" - Gamification

**DSA Concepts:**
- Sorting & searching algorithms
- Set/hash-based computations (mutual friends)
- Utility structures & functions
- Graph analytics & ranking algorithms
- BFS traversal variants (shortest path, 2-hop, distance-limited)
- Max-heap for priority ranking (PriorityQueue)
- Percentile calculations & statistical ranking
- Network metrics (density, clustering coefficient, diameter)

---

## **Shared / Integration Responsibilities**

- `storage/JSONLoader.cpp` / `JSONWriter.cpp`: Shared by all for loading/saving users, friendships, posts.
- `main.cpp`: Integrates all modules for testing, demo, and API exposure.

---

## **DSA Coverage Summary**

| Team Member | Files | DSA Concepts Covered | API Routes |
|------------|-------|----------------------|------------|
| 1 | Graph.h/.cpp, Node.h, Edge.h, BFS, DFS, ShortestPath | Graphs, BFS/DFS, shortest paths, connected components | `/graph/*` (9 endpoints) |
| 2 | User.h, UserManager.cpp, Trie (optional) | Trees, Trie, recursive search, hierarchical user management | `/api/users/*` (8 endpoints) |
| 3 | LinkedList, Stack, Queue, HashMap, DynamicArray, PriorityQueue | Linked lists, stacks, queues, heaps, hash maps, dynamic arrays | Used internally by all routes |
| 4 | MutualFriends, FriendSuggestion, PopularityRanker, GraphStats, utils/*.h, algoRoutes | Sorting, searching, hash/set operations, graph analytics, heap-based ranking, network metrics | `/api/algo/*` (10 endpoints) |

**Total API Coverage**: 35+ endpoints across Graph, Messaging, User Management, and Advanced Algorithms

---

### **Usage Notes**
- Each member should **implement and test their module independently**.
- Modules should be **integrated through `main.cpp` and API routes**.
- Encourage **code reusability**, e.g., utilities, iterators, hashing functions.
- Add **unit tests** in `tests/unit/` for all DSA components.

---

**This roadmap ensures fair workload, maximum DSA coverage, and a modular, maintainable project structure.**

