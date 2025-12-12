import { useState } from 'react';
import { ChevronDown, ChevronRight, Network, Home, MessageSquare, Activity, LogOut, BarChart3, Trophy, Navigation, Trash2 } from 'lucide-react';
import { userAPI } from '../services/api';
import '../styles/Sidebar.css';

export default function Sidebar({ onUserClick, onNavigate, user, onLogout }) {
  const [graphsExpanded, setGraphsExpanded] = useState(true);
  const [apiExpanded, setApiExpanded] = useState(true);
  const [analyticsExpanded, setAnalyticsExpanded] = useState(true);
  const [deleteError, setDeleteError] = useState(null);
  const [isDeleting, setIsDeleting] = useState(false);

  const handleDeleteAccount = async () => {
    // Show confirmation dialog
    const confirmed = window.confirm(
      'Are you sure you want to delete your account? This action cannot be undone.'
    );
    
    if (!confirmed) return;
    
    setIsDeleting(true);
    setDeleteError(null);
    
    try {
      // Get user ID from localStorage
      const storedUser = localStorage.getItem('user');
      if (!storedUser) {
        throw new Error('No user found');
      }
      
      const userData = JSON.parse(storedUser);
      const userId = userData.userId;
      
      if (!userId) {
        throw new Error('Invalid user ID');
      }
      
      // Call DELETE API
      await userAPI.deleteUser(userId);
      
      // Clear localStorage and logout
      localStorage.removeItem('user');
      onLogout();
      
    } catch (err) {
      console.error('Failed to delete account:', err);
      setDeleteError('Failed to delete account. Please try again.');
      setTimeout(() => setDeleteError(null), 5000); // Clear error after 5 seconds
    } finally {
      setIsDeleting(false);
    }
  };

  return (
    <div className="sidebar">
      <div className="sidebar-header">
        <h2>Social Graph Explorer</h2>
        {user && (
          <div style={{ marginTop: '8px', padding: '8px', background: 'rgba(99, 102, 241, 0.1)', borderRadius: '6px' }}>
            <div style={{ fontSize: '12px', color: 'var(--text-secondary)', marginBottom: '4px' }}>
              Logged in as:
            </div>
            <div style={{ fontSize: '14px', fontWeight: '600', color: 'var(--text-primary)' }}>
              {user.username}
            </div>
            {deleteError && (
              <div style={{
                marginTop: '8px',
                padding: '6px 8px',
                background: 'rgba(239, 68, 68, 0.15)',
                border: '1px solid rgba(239, 68, 68, 0.3)',
                borderRadius: '4px',
                color: '#f87171',
                fontSize: '11px'
              }}>
                {deleteError}
              </div>
            )}
            <div style={{ display: 'flex', gap: '6px', marginTop: '8px' }}>
              <button
                onClick={onLogout}
                style={{
                  flex: 1,
                  padding: '6px',
                  background: '#ef4444',
                  color: 'white',
                  border: 'none',
                  borderRadius: '4px',
                  cursor: 'pointer',
                  fontSize: '12px',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  gap: '4px'
                }}
              >
                <LogOut size={14} />
                Logout
              </button>
              <button
                onClick={handleDeleteAccount}
                disabled={isDeleting}
                style={{
                  flex: 1,
                  padding: '6px',
                  background: isDeleting ? '#6b7280' : '#7f1d1d',
                  color: 'white',
                  border: 'none',
                  borderRadius: '4px',
                  cursor: isDeleting ? 'not-allowed' : 'pointer',
                  fontSize: '12px',
                  display: 'flex',
                  alignItems: 'center',
                  justifyContent: 'center',
                  gap: '4px',
                  opacity: isDeleting ? 0.7 : 1
                }}
                title="Delete your account permanently"
              >
                <Trash2 size={14} />
                {isDeleting ? '...' : 'Delete'}
              </button>
            </div>
          </div>
        )}
      </div>

      <div className="sidebar-content">
        <div>
          <button
            onClick={() => onNavigate('home')}
            className="sidebar-item"
          >
            <div className="item-left">
              <Home size={16} />
              <span>Home</span>
            </div>
          </button>
        </div>

        <div className="sidebar-section">
          <div
            onClick={() => setAnalyticsExpanded(!analyticsExpanded)}
            className="section-header"
          >
            <div className="section-title">
              {analyticsExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
              <BarChart3 size={16} />
              <span>Analytics</span>
            </div>
          </div>

          {analyticsExpanded && (
            <div>
              <div
                onClick={() => onNavigate('leaderboard')}
                className="sidebar-item"
              >
                <div className="item-left">
                  <Trophy size={14} />
                  <span>Leaderboard</span>
                </div>
              </div>
              <div
                onClick={() => onNavigate('shortest-path')}
                className="sidebar-item"
              >
                <div className="item-left">
                  <Navigation size={14} />
                  <span>Shortest Path</span>
                </div>
              </div>
            </div>
          )}
        </div>

        <div className="sidebar-section">
          <div
            onClick={() => setGraphsExpanded(!graphsExpanded)}
            className="section-header"
          >
            <div className="section-title">
              {graphsExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
              <Network size={16} />
              <span>Graphs</span>
            </div>
          </div>

          {graphsExpanded && (
            <div>
              <div
                onClick={() => onNavigate('graph', { graphId: 'communities' })}
                className="sidebar-item"
              >
                <div className="item-left">
                  <Network size={14} />
                  <span>Communities</span>
                </div>
              </div>
            </div>
          )}
        </div>

        <div className="sidebar-section">
          <div
            onClick={() => setApiExpanded(!apiExpanded)}
            className="section-header"
          >
            <div className="section-title">
              {apiExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
              <Activity size={16} />
              <span>API Tools</span>
            </div>
          </div>

          {apiExpanded && (
            <div>
              <div
                onClick={() => onNavigate('graph-explorer')}
                className="sidebar-item"
              >
                <div className="item-left">
                  <Network size={14} />
                  <span>Graph Explorer</span>
                </div>
              </div>
              <div
                onClick={() => onNavigate('messaging-hub')}
                className="sidebar-item"
              >
                <div className="item-left">
                  <MessageSquare size={14} />
                  <span>Messaging Hub</span>
                </div>
              </div>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}
