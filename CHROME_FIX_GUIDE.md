# Chrome Login Issue - Troubleshooting Guide

## Problem
Login page shows in Edge but not in Chrome. Links are not working.

## Root Cause
Chrome has cached an old version of the app or has corrupted localStorage data.

---

## ✅ Solutions (Try in Order)

### Solution 1: Clear localStorage via DevTools
1. Open Chrome and navigate to `http://localhost:5174/`
2. Press **F12** to open DevTools
3. Go to the **Console** tab
4. Paste and run:
```javascript
localStorage.clear();
location.reload();
```

### Solution 2: Use the Debug Panel
1. Look for the **"Debug"** button in the bottom-right corner
2. Click **"Clear Storage & Reload"**
3. The page will refresh with clean state

### Solution 3: Clear Chrome Cache
1. Press **Ctrl+Shift+Delete**
2. Select:
   - ✅ Cached images and files
   - ✅ Cookies and other site data
3. Time range: **Last hour**
4. Click **Clear data**
5. Navigate to `http://localhost:5174/`

### Solution 4: Incognito Mode
1. Press **Ctrl+Shift+N** to open Incognito
2. Navigate to `http://localhost:5174/`
3. This bypasses all cache and storage

---

## 🔍 Verification Steps

1. **Check Console for Errors**
   - Press F12 → Console tab
   - Look for any red error messages
   - You should see: `Current user state: null` (if not logged in)

2. **Check Network Tab**
   - Press F12 → Network tab
   - Try to login
   - Watch for requests to `http://localhost:8081/api/users/login`
   - Check if CORS errors appear

3. **Verify localStorage**
   - Press F12 → Application tab
   - Left sidebar: Storage → Local Storage → `http://localhost:5174`
   - Should show `user` key after successful login

---

## 🎯 Current Setup

- **Frontend URL**: `http://localhost:5174/` (changed from 5173)
- **Backend URL**: `http://localhost:8081/`
- **Login credentials**: Any username/password (backend must be running)

---

## 🐛 Common Issues

### Issue: "Server connection failed"
**Solution**: Start the backend server
```powershell
cd D:\SocialGraphExplorer\backend
./server.exe
```

### Issue: Login button does nothing
**Solution**: 
1. Open DevTools Console
2. Check for JavaScript errors
3. Verify you're on the correct port (5174, not 5173)

### Issue: Links not working after login
**Solution**: 
1. Check if you see the logout button in the sidebar
2. Try clicking "Home" in the sidebar
3. Check console for errors like "onClick is not defined"

---

## 📝 Debug Features Added

1. **Console Logging**
   - Login/logout events are logged
   - User state is logged on every render
   - Check console with F12

2. **Debug Panel**
   - Fixed button in bottom-right corner
   - Clear Storage & Reload
   - Show Storage contents

3. **Logout Button**
   - Located in the sidebar
   - Under username display
   - Red button with logout icon

---

## 🔧 For Developers

### Check if port changed:
```powershell
netstat -ano | findstr :5173
netstat -ano | findstr :5174
```

### Force restart frontend:
```powershell
cd D:\SocialGraphExplorer\frontend
# Kill any existing Vite process, then:
npm run dev
```

### Verify backend is running:
```powershell
curl http://localhost:8081/api/users/login
# Should return: 405 Method Not Allowed (expects POST)
```

---

## 📞 Still Having Issues?

1. **Check browser version**: Chrome should be up to date
2. **Try Firefox**: To verify it's Chrome-specific
3. **Check for extensions**: Disable ad blockers, privacy extensions
4. **Look at Terminal**: Check for Vite errors in the terminal running `npm run dev`
