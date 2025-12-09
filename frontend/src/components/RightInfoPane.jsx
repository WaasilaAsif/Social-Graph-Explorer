import { X } from 'lucide-react';
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

  const userName = selectedNode.name || selectedNode.label || `User ${selectedNode.id}`;
  const connections = selectedNode.connections || [];

  return (
    <div className="right-info-pane">
      <div className="info-pane-header">
        <h3 className="info-pane-title">Node Details</h3>
        <button onClick={onClose}>
          <X size={16} />
        </button>
      </div>

      <div className="info-pane-content">
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
            {userName.charAt(0).toUpperCase()}
          </div>
          <h4 style={{ fontSize: '1.125rem', fontWeight: '600' }}>{userName}</h4>
          <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', marginTop: '0.25rem' }}>
            Node ID: {selectedNode.id}
          </p>
        </div>

        <div className="info-section">
          <div className="info-section-title">Statistics</div>
          <div className="info-item">
            <span className="info-label">Node ID</span>
            <span className="info-value">{selectedNode.id}</span>
          </div>
          <div className="info-item">
            <span className="info-label">Connections</span>
            <span className="info-value">{connections.length}</span>
          </div>
          {selectedNode.degree && (
            <div className="info-item">
              <span className="info-label">Degree</span>
              <span className="info-value">{selectedNode.degree}</span>
            </div>
          )}
        </div>

        {connections.length > 0 && (
          <div className="info-section">
            <div className="info-section-title">Connected Nodes</div>
            <div style={{ display: 'flex', flexDirection: 'column', gap: '0.5rem' }}>
              {connections.slice(0, 10).map((connId) => (
                <button
                  key={connId}
                  onClick={() => onUserClick && onUserClick({ id: connId, name: `User ${connId}` })}
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
                    {String(connId).charAt(0)}
                  </div>
                  <span style={{ overflow: 'hidden', textOverflow: 'ellipsis', whiteSpace: 'nowrap' }}>
                    User {connId}
                  </span>
                </button>
              ))}
              {connections.length > 10 && (
                <p style={{ fontSize: '0.75rem', color: 'var(--text-muted)', textAlign: 'center', marginTop: '0.5rem' }}>
                  + {connections.length - 10} more connections
                </p>
              )}
            </div>
          </div>
        )}

        <button
          onClick={() => onUserClick && onUserClick({ id: selectedNode.id, name: userName })}
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
      </div>
    </div>
  );
}
