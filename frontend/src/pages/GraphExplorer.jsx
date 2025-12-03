import { useState } from 'react';
import { graphAPI } from '../services/api';
import { Network, Users, ArrowRight, Search } from 'lucide-react';
import '../styles/GraphExplorer.css';

export default function GraphExplorer() {
  const [activeSection, setActiveSection] = useState('friends');
  const [userId, setUserId] = useState('1');
  const [user2Id, setUser2Id] = useState('');
  const [result, setResult] = useState(null);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState(null);

  const handleGetFriends = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.getFriends(parseInt(userId));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleAddFriend = async () => {
    if (!user2Id) {
      setError('Please enter User 2 ID');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.addFriend(parseInt(userId), parseInt(user2Id));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleRemoveFriend = async () => {
    if (!user2Id) {
      setError('Please enter User 2 ID');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.removeFriend(parseInt(userId), parseInt(user2Id));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleBFS = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.bfs(parseInt(userId));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleDFS = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.dfs(parseInt(userId));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  const handleShortestPath = async () => {
    if (!user2Id) {
      setError('Please enter destination user ID');
      return;
    }
    setLoading(true);
    setError(null);
    try {
      const data = await graphAPI.shortestPath(parseInt(userId), parseInt(user2Id));
      setResult(data);
    } catch (err) {
      setError(err.message);
    } finally {
      setLoading(false);
    }
  };

  return (
    <div className="graph-explorer">
      <div className="graph-header">
        <Network size={24} />
        <h1>Graph Explorer</h1>
        <p>Explore social network connections using graph algorithms</p>
      </div>

      <div className="graph-sections">
        <button
          className={`section-btn ${activeSection === 'friends' ? 'active' : ''}`}
          onClick={() => setActiveSection('friends')}
        >
          <Users size={16} />
          Friends Management
        </button>
        <button
          className={`section-btn ${activeSection === 'traversal' ? 'active' : ''}`}
          onClick={() => setActiveSection('traversal')}
        >
          <Search size={16} />
          Graph Traversal
        </button>
        <button
          className={`section-btn ${activeSection === 'path' ? 'active' : ''}`}
          onClick={() => setActiveSection('path')}
        >
          <ArrowRight size={16} />
          Shortest Path
        </button>
      </div>

      <div className="graph-content">
        {activeSection === 'friends' && (
          <div className="section-content">
            <h2>Friends Management</h2>
            
            <div className="input-group">
              <label>User ID</label>
              <input
                type="number"
                value={userId}
                onChange={(e) => setUserId(e.target.value)}
                placeholder="Enter user ID"
              />
            </div>

            <button className="action-btn primary" onClick={handleGetFriends}>
              Get Friends List
            </button>

            <div className="divider"></div>

            <div className="input-group">
              <label>User 2 ID (for add/remove)</label>
              <input
                type="number"
                value={user2Id}
                onChange={(e) => setUser2Id(e.target.value)}
                placeholder="Enter second user ID"
              />
            </div>

            <div className="button-row">
              <button className="action-btn success" onClick={handleAddFriend}>
                Add Friend
              </button>
              <button className="action-btn danger" onClick={handleRemoveFriend}>
                Remove Friend
              </button>
            </div>
          </div>
        )}

        {activeSection === 'traversal' && (
          <div className="section-content">
            <h2>Graph Traversal Algorithms</h2>
            
            <div className="input-group">
              <label>Start User ID</label>
              <input
                type="number"
                value={userId}
                onChange={(e) => setUserId(e.target.value)}
                placeholder="Enter starting user ID"
              />
            </div>

            <div className="button-row">
              <button className="action-btn primary" onClick={handleBFS}>
                Run BFS (Breadth-First Search)
              </button>
              <button className="action-btn primary" onClick={handleDFS}>
                Run DFS (Depth-First Search)
              </button>
            </div>

            <div className="info-box">
              <p><strong>BFS:</strong> Explores nodes level by level, finding shortest paths.</p>
              <p><strong>DFS:</strong> Explores as far as possible along each branch before backtracking.</p>
            </div>
          </div>
        )}

        {activeSection === 'path' && (
          <div className="section-content">
            <h2>Shortest Path Finder</h2>
            
            <div className="input-group">
              <label>Source User ID</label>
              <input
                type="number"
                value={userId}
                onChange={(e) => setUserId(e.target.value)}
                placeholder="Enter source user ID"
              />
            </div>

            <div className="input-group">
              <label>Destination User ID</label>
              <input
                type="number"
                value={user2Id}
                onChange={(e) => setUser2Id(e.target.value)}
                placeholder="Enter destination user ID"
              />
            </div>

            <button className="action-btn primary" onClick={handleShortestPath}>
              Find Shortest Path
            </button>

            <div className="info-box">
              <p>Finds the shortest connection path between two users in the social network.</p>
            </div>
          </div>
        )}

        {loading && (
          <div className="result-box loading">
            <div className="spinner"></div>
            <p>Loading...</p>
          </div>
        )}

        {error && (
          <div className="result-box error">
            <h3>Error</h3>
            <p>{error}</p>
          </div>
        )}

        {result && !loading && (
          <div className="result-box success">
            <h3>Result</h3>
            <pre>{JSON.stringify(result, null, 2)}</pre>
          </div>
        )}
      </div>
    </div>
  );
}
