# Quick Start Guide - Social Graph Explorer

## 🚀 Current Setup (CORS Fixed!)

### Servers Running:
1. **Backend Server** (C++)
   - Port: `8081`
   - Direct access (no CORS headers)

2. **CORS Proxy** (Node.js)
   - Port: `8082`
   - Adds CORS headers and forwards to backend
   - **Frontend uses this**

3. **Frontend** (React + Vite)
   - Port: `5174`
   - Connects to CORS proxy on port 8082

---

## 📝 How to Start Everything

### Terminal 1: Backend Server
```powershell
cd D:\SocialGraphExplorer\backend
./server.exe
```

### Terminal 2: CORS Proxy
```powershell
cd D:\SocialGraphExplorer\backend
node cors-proxy.js
```

### Terminal 3: Frontend
```powershell
cd D:\SocialGraphExplorer\frontend
npm run dev
```

---

## 🌐 URLs

- **Frontend**: http://localhost:5174/
- **API (via CORS proxy)**: http://localhost:8082/
- **Backend (direct)**: http://localhost:8081/ *(don't use from browser)*

---

## [x]
 Testing Login

1. Open Chrome and go to http://localhost:5174/
2. If you see a cached page, press F12 and run in Console:
   ```javascript
   localStorage.clear();
   location.reload();
   ```
3. You should see the login page
4. **Register a new account**:
   - Username: `testuser`
   - Password: `password123`
   - Click "Register"
5. After successful registration, you'll be logged in automatically
6. You should see the main app with sidebar showing your username

---

## 🐛 Troubleshooting

### Chrome Not Showing Login Page
**Solution**: Clear cache and localStorage
```javascript
// In Chrome DevTools Console (F12):
localStorage.clear();
sessionStorage.clear();
location.reload();
```

### CORS Errors Still Appearing
**Check**:
1. Are all 3 servers running?
2. Is frontend using port 8082? (Check Login.tsx line 28)
3. Is CORS proxy forwarding to port 8081?

### Backend Not Starting
**Check**:
```powershell
Get-Process server -ErrorAction SilentlyContinue
# If running, stop it:
Stop-Process -Name server -Force
# Then restart
```

### Port Already in Use
```powershell
# Check what's using the port:
netstat -ano | findstr :8081
netstat -ano | findstr :8082
netstat -ano | findstr :5174

# Kill process by PID:
taskkill /PID <PID> /F
```

---

## 🔧 Debug Tools

### Debug Panel (Bottom-Right Corner)
- **Clear Storage & Reload**: Clears localStorage and reloads page
- **Show Storage**: Displays current localStorage contents

### Console Logging
- Open DevTools (F12) → Console tab
- You'll see: `Current user state: null` (when not logged in)
- After login: `Login successful: {userId: X, username: "..."}}`

### Logout Button
- In the sidebar (purple box)
- Shows your username
- Red logout button to sign out

---

## 📂 Modified Files

- `frontend/src/pages/Login.tsx` - Changed API URL to port 8082
- `backend/cors-proxy.js` - New CORS proxy server
- `frontend/src/App.tsx` - Added debug logging and validation
- `frontend/src/components/DebugPanel.tsx` - New debug UI
- `frontend/src/components/Sidebar.jsx` - Added logout button

---

## 🎯 Next Steps

After successful login, you can:
1. Click "Home" in sidebar to see the feed
2. Browse users in the Users section
3. Explore Graph Explorer
4. Try Messaging Hub
5. View analytics and algorithms

---

## 💡 Why CORS Proxy?

The C++ backend doesn't properly handle OPTIONS preflight requests. Instead of recompiling (which has dependency issues), we use a lightweight Node.js proxy that:
- Intercepts all requests
- Adds proper CORS headers
- Forwards to backend
- Returns responses with CORS headers

This is a **development workaround**. For production, fix CORS in the C++ server.

---

## 📞 Still Having Issues?

1. Check all 3 servers are running
2. Look at terminal output for errors
3. Check Chrome DevTools Console for errors
4. Verify ports: 5174 (frontend), 8082 (proxy), 8081 (backend)
5. Try incognito mode: Ctrl+Shift+N
