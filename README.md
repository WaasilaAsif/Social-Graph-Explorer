# SocialGraphExplorer

**SocialGraphExplorer** is a modular backend framework for exploring and interacting with a social graph, designed as a **mini Instagram-like social network**. The system emphasizes **Data Structures and Algorithms (DSA)** while providing a fully functional prototype for managing users, friendships, posts, and analytics.

This project is both a **learning-focused DSA implementation** and a **practical social network backend prototype**.

---

## Table of Contents

1. [Problem Statement](#problem-statement)  
2. [Objectives](#objectives)  
3. [System Requirements](#system-requirements)  
4. [Design Considerations](#design-considerations)  
5. [Key Features & Abstract Implementation](#key-features--abstract-implementation)  
6. [Data Structures & Algorithm Mapping](#data-structures--algorithm-mapping)  
7. [Module Interaction & Flow](#module-interaction--flow)  
8. [Project Structure](#project-structure)  
9. [Team Responsibilities](#team-responsibilities)  
10. [Future Work / Extensions](#future-work--extensions)  
11. [Testing & Validation](#testing--validation)

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

## System Requirements

**Hardware Requirements:**
- 8 GB RAM minimum
- 50 GB free storage for dataset and posts
- CPU supporting multi-threading (optional for future scaling)

**Software Requirements:**
- C++ compiler supporting C++17 or higher
- Python/Node.js (optional for frontend API integration)
- React.js for frontend visualization
- JSON parsing library for data persistence

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

### 6. Data Persistence
- **Description:** Save/load users and friendships to/from JSON.  
- **Implementation:** `JSONLoader.cpp` and `JSONWriter.cpp`.

---

## Data Structures & Algorithm Mapping

| Module | File | DSA Concepts |
|--------|------|--------------|
| Graph | Graph.h/.cpp, Node.h, Edge.h | Graphs, adjacency list/matrix, node/edge metadata |
| Traversal | BFS.h/.cpp, DFS.h/.cpp | BFS, DFS, connected components, path finding |
| Shortest Paths | ShortestPath.cpp | Dijkstra, Bellman-Ford |
| User Management | User.h, UserManager.cpp | Trees, Trie, recursive search, CRUD |
| Containers | LinkedList, Stack, Queue, HashMap, DynamicArray | Linked lists, stacks, queues, heaps, hash tables |
| Algorithms | MutualFriends.cpp, FriendSuggestion.cpp | Graph-based analytics, hash sets, priority queues |
| Utilities | Pair.h, Vector2.h, Errors.h | Custom structures, graph layout, error handling |

---

## Module Interaction & Flow

```text
[ UserManager ] <----> [ Graph ] <----> [ BFS/DFS/ShortestPath ]
       |                          |
       v                          v
 [ Containers: LinkedList/Stack/Queue/DynamicArray/HashMap ]
       |
       v
 [ MutualFriends / FriendSuggestion ] <- consumes graph + container structures
       |
       v
 [ main.cpp ] <----> [ JSONLoader / JSONWriter ] <- persistent storage
---
Integration occurs in main.cpp which coordinates all modules.

Containers serve as shared structures for storing nodes, posts, feeds, and rankings.

Algorithms consume graph and container data for analytics and friend suggestions.
---

#Project Structure
SocialGraphExplorer/
├── backend/
│   ├── dsa/
│   │   ├── graph/
│   │   ├── containers/
│   │   ├── user/
│   │   └── utils/
│   ├── algorithms/
│   ├── storage/
│   └── main.cpp
├── frontend/ (React)
└── tests/ (unit, integration, performance)

## *Team Responsibilities**
| Team Member | Files                                                         | Focus                                                   |
| ----------- | ------------------------------------------------------------- | ------------------------------------------------------- |
| 1           | Graph, Node, Edge, BFS, DFS, ShortestPath                     | Graph structures, traversal, shortest paths             |
| 2           | User, UserManager, Trie                                       | User management, search, hierarchy                      |
| 3           | LinkedList, Stack, Queue, HashMap, DynamicArray               | Containers for posts, feeds, undo/redo                  |
| 4           | MutualFriends, FriendSuggestion, utils/*.h, Sorting/Searching | Graph analytics, friend suggestions, utility structures |

