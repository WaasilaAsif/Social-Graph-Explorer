# Social Graph Explorer - Complete File Structure

```
SocialGraphExplorer/
│
├── .gitignore
├── .vscode/                          # VS Code configuration
├── DEPENDENCIES.md                   # Project dependencies documentation
├── Overview.md                       # Project overview
├── README.md                         # Main documentation
├── structure.md                      # This file - complete file structure
├── image.png                         # Project images
├── image-1.png
├── image-2.png
│
├── backend/                          # C++ Backend
│   ├── main.cpp                      # Main entry point
│   ├── server.exe                    # Compiled server binary
│   │
│   ├── libs/                         # External Dependencies (Generated)
│   │   ├── asio/                     # ASIO 1.30.2 standalone async I/O
│   │   │   ├── asio.hpp
│   │   │   ├── detail/
│   │   │   ├── execution/
│   │   │   ├── experimental/
│   │   │   ├── generic/
│   │   │   ├── impl/
│   │   │   ├── ip/
│   │   │   ├── local/
│   │   │   ├── posix/
│   │   │   ├── ssl/
│   │   │   ├── ts/
│   │   │   └── windows/
│   │   ├── crow/                     # Crow HTTP framework
│   │   │   ├── crow_all.h            # Main Crow header
│   │   │   └── nlohmann/
│   │   │       └── json.hpp          # JSON parsing library
│   │   └── project_headers/          # Copied algorithm headers
│   │       ├── BFS.h
│   │       ├── DFS.h
│   │       ├── FriendSuggestion.h
│   │       └── ShortestPath.h
│   │
│   ├── algorithms/                   # Graph & Messaging Algorithms
│   │   ├── BFS.h                     # Breadth-First Search
│   │   ├── DFS.h                     # Depth-First Search
│   │   ├── FriendSuggestion.cpp
│   │   ├── FriendSuggestion.h
│   │   ├── MutualFriends.cpp         # Find mutual friends algorithm
│   │   ├── MutualFriends.h
│   │   ├── ShortestPath.cpp          # Shortest path algorithm
│   │   ├── ShortestPath.h
│   │   ├── MsgFriendSuggestion.cpp   # Message-based friend suggestions
│   │   ├── MsgFriendSuggestion.h
│   │   ├── MsgMutualInteraction.h
│   │   ├── MsgMutualInteractions.cpp
│   │   ├── MsgPopularityRanker.cpp
│   │   ├── MsgPopularityRanker.h
│   │   ├── MsgShortestPatch.cpp
│   │   ├── MsgShortestPath.h
│   │   ├── MsgTopKMessage.cpp
│   │   └── MsgTopKMessages.h
│   │
│   ├── analytics/                    # Graph Analytics & Statistics
│   │   ├── GraphLayout.h
│   │   ├── GraphStats.cpp            # Graph statistics calculations
│   │   ├── GraphStats.h
│   │   ├── PopularityRanker.cpp      # User popularity ranking
│   │   └── PopularityRanker.h
│   │
│   ├── api/                          # REST API Server
│   │   ├── server.cpp                # Main API server (port 8081)
│   │   └── routes/                   # API Route Handlers
│   │       ├── algoRoutes.cpp        # Algorithm endpoints (legacy)
│   │       ├── graphRoutes.cpp       # Graph operation endpoints (6 APIs)
│   │       ├── graphRoutes.h
│   │       ├── MsgRoutes.cpp         # Messaging route registration (8 APIs)
│   │       ├── MsgRoutes.h
│   │       ├── MsgAPI.cpp            # Messaging API handlers
│   │       ├── MsgAPI.h
│   │       ├── messageRoutes.cpp     # Legacy message routes
│   │       └── userRoutes.cpp        # User management endpoints
│   │
│   ├── dsa/                          # Custom Data Structures & Algorithms
│   │   ├── containers/               # Generic Container Implementations
│   │   │   ├── DynamicArray.h        # Custom dynamic array (replaces std::vector)
│   │   │   ├── HashMap.cpp
│   │   │   ├── HashMap.h             # Custom hash map (replaces std::unordered_map)
│   │   │   ├── LinkedList.h          # Custom linked list
│   │   │   ├── Pair.h                # Pair container
│   │   │   ├── PriorityQueue.h       # Priority queue implementation
│   │   │   ├── Queue.h               # Queue implementation
│   │   │   ├── Stack.h               # Stack implementation
│   │   │   └── trie.h                # Trie data structure
│   │   │
│   │   ├── graph/                    # Graph Data Structures
│   │   │   ├── Edge.h                # Graph edge representation
│   │   │   ├── Graph.h               # Main graph structure
│   │   │   └── Node.h                # Graph node representation
│   │   │
│   │   ├── messaging_ds/             # Messaging-Specific Data Structures
│   │   │   ├── AVLTree.cpp           # Self-balancing AVL tree
│   │   │   ├── AVLTree.h
│   │   │   ├── ConversationGraph.cpp # Weighted conversation graph
│   │   │   ├── ConversationGraph.h
│   │   │   ├── MsgHeap.cpp           # Priority heap for messages
│   │   │   ├── MsgHeap.h
│   │   │   ├── MsgStack.cpp          # Message stack (LIFO)
│   │   │   ├── MsgStack.h
│   │   │   ├── MsgTrie.cpp           # Trie for message search
│   │   │   └── MsgTrie.h
│   │   │
│   │   ├── user/                     # User Management
│   │   │   ├── test.cpp
│   │   │   ├── user.cpp
│   │   │   ├── User.h                # User data structure
│   │   │   ├── UserManager.cpp       # User management logic
│   │   │   └── UserManager.h
│   │   │
│   │   └── utils/                    # Utility Functions
│   │       ├── Errors.h              # Error handling
│   │       ├── idGenerator.cpp       # ID generation utility
│   │       ├── idGenerator.h
│   │       ├── Pair.h                # Utility pair structure
│   │       └── Vector2.h             # 2D vector utility
│   │
│   ├── include/                      # External Libraries
│   │   ├── crow_all.h                # Crow HTTP framework
│   │   └── nlohmann/
│   │       └── json.hpp              # JSON library
│   │
│   ├── messaging/                    # Messaging System
│   │   ├── Message.h                 # Message data structure
│   │   ├── MessageStore.cpp          # Message storage and retrieval
│   │   ├── MessageStore.h
│   │   ├── MessageAnalytics.cpp      # Message analytics & statistics
│   │   ├── MessageAnalytics.h
│   │   ├── MessageQueue.cpp          # Message queue implementation
│   │   ├── MessageQueue.h
│   │   ├── MessagingSystem.cpp       # Main messaging system
│   │   ├── MessagingSystem.h
│   │   ├── ScheduledMessages.cpp     # Scheduled message handling
│   │   ├── ScheduledMessages.h
│   │   ├── TopKConversations.cpp     # Top-K conversation finder
│   │   ├── TopKConversations.h
│   │   ├── UndoStack.cpp             # Undo functionality
│   │   └── UndoStack.h
│   │
│   ├── storage/                      # Data Persistence
│   │   ├── JSONLoader.cpp            # Load data from JSON
│   │   ├── JSONLoader.h
│   │   ├── JSONWriter.cpp            # Write data to JSON
│   │   ├── JSONWriter.h
│   │   └── local_db/                 # Local JSON Database
│   │       ├── friendships.json      # 62 friendship connections
│   │       ├── messages.json         # 50+ messages with full text
│   │       └── users.json            # 20 users with posts
│   │
│   ├── tests/                        # Testing Suite
│   │   ├── integration/              # Integration Tests
│   │   │   ├── full_integration_aman.cpp
│   │   │   └── full_integration_Fatima.cpp
│   │   │
│   │   └── unit-tests/               # Unit Tests
│   │       ├── AVLTree_messaging.cpp
│   │       ├── BFS.cpp
│   │       ├── ConversationGraph.cpp
│   │       ├── DFS.cpp
│   │       ├── friendsuggestion.cpp
│   │       ├── Graph.cpp
│   │       ├── graphstats.cpp
│   │       ├── LinkedList.cpp
│   │       ├── MsgHeap.cpp
│   │       ├── MsgStack.cpp
│   │       ├── MsgTrie.cpp
│   │       ├── mutualfriends.cpp
│   │       ├── popularityranker.cpp
│   │       ├── priorityqueue.cpp
│   │       ├── Queue.cpp
│   │       ├── README_MESSAGING_TESTS.md
│   │       ├── shortestpath.cpp
│   │       └── Stack.cpp
│   │
│   └── MESSAGING_API_GUIDE.md        # Complete messaging API documentation
│       # - 8 messaging endpoints documented
│       # - Real examples with cURL/PowerShell
│       # - Expected outputs and testing guide
│       # - Performance metrics and troubleshooting
│
└── frontend/                         # React TypeScript Frontend
    ├── .gitignore
    ├── eslint.config.js              # ESLint configuration
    ├── index.html                    # Main HTML entry
    ├── package.json                  # NPM dependencies
    ├── package-lock.json
    ├── README.md
    ├── tsconfig.json                 # TypeScript configuration
    ├── tsconfig.app.json
    ├── tsconfig.node.json
    ├── vite.config.ts                # Vite build configuration
    │
    ├── public/
    │   └── vite.svg
    │
    └── src/
        ├── main.tsx                  # React entry point
        ├── App.tsx                   # Main App component
        ├── vite-env.d.ts             # Vite type definitions
        │
        ├── components/               # React Components
        │   ├── GraphView.jsx         # Graph visualization
        │   ├── Pane.jsx              # Generic pane component
        │   ├── PostView.jsx          # Post display
        │   ├── RightInfoPane.jsx     # Right sidebar info
        │   ├── SettingsModal.jsx     # Settings modal
        │   ├── Sidebar.jsx           # Left sidebar navigation
        │   ├── Splitter.jsx          # Pane splitter
        │   ├── TabBar.jsx            # Tab navigation
        │   └── UserProfileView.jsx   # User profile display
        │
        ├── data/                     # Mock Data
        │   ├── dummyGraph.js         # Sample graph data
        │   ├── dummyPosts.js         # Sample posts
        │   └── dummyUsers.js         # Sample users
        │
        ├── layouts/                  # Layout Components
        │   └── AppLayout.jsx         # Main app layout
        │
        ├── pages/                    # Page Components
        │   └── MainUI.jsx            # Main UI page
        │
        └── styles/                   # CSS Styles (Obsidian Theme)
            ├── index.css             # Global styles & CSS variables
            ├── AppLayout.css
            ├── GraphView.css
            ├── MainUI.css
            ├── Pane.css
            ├── PostView.css
            ├── RightInfoPane.css
            ├── SettingsModal.css
            ├── Sidebar.css
            ├── Splitter.css
            ├── TabBar.css
            └── UserProfileView.css
```

