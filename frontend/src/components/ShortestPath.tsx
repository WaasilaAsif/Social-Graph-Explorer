import { useState } from 'react';
import { algoAPI } from '../services/api';
import { MapPin, ArrowRight, Search, Navigation } from 'lucide-react';
import '../styles/ShortestPath.css';

const ShortestPath = () => {
  const [startUser, setStartUser] = useState<string>('');
  const [endUser, setEndUser] = useState<string>('');
  const [path, setPath] = useState<number[]>([]);
  const [distance, setDistance] = useState<number | null>(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);

  const findPath = async () => {
    if (!startUser || !endUser) {
      setError('Please enter both user IDs');
      return;
    }

    const start = parseInt(startUser);
    const end = parseInt(endUser);

    if (isNaN(start) || isNaN(end)) {
      setError('Please enter valid user IDs');
      return;
    }

    setLoading(true);
    setError(null);
    setPath([]);
    setDistance(null);

    try {
      const result = await algoAPI.getShortestPath(start, end);
      
      if (result.path && result.path.length > 0) {
        setPath(result.path);
        setDistance(result.distance || result.path.length - 1);
      } else {
        setError('No path found between these users');
      }
    } catch (err: any) {
      setError(err.message || 'Failed to find path');
    } finally {
      setLoading(false);
    }
  };

  const handleKeyPress = (e: React.KeyboardEvent) => {
    if (e.key === 'Enter') {
      findPath();
    }
  };

  return (
    <div className="shortest-path-container">
      <div className="path-header">
        <h1><Navigation size={32} /> Shortest Path Finder</h1>
        <p>Find the shortest connection path between any two users</p>
      </div>

      <div className="path-search-box">
        <div className="input-group">
          <label>Start User ID</label>
          <div className="input-with-icon">
            <MapPin size={20} />
            <input
              type="number"
              value={startUser}
              onChange={(e) => setStartUser(e.target.value)}
              onKeyPress={handleKeyPress}
              placeholder="Enter user ID..."
            />
          </div>
        </div>

        <ArrowRight size={24} className="arrow-icon" />

        <div className="input-group">
          <label>End User ID</label>
          <div className="input-with-icon">
            <MapPin size={20} />
            <input
              type="number"
              value={endUser}
              onChange={(e) => setEndUser(e.target.value)}
              onKeyPress={handleKeyPress}
              placeholder="Enter user ID..."
            />
          </div>
        </div>

        <button onClick={findPath} disabled={loading} className="find-path-btn">
          <Search size={20} />
          {loading ? 'Searching...' : 'Find Path'}
        </button>
      </div>

      {error && (
        <div className="path-error">
          <p>{error}</p>
        </div>
      )}

      {path.length > 0 && (
        <div className="path-result">
          <div className="result-header">
            <h2>Path Found!</h2>
            <div className="result-stats">
              <div className="stat-badge">
                <span className="stat-label">Distance:</span>
                <span className="stat-value">{distance} {distance === 1 ? 'hop' : 'hops'}</span>
              </div>
              <div className="stat-badge">
                <span className="stat-label">Nodes:</span>
                <span className="stat-value">{path.length}</span>
              </div>
            </div>
          </div>

          <div className="path-visualization">
            {path.map((userId, index) => (
              <div key={index} className="path-segment">
                <div className="path-node">
                  <div className="node-circle">
                    <span>{userId}</span>
                  </div>
                  <div className="node-label">User {userId}</div>
                </div>
                {index < path.length - 1 && (
                  <div className="path-connector">
                    <ArrowRight size={24} />
                  </div>
                )}
              </div>
            ))}
          </div>

          <div className="path-description">
            <p>
              The shortest path from <strong>User {path[0]}</strong> to <strong>User {path[path.length - 1]}</strong> is {distance} {distance === 1 ? 'connection' : 'connections'} away.
            </p>
          </div>
        </div>
      )}

      {!loading && !error && path.length === 0 && (
        <div className="path-placeholder">
          <Navigation size={64} />
          <p>Enter two user IDs to find the shortest connection path</p>
        </div>
      )}
    </div>
  );
};

export default ShortestPath;
