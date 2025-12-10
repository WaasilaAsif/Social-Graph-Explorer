import { useState } from 'react';
import { ChevronDown, ChevronRight, Network, Home, MessageSquare, Activity, LogOut, BarChart3, Trophy, Navigation, Globe } from 'lucide-react';
import '../styles/Sidebar.css';

export default function Sidebar({ onUserClick, onNavigate, user, onLogout }) {
  const [graphsExpanded, setGraphsExpanded] = useState(true);
  const [apiExpanded, setApiExpanded] = useState(true);
  const [analyticsExpanded, setAnalyticsExpanded] = useState(true);

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
            <button
              onClick={onLogout}
              style={{
                marginTop: '8px',
                width: '100%',
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
                gap: '6px'
              }}
            >
              <LogOut size={14} />
              Logout
            </button>
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
                onClick={() => onNavigate('graph-stats')}
                className="sidebar-item"
              >
                <div className="item-left">
                  <BarChart3 size={14} />
                  <span>Network Stats</span>
                </div>
              </div>
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
                onClick={() => onNavigate('network-overview', {})}
                className="sidebar-item"
                style={{ background: 'rgba(157, 78, 221, 0.1)', borderLeft: '3px solid #9d4edd' }}
              >
                <div className="item-left">
                  <Globe size={14} />
                  <span>Complete Overview</span>
                </div>
              </div>
              <div
                onClick={() => onNavigate('graph', { graphId: 'main' })}
                className="sidebar-item"
              >
                <div className="item-left">
                  <Network size={14} />
                  <span>Main Network</span>
                </div>
              </div>
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
