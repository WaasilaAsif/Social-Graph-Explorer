# Social Graph Explorer - Frontend

A React + TypeScript + Vite frontend for the Social Graph Explorer project with integrated API tools for graph and messaging operations.

## Features

- **Modern UI**: Built with React 19.2.0 and TypeScript 5.9.3
- **Obsidian Dark Theme**: Custom CSS styling with consistent design
- **Tab-Based Navigation**: Multi-tab interface for exploring different views
- **API Integration**: Direct integration with backend C++ APIs
  - **Graph Explorer**: Test and visualize graph operations (friends, BFS, DFS, shortest path)
  - **Messaging Hub**: Send messages and explore messaging analytics
- **Real-time Data**: Live communication with backend server on port 8081

## Quick Start

### Prerequisites
- Node.js v18.0.0 or higher
- npm v9.0.0 or higher
- Backend server running on `http://localhost:8081`

### Installation

```bash
cd frontend
npm install
```

### Development

```bash
npm run dev
```

Frontend will be available at `http://localhost:5173`

### Build for Production

```bash
npm run build
```

## New Features

### Graph Explorer
Located in sidebar under "API Tools" → "Graph Explorer"

**Features:**
- Get friends list for any user
- Add/remove friendships
- Run BFS (Breadth-First Search) traversal
- Run DFS (Depth-First Search) traversal
- Find shortest path between users

**Usage:**
1. Click "Graph Explorer" in the sidebar
2. Select operation from tabs (Friends Management, Graph Traversal, Shortest Path)
3. Enter user ID(s)
4. Click action button
5. View results in JSON format

### Messaging Hub
Located in sidebar under "API Tools" → "Messaging Hub"

**Features:**
- Send new messages
- Search messages by exact word
- Search messages by prefix
- Get top K conversation partners
- Get friend suggestions based on messages
- View mutual interactions
- See popularity rankings
- Find shortest messaging path

**Usage:**
1. Click "Messaging Hub" in the sidebar
2. Select section from tabs (Send Message, Search Messages, Analytics, Message Path)
3. Enter required parameters
4. Click action button
5. View results in JSON format

## Project Structure

```
frontend/
├── src/
│   ├── components/       # Reusable UI components
│   │   ├── Sidebar.jsx   # Main navigation (updated with API tools)
│   │   ├── TabBar.jsx
│   │   └── ...
│   ├── pages/           # Page components
│   │   ├── MainUI.jsx   # Main layout (updated with routing)
│   │   ├── GraphExplorer.jsx  # NEW: Graph API interface
│   │   └── MessagingHub.jsx   # NEW: Messaging API interface
│   ├── services/        # API service layer
│   │   └── api.ts       # NEW: Backend API calls
│   ├── styles/          # CSS modules
│   │   ├── GraphExplorer.css    # NEW
│   │   ├── MessagingHub.css     # NEW
│   │   └── ...
│   └── data/           # Mock data for development
└── ...
```

## Backend API Integration

The frontend connects to the C++ backend server running on port 8081.

### API Endpoints Used

**Graph APIs (6 endpoints):**
- `GET /graph/friends/:id`
- `POST /graph/add-friend`
- `DELETE /graph/remove-friend/:user1/:user2`
- `GET /graph/bfs/:start`
- `GET /graph/dfs/:start`
- `GET /graph/shortest-path/:src/:dest`

**Messaging APIs (8 endpoints):**
- `POST /msg/send`
- `GET /msg/search/:word`
- `GET /msg/prefix/:prefix`
- `GET /msg/topk/:userId/:k`
- `GET /msg/suggestions/:userId/:k`
- `GET /msg/mutual/:userId`
- `GET /msg/rank/:top`
- `GET /msg/path/:src/:dest`

### Proxy Configuration

Vite dev server is configured to proxy API requests to the backend:
- Frontend: `http://localhost:5173`
- Backend: `http://localhost:8081`
- Proxy: `/api/*` → Backend

## Technologies

**Core:**
- React 19.2.0
- TypeScript 5.9.3
- Vite 7.2.5 (Rolldown)

**UI:**
- Lucide React (icons)
- Custom CSS (Obsidian theme)

**State Management:**
- Zustand 5.0.8

**Routing:**
- React Router 7.9.6

## Development Tips

### Testing API Integration

1. **Ensure Backend is Running:**
   ```bash
   cd ../backend
   ./server.exe
   ```

2. **Start Frontend:**
   ```bash
   npm run dev
   ```

3. **Test Graph Operations:**
   - Navigate to "Graph Explorer"
   - Try getting friends for user ID 1
   - Expected: List of friend connections

4. **Test Messaging:**
   - Navigate to "Messaging Hub"
   - Try searching for word "project"
   - Expected: List of message IDs

### Troubleshooting

**CORS Errors:**
- Ensure backend server has CORS headers enabled
- Check vite proxy configuration in `vite.config.ts`

**API Not Found (404):**
- Verify backend server is running on port 8081
- Check API endpoint URLs in `src/services/api.ts`

**Connection Refused:**
- Ensure backend is compiled and running
- Check firewall settings

## React Compiler

The React Compiler is enabled on this template for optimized performance. See [React Compiler Documentation](https://react.dev/learn/react-compiler) for more information.

Note: This will impact Vite dev & build performances.

## Expanding the ESLint configuration

If you are developing a production application, we recommend updating the configuration to enable type-aware lint rules:

```js
export default defineConfig([
  globalIgnores(['dist']),
  {
    files: ['**/*.{ts,tsx}'],
    extends: [
      // Other configs...

      // Remove tseslint.configs.recommended and replace with this
      tseslint.configs.recommendedTypeChecked,
      // Alternatively, use this for stricter rules
      tseslint.configs.strictTypeChecked,
      // Optionally, add this for stylistic rules
      tseslint.configs.stylisticTypeChecked,

      // Other configs...
    ],
    languageOptions: {
      parserOptions: {
        project: ['./tsconfig.node.json', './tsconfig.app.json'],
        tsconfigRootDir: import.meta.dirname,
      },
      // other options...
    },
  },
])
```

You can also install [eslint-plugin-react-x](https://github.com/Rel1cx/eslint-react/tree/main/packages/plugins/eslint-plugin-react-x) and [eslint-plugin-react-dom](https://github.com/Rel1cx/eslint-react/tree/main/packages/plugins/eslint-plugin-react-dom) for React-specific lint rules:

```js
// eslint.config.js
import reactX from 'eslint-plugin-react-x'
import reactDom from 'eslint-plugin-react-dom'

export default defineConfig([
  globalIgnores(['dist']),
  {
    files: ['**/*.{ts,tsx}'],
    extends: [
      // Other configs...
      // Enable lint rules for React
      reactX.configs['recommended-typescript'],
      // Enable lint rules for React DOM
      reactDom.configs.recommended,
    ],
    languageOptions: {
      parserOptions: {
        project: ['./tsconfig.node.json', './tsconfig.app.json'],
        tsconfigRootDir: import.meta.dirname,
      },
      // other options...
    },
  },
])
```
