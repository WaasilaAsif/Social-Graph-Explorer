import { useState } from 'react';

export default function DebugPanel() {
  const [isOpen, setIsOpen] = useState(false);

  const clearStorage = () => {
    localStorage.clear();
    alert('localStorage cleared! Reloading...');
    window.location.reload();
  };

  const showStorageContents = () => {
    const user = localStorage.getItem('user');
    alert(`localStorage contents:\nuser: ${user || 'null'}`);
  };

  if (!isOpen) {
    return (
      <button
        onClick={() => setIsOpen(true)}
        style={{
          position: 'fixed',
          bottom: '10px',
          right: '10px',
          padding: '8px 12px',
          background: '#6366f1',
          color: 'white',
          border: 'none',
          borderRadius: '4px',
          cursor: 'pointer',
          fontSize: '12px',
          zIndex: 9999
        }}
      >
        Debug
      </button>
    );
  }

  return (
    <div
      style={{
        position: 'fixed',
        bottom: '10px',
        right: '10px',
        background: 'white',
        border: '1px solid #ddd',
        borderRadius: '8px',
        padding: '16px',
        boxShadow: '0 4px 6px rgba(0,0,0,0.1)',
        zIndex: 9999,
        minWidth: '250px'
      }}
    >
      <h3 style={{ margin: '0 0 12px 0', fontSize: '14px' }}>Debug Tools</h3>
      <div style={{ display: 'flex', flexDirection: 'column', gap: '8px' }}>
        <button
          onClick={clearStorage}
          style={{
            padding: '6px 12px',
            background: '#ef4444',
            color: 'white',
            border: 'none',
            borderRadius: '4px',
            cursor: 'pointer',
            fontSize: '12px'
          }}
        >
          Clear Storage & Reload
        </button>
        <button
          onClick={showStorageContents}
          style={{
            padding: '6px 12px',
            background: '#3b82f6',
            color: 'white',
            border: 'none',
            borderRadius: '4px',
            cursor: 'pointer',
            fontSize: '12px'
          }}
        >
          Show Storage
        </button>
        <button
          onClick={() => setIsOpen(false)}
          style={{
            padding: '6px 12px',
            background: '#6b7280',
            color: 'white',
            border: 'none',
            borderRadius: '4px',
            cursor: 'pointer',
            fontSize: '12px'
          }}
        >
          Close
        </button>
      </div>
    </div>
  );
}
