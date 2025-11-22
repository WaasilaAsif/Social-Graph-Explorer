import { X } from 'lucide-react';
import { getUserById } from '../data/dummyUsers';
import { getNodeConnections } from '../data/dummyGraph';
import '../styles/RightInfoPane.css';

export default function RightInfoPane({ selectedNode, onClose, onUserClick }) {
  if (!selectedNode) {
    return (
      <div className="right-info-pane" style={{ alignItems: 'center', justifyContent: 'center' }}>
        <p style={{ color: 'var(--text-muted)', fontSize: '0.875rem' }}>
          Select a node to view details
        </p>
      </div>
    );
  }

  const user = getUserById(selectedNode.id);
  const connections = getNodeConnections(selectedNode.id);

  return (
    <div className="right-info-pane">
      <div className="info-pane-header">
        <h3 className="info-pane-title">Node Details</h3>
        <button onClick={onClose}>
          <X size={16} />
        </button>
      </div>

      <div className="info-pane-content">
        {user && (
          <>
            <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', textAlign: 'center', marginBottom: '1.5rem' }}>
              <div style={{
                width: '64px',
                height: '64px',
                borderRadius: '50%',
                background: 'linear-gradient(135deg, #3b82f6, #8b5cf6)',
                display: 'flex',
                alignItems: 'center',
                justifyContent: 'center',
                fontSize: '1.25rem',
                fontWeight: '600',
                color: 'white',
                marginBottom: '0.75rem'
              }}>
                {user.avatar}
              </div>
              <h4 style={{ fontSize: '1.125rem', fontWeight: '600' }}>{user.name}</h4>
              <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.25rem' }}>
                Node ID: {user.id}
              </p>
            </div>

            <div className="info-section">
              <div className="info-section-title">Bio</div>
              <p style={{ fontSize: '0.875rem', color: 'var(--text-secondary)' }}>{user.bio}</p>
            </div>

            <div className="info-section">
              <div className="info-section-title">Statistics</div>
              <div className="info-item">
                <span className="info-label">Followers</span>
                <span className="info-value">{user.followers}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Following</span>
                <span className="info-value">{user.following}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Posts</span>
                <span className="info-value">{user.posts}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Connections</span>
                <span className="info-value">{connections.length}</span>
              </div>
            </div>

            <div className="info-section">
              <div className="info-section-title">Connected Nodes</div>
              <div style={{ display: 'flex', flexDirection: 'column', gap: '0.5rem' }}>
                {connections.map((connId) => {
                  const connUser = getUserById(connId);
                  return (
                    <button
                      key={connId}
                      onClick={() => onUserClick(connUser)}
                      className="quick-action-button"
                    >
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
                        {connUser?.avatar}
                      </div>
                      <span style={{ overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>
                        {connUser?.name}
                      </span>
                    </button>
                  );
                })}
              </div>
            </div>

            <div className="info-section">
              <div className="info-section-title">Graph Properties</div>
              <div className="info-item">
                <span className="info-label">Degree</span>
                <span className="info-value">{connections.length}</span>
              </div>
              <div className="info-item">
                <span className="info-label">Group</span>
                <span className="info-value">{selectedNode.group}</span>
              </div>
            </div>

            <button
              onClick={() => onUserClick(user)}
              style={{
                width: '100%',
                marginTop: '1rem',
                padding: '0.75rem',
                backgroundColor: '#3b82f6',
                color: 'white',
                fontWeight: '500',
                borderRadius: '4px',
                fontSize: '0.875rem',
                transition: 'background-color 0.2s'
              }}
              onMouseOver={(e) => e.currentTarget.style.backgroundColor = '#2563eb'}
              onMouseOut={(e) => e.currentTarget.style.backgroundColor = '#3b82f6'}
            >
              View Full Profile
            </button>
          </>
        )}
      </div>
    </div>
  );
}
