import { useState } from 'react';
import { ChevronDown, ChevronRight, Users, Network, Home } from 'lucide-react';
import { dummyUsers } from '../data/dummyUsers';
import '../styles/Sidebar.css';

export default function Sidebar({ onUserClick, onNavigate }) {
  const [usersExpanded, setUsersExpanded] = useState(true);
  const [graphsExpanded, setGraphsExpanded] = useState(true);

  return (
    <div className="sidebar">
      <div className="sidebar-header">
        <h2>Social Graph Explorer</h2>
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
            onClick={() => setUsersExpanded(!usersExpanded)}
            className="section-header"
          >
            <div className="section-title">
              {usersExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
              <Users size={16} />
              <span>Users</span>
            </div>
          </div>

          {usersExpanded && (
            <div>
              {dummyUsers.map(user => (
                <div
                  key={user.id}
                  onClick={() => onUserClick(user)}
                  className="sidebar-item"
                >
                  <div className="item-left">
                    <div style={{
                      width: '24px',
                      height: '24px',
                      borderRadius: '50%',
                      background: 'linear-gradient(135deg, #3b82f6, #8b5cf6)',
                      display: 'flex',
                      alignItems: 'center',
                      justifyContent: 'center',
                      fontSize: '0.75rem',
                      fontWeight: '600',
                      color: 'white'
                    }}>
                      {user.avatar}
                    </div>
                    <span>{user.name}</span>
                  </div>
                </div>
              ))}
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
      </div>
    </div>
  );
}
