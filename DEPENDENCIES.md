# Dependencies

This document lists all dependencies required to build and run SocialGraphExplorer.

---

## Backend Dependencies

### Build Requirements

**C++ Compiler:**
- **Minimum:** C++17 or higher
- **Recommended:** C++20
- **Supported Compilers:**
  - GCC 9.0+
  - Clang 10.0+
  - MSVC 2019+

**Build System:**
- CMake 3.15+ (if using CMake)
- Make (Unix/Linux)
- Visual Studio 2019+ (Windows)

### Runtime Dependencies

**Standard Library:**
- C++ Standard Library (included with compiler)
- No external libraries required for core functionality

**Optional Dependencies:**
- **JSON Parsing:** nlohmann/json (header-only) - for enhanced JSON support
- **Testing:** Google Test (gtest) - for unit testing framework

---

## Frontend Dependencies

### Node.js & Package Manager

**Required:**
- **Node.js:** v18.0.0 or higher
- **npm:** v9.0.0 or higher (comes with Node.js)

### Production Dependencies

```json
{
  "@heroicons/react": "^2.2.0",
  "@radix-ui/react-icons": "^1.3.2",
  "lucide-react": "^0.554.0",
  "react": "^19.2.0",
  "react-dom": "^19.2.0",
  "react-router-dom": "^7.9.6",
  "zustand": "^5.0.8"
}
```

**Description:**
- **react/react-dom:** Core React framework v19.2.0
- **react-router-dom:** Client-side routing v7.9.6
- **lucide-react:** Icon library with 1000+ icons
- **@heroicons/react:** Hero Icons library
- **@radix-ui/react-icons:** Radix UI icon set
- **zustand:** Lightweight state management

### Development Dependencies

```json
{
  "@eslint/js": "^9.39.1",
  "@types/node": "^24.10.1",
  "@types/react": "^19.2.5",
  "@types/react-dom": "^19.2.3",
  "@vitejs/plugin-react": "^5.1.1",
  "babel-plugin-react-compiler": "^1.0.0",
  "eslint": "^9.39.1",
  "eslint-plugin-react-hooks": "^7.0.1",
  "eslint-plugin-react-refresh": "^0.4.24",
  "globals": "^16.5.0",
  "typescript": "~5.9.3",
  "typescript-eslint": "^8.46.4",
  "vite": "npm:rolldown-vite@7.2.5"
}
```

**Description:**
- **TypeScript:** v5.9.3 for type safety
- **Vite (Rolldown):** v7.2.5 - Fast build tool using Rolldown
- **ESLint:** v9.39.1 - Code linting with React plugins
- **@vitejs/plugin-react:** v5.1.1 - React plugin with Fast Refresh
- **babel-plugin-react-compiler:** v1.0.0 - React Compiler support

---

## Installation Instructions

### Backend Setup

**Linux/macOS:**
```bash
cd backend
g++ -std=c++17 -o socialgraph main.cpp
```

**Windows (Visual Studio):**
```cmd
cd backend
cl /EHsc /std:c++17 main.cpp
```

**With CMake:**
```bash
cd backend
mkdir build && cd build
cmake ..
make
```

### Frontend Setup

```bash
cd frontend
npm install
npm run dev
```

**Production Build:**
```bash
npm run build
npm run preview
```

---

## Development Tools

### Recommended VSCode Extensions

**Backend:**
- C/C++ (Microsoft)
- CMake Tools
- C++ TestMate

**Frontend:**
- ESLint
- TypeScript Vue Plugin (Volar)
- Prettier - Code formatter

---

## System Requirements

### Minimum Requirements

**Backend:**
- 4 GB RAM
- 1 GB free disk space
- Any OS with C++17 compiler support

**Frontend:**
- 4 GB RAM
- 500 MB free disk space
- Node.js v18+

### Recommended Requirements

**Backend:**
- 8 GB RAM
- 2 GB free disk space
- Multi-core CPU for parallel testing

**Frontend:**
- 8 GB RAM
- 1 GB free disk space
- Modern browser (Chrome 90+, Firefox 88+, Safari 14+)

---

## Troubleshooting

### Common Issues

**Backend:**
- **Missing C++17 support:** Update your compiler
- **Linker errors:** Ensure all .cpp files are compiled together
- **Template errors:** Check that template implementations are included

**Frontend:**
- **npm install fails:** Clear cache with `npm cache clean --force`
- **Port 5173 in use:** Stop other Vite processes or change port in vite.config.ts
- **TypeScript errors:** Run `npm run build` to check for type issues

---

## Version Compatibility

| Component | Minimum Version | Recommended Version |
|-----------|----------------|---------------------|
| C++ Standard | C++17 | C++20 |
| Node.js | v18.0.0 | v20.0.0+ |
| npm | v9.0.0 | v10.0.0+ |
| React | v19.2.0 | Latest |
| TypeScript | v5.0.0 | v5.9.3 |
| Vite | v7.2.5 | Latest |

---

## License Information

All dependencies are used under their respective open-source licenses:
- React: MIT License
- TypeScript: Apache License 2.0
- Vite: MIT License
- Lucide Icons: ISC License
- Other dependencies: Check individual package.json or LICENSE files
