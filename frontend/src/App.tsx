import { useState } from 'react';
import { BrowserRouter, Routes, Route, Navigate } from 'react-router-dom';
import AppLayout from './layouts/AppLayout';
import MainUI from './pages/MainUI';
import Login from './pages/Login';
import GraphStats from './pages/GraphStats';
import PopularUsers from './pages/PopularUsers';
import UserProfile from './pages/UserProfile';
import DebugPanel from './components/DebugPanel';

interface UserData {
  userId: number;
  username: string;
}

function App() {
  const [user, setUser] = useState<UserData | null>(() => {
    // Initialize state from localStorage with validation
    try {
      const storedUser = localStorage.getItem('user');
      if (storedUser) {
        const parsed = JSON.parse(storedUser);
        // Validate the stored user object
        if (parsed && typeof parsed.userId === 'number' && typeof parsed.username === 'string') {
          return parsed;
        }
        // Invalid user data, clear it
        localStorage.removeItem('user');
      }
    } catch (error) {
      console.error('Error reading user from localStorage:', error);
      localStorage.removeItem('user');
    }
    return null;
  });

  const handleLogin = (userData: UserData) => {
    console.log('Login successful:', userData);
    setUser(userData);
  };

  const handleLogout = () => {
    console.log('Logging out...');
    localStorage.removeItem('user');
    setUser(null);
  };

  // Debug: Log current user state
  console.log('Current user state:', user);

  if (!user) {
    return (
      <>
        <BrowserRouter>
          <Routes>
            <Route path="/login" element={<Login onLogin={handleLogin} />} />
            <Route path="*" element={<Navigate to="/login" replace />} />
          </Routes>
        </BrowserRouter>
        <DebugPanel />
      </>
    );
  }

  return (
    <>
      <BrowserRouter>
        <AppLayout>
          <Routes>
            <Route path="/" element={<MainUI user={user} onLogout={handleLogout} />} />
            <Route path="/stats" element={<GraphStats />} />
            <Route path="/leaderboard" element={<PopularUsers />} />
            <Route path="/users/:id" element={<UserProfile />} />
            <Route path="*" element={<Navigate to="/" replace />} />
          </Routes>
        </AppLayout>
      </BrowserRouter>
      <DebugPanel />
    </>
  );
}

export default App;