## Key Architecture Components

### Backend (C++)
- **Custom DSA**: All STL containers replaced with custom implementations
  - `DynamicArray` replaces `std::vector`
  - `HashMap` replaces `std::unordered_map`
  - Custom `Stack`, `Queue`, `LinkedList`, `PriorityQueue`, `Trie`
  
- **Messaging System**: Complete messaging infrastructure with database integration
  - `MessageStore`: Storage and retrieval of messages
  - `ConversationGraph`: Weighted graph for user interactions
  - `MsgTrie`: Fast message search by keywords (word and prefix search)
  - `MsgHeap`: Priority-based message handling
  - `MsgStack`: Undo/redo functionality
  - `AVLTree`: Self-balancing tree for sorted data
  - **Database Integration**: All messages loaded from and saved to `messages.json`
  - **Auto-persistence**: New messages automatically saved to database

- **Graph Algorithms**: Social network analysis
  - BFS/DFS traversal
  - Shortest path finding (Dijkstra/Bellman-Ford)
  - Mutual friends detection
  - Friend suggestions (graph-based and message-based)
  - Popularity ranking

- **API Server**: Crow-based HTTP REST API (Port 8081)
  - **6 Graph endpoints**: Friends list, add/remove friends, BFS, DFS, shortest path
  - **8 Messaging endpoints**: Send, word search, prefix search, top-K, suggestions, mutual, rank, path
  - **8+ User endpoints**: Registration, login, profile, posts
  - Total: 32+ REST endpoints
  - JSON request/response format
  - CORS enabled for frontend integration

