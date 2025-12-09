import { useState, useEffect } from 'react';
import { algoAPI, graphAPI } from '../services/api';
import { BarChart3, Users, Network, TrendingUp } from 'lucide-react';
import '../styles/GraphStats.css';

interface GraphStatsData {
  numNodes: number;
  numEdges: number;
  avgDegree: number;
  maxDegree: number;
  density: number;
}

const GraphStats = () => {
  const [stats, setStats] = useState<GraphStatsData | null>(null);
  const [components, setComponents] = useState<any>(null);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    loadData();
  }, []);

  const loadData = async () => {
    setLoading(true);
    setError(null);
    try {
      const [statsData, componentsData] = await Promise.all([
        algoAPI.getGraphStats(),
        graphAPI.getComponents()
      ]);
      setStats(statsData);
      setComponents(componentsData);
    } catch (err: any) {
      setError(err.message || 'Failed to load graph statistics');
    } finally {
      setLoading(false);
    }
  };

  if (loading) {
    return (
      <div className="graph-stats-loading">
        <div className="spinner"></div>
        <p>Loading graph analytics...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="graph-stats-error">
        <p>Error: {error}</p>
        <button onClick={loadData}>Retry</button>
      </div>
    );
  }

  return (
    <div className="graph-stats-container">
      <div className="stats-header">
        <h1><BarChart3 size={32} /> Network Analytics</h1>
        <p>Comprehensive statistics about your social network graph</p>
      </div>

      <div className="stats-grid">
        {/* Total Users */}
        <div className="stat-card">
          <div className="stat-icon users">
            <Users size={28} />
          </div>
          <div className="stat-content">
            <h3>Total Users</h3>
            <div className="stat-value">{stats?.numNodes || 0}</div>
            <p>Active network members</p>
          </div>
        </div>

        {/* Total Connections */}
        <div className="stat-card">
          <div className="stat-icon connections">
            <Network size={28} />
          </div>
          <div className="stat-content">
            <h3>Total Connections</h3>
            <div className="stat-value">{stats?.numEdges || 0}</div>
            <p>Friendships in network</p>
          </div>
        </div>

        {/* Average Degree */}
        <div className="stat-card">
          <div className="stat-icon avg">
            <TrendingUp size={28} />
          </div>
          <div className="stat-content">
            <h3>Avg Connections</h3>
            <div className="stat-value">{stats?.avgDegree?.toFixed(2) || 0}</div>
            <p>Per user</p>
          </div>
        </div>

        {/* Max Degree */}
        <div className="stat-card">
          <div className="stat-icon max">
            <BarChart3 size={28} />
          </div>
          <div className="stat-content">
            <h3>Most Connected</h3>
            <div className="stat-value">{stats?.maxDegree || 0}</div>
            <p>Friends</p>
          </div>
        </div>

        {/* Network Density */}
        <div className="stat-card wide">
          <div className="stat-icon density">
            <Network size={28} />
          </div>
          <div className="stat-content">
            <h3>Network Density</h3>
            <div className="stat-value">{((stats?.density || 0) * 100).toFixed(2)}%</div>
            <p>How interconnected the network is</p>
            <div className="density-bar">
              <div 
                className="density-fill" 
                style={{ width: `${((stats?.density || 0) * 100)}%` }}
              ></div>
            </div>
          </div>
        </div>

        {/* Connected Components */}
        {components && (
          <div className="stat-card wide">
            <div className="stat-icon components">
              <Network size={28} />
            </div>
            <div className="stat-content">
              <h3>Network Components</h3>
              <div className="stat-value">{components.numComponents || 0}</div>
              <p>Separate connected groups</p>
              {components.componentSizes && components.componentSizes.length > 0 && (
                <div className="component-details">
                  <p className="component-info">
                    Largest component: {Math.max(...components.componentSizes)} users
                  </p>
                  <p className="component-info">
                    Smallest component: {Math.min(...components.componentSizes)} users
                  </p>
                </div>
              )}
            </div>
          </div>
        )}
      </div>

      <div className="stats-footer">
        <button onClick={loadData} className="refresh-btn">
          <TrendingUp size={16} /> Refresh Data
        </button>
      </div>
    </div>
  );
};

export default GraphStats;
