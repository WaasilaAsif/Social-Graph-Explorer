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
│   │   ├── server.cpp                # Main API server
│   │   ├── routes/                   # API Route Handlers
│   │   │   ├── algoRoutes.cpp        # Algorithm endpoints
│   │   │   ├── graphRoutes.cpp       # Graph operation endpoints
│   │   │   ├── graphRoutes.h
│   │   │   ├── messageRoutes.cpp     # Messaging endpoints
│   │   │   └── userRoutes.cpp        # User management endpoints
│   │   └── server/
│   │       └── server.cpp
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
│   │   ├── JSONWriter.cpp            # Write data to JSON
│   │   └── local_db/                 # Local JSON Database
│   │       ├── friendships.json      # Friendship connections
│   │       └── users.json            # User data
│   │
│   └── tests/                        # Testing Suite
│       ├── integration/              # Integration Tests
│       │   ├── full_integration_aman.cpp
│       │   └── full_integration_Fatima.cpp
│       │
│       └── unit-tests/               # Unit Tests
│           ├── AVLTree_messaging.cpp
│           ├── BFS.cpp
│           ├── ConversationGraph.cpp
│           ├── DFS.cpp
│           ├── friendsuggestion.cpp
│           ├── Graph.cpp
│           ├── graphstats.cpp
│           ├── LinkedList.cpp
│           ├── MsgHeap.cpp
│           ├── MsgStack.cpp
│           ├── MsgTrie.cpp
│           ├── mutualfriends.cpp
│           ├── popularityranker.cpp
│           ├── priorityqueue.cpp
│           ├── Queue.cpp
│           ├── README_MESSAGING_TESTS.md
│           ├── shortestpath.cpp
│           └── Stack.cpp
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
  
- **Messaging System**: Complete messaging infrastructure
  - `ConversationGraph`: Weighted graph for user interactions
  - `MsgTrie`: Fast message search by keywords
  - `MsgHeap`: Priority-based message handling
  - `MsgStack`: Undo/redo functionality
  - `AVLTree`: Self-balancing tree for sorted data

- **Graph Algorithms**: Social network analysis
  - BFS/DFS traversal
  - Shortest path finding
  - Mutual friends detection
  - Friend suggestions
  - Popularity ranking

- **API Server**: Crow-based HTTP REST API
  - User management endpoints
  - Graph operation endpoints
  - Messaging endpoints
  - Algorithm execution endpoints

### Frontend (React + TypeScript)
- **Obsidian Dark Theme**: Custom CSS with CSS variables
- **Three-Pane Layout**: Sidebar, Main View, Info Pane
- **Graph Visualization**: Interactive social graph display
- **User Profiles**: Detailed user information display
- **Post Feed**: Social media post viewing
- **Settings**: Application configuration

## Technology Stack

**Backend:**
- C++17
- Crow (HTTP framework)
- nlohmann/json (JSON parsing)
- Custom DSA implementations

**Frontend:**
- React 19.2.0
- TypeScript 5.9.3
- Vite 7.2.5 (Rolldown)
- lucide-react (icons)
- React Router 7.9.6

**Testing:**
- Unit tests for all custom data structures
- Integration tests for system components
- g++ with C++17 standard

## File Statistics
- **Total Files**: ~150 files
- **Backend C++ Files**: ~90 files
- **Frontend Files**: ~35 files
- **Test Files**: ~20 files
- **Documentation**: 3 files