- **Data Persistence**: JSON-based local database
  - `users.json`: 20 users with profiles and posts
  - `friendships.json`: 62 friendship connections
  - `messages.json`: 50+ messages with full text
  - Auto-load on server startup
  - Auto-save on data modifications

### Frontend (React + TypeScript)
- **Obsidian Dark Theme**: Custom CSS with CSS variables
- **Three-Pane Layout**: Sidebar, Main View, Info Pane
- **Graph Visualization**: Interactive social graph display
- **User Profiles**: Detailed user information display
- **Post Feed**: Social media post viewing
- **Settings**: Application configuration

## Technology Stack

**Backend:**
- C++17 (GCC 13.2.0 on Windows/MSYS2)
- Crow 1.0+ (HTTP framework)
- ASIO 1.30.2 (Standalone async I/O)
- nlohmann/json (JSON parsing)
- Custom DSA implementations (no STL containers)
- Windows Sockets (ws2_32, wsock32)

**Frontend:**
- React 19.2.0
- TypeScript 5.9.3
- Vite 7.2.5 (Rolldown)
- lucide-react (icons)
- React Router 7.9.6

**Development Tools:**
- g++ (MinGW-w64)
- PowerShell (automation scripts)
- Git (version control)

**Testing:**
- Unit tests for all custom data structures (79+ tests passing)
- Integration tests for system components
- PowerShell test runners
- g++ with C++17 standard

## File Statistics
- **Total Files**: ~180+ files
- **Backend C++ Files**: ~100+ files
  - Source files (.cpp): ~50 files
  - Header files (.h): ~50 files
  - Library files: 1000+ headers in libs/asio/
- **Frontend Files**: ~35 files
- **Test Files**: ~25 files
- **Documentation**: 5 files (README, structure, DEPENDENCIES, MESSAGING_API_GUIDE, Overview)
- **Database Files**: 3 JSON files (users, friendships, messages)
- **Configuration**: 10+ config files (package.json, tsconfig, eslint, vite, .gitignore)
