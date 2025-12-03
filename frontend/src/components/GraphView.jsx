import { useState, useEffect } from 'react';
import { getUserById } from '../data/dummyUsers';
import { graphAPI } from '../services/api';
import '../styles/GraphView.css';

export default function GraphView({ graphId, onNodeClick }) {
  const [selectedNode, setSelectedNode] = useState(null);
  const [graphData, setGraphData] = useState({ nodes: [], edges: [] });
  const [loading, setLoading] = useState(true);
  const [algorithm, setAlgorithm] = useState(null); // 'bfs', 'dfs', 'path'
  const [algorithmResult, setAlgorithmResult] = useState(null);
  const [pathStart, setPathStart] = useState(null);
  const [pathEnd, setPathEnd] = useState(null);

  // Fetch graph data from backend
  useEffect(() => {
    const fetchGraphData = async () => {
      try {
        setLoading(true);
        // Fetch friendships for users 1-20
        const nodes = [];
        const edges = [];
        const edgeSet = new Set();

        for (let userId = 1; userId <= 20; userId++) {
          try {
            const response = await graphAPI.getFriends(userId);
            if (response.success) {
              // Add node if not exists
              if (!nodes.find(n => n.id === userId)) {
                nodes.push({ 
                  id: userId, 
                  label: `User ${userId}`,
                  group: (userId % 3) + 1,
                  friends: response.friends || []
                });
              }

              // Add edges
              if (response.friends && response.friends.length > 0) {
                response.friends.forEach(friend => {
                  const friendId = friend.id;
                  const edgeId = userId < friendId 
                    ? `${userId}-${friendId}` 
                    : `${friendId}-${userId}`;
                  
                  if (!edgeSet.has(edgeId)) {
                    edgeSet.add(edgeId);
                    edges.push({
                      source: userId,
                      target: friendId,
                      weight: 0.7
                    });
                  }

                  // Add friend node if not exists
                  if (!nodes.find(n => n.id === friendId)) {
                    nodes.push({ 
                      id: friendId, 
                      label: `User ${friendId}`,
                      group: (friendId % 3) + 1,
                      friends: []
                    });
                  }
                });
              }
            }
          } catch (error) {
            console.error(`Failed to fetch friends for user ${userId}:`, error);
          }
        }

        setGraphData({ nodes, edges });
      } catch (error) {
        console.error('Failed to fetch graph data:', error);
      } finally {
        setLoading(false);
      }
    };

    fetchGraphData();
  }, []);

  const handleNodeClick = (nodeId) => {
    // Handle path finding mode
    if (algorithm === 'path') {
      if (!pathStart) {
        setPathStart(nodeId);
        setSelectedNode(nodeId);
      } else if (!pathEnd && nodeId !== pathStart) {
        setPathEnd(nodeId);
        findShortestPath(pathStart, nodeId);
      } else {
        // Reset path finding
        setPathStart(nodeId);
        setPathEnd(null);
        setAlgorithmResult(null);
        setSelectedNode(nodeId);
      }
    } else {
      setSelectedNode(nodeId);
      const user = getUserById(nodeId);
      if (user && onNodeClick) {
        onNodeClick(user);
      }
    }
  };

  const runBFS = async (startNode) => {
    try {
      setAlgorithm('bfs');
      setSelectedNode(startNode);
      const response = await graphAPI.bfs(startNode);
      if (response.traversal) {
        setAlgorithmResult(response.traversal);
      }
    } catch (error) {
      console.error('BFS failed:', error);
      alert('Failed to run BFS. Make sure the server is running.');
    }
  };

  const runDFS = async (startNode) => {
    try {
      setAlgorithm('dfs');
      setSelectedNode(startNode);
      const response = await graphAPI.dfs(startNode);
      if (response.traversal) {
        setAlgorithmResult(response.traversal);
      }
    } catch (error) {
      console.error('DFS failed:', error);
      alert('Failed to run DFS. Make sure the server is running.');
    }
  };

  const findShortestPath = async (start, end) => {
    try {
      const response = await graphAPI.shortestPath(start, end);
      if (response.path) {
        setAlgorithmResult(response.path);
      }
    } catch (error) {
      console.error('Shortest path failed:', error);
      alert('Failed to find shortest path. Make sure the server is running.');
    }
  };

  const clearAlgorithm = () => {
    setAlgorithm(null);
    setAlgorithmResult(null);
    setPathStart(null);
    setPathEnd(null);
    setSelectedNode(null);
  };

  // Calculate node position
  const getNodePosition = (nodeId, totalNodes) => {
    const radius = 250;
    const centerX = 400;
    const centerY = 300;
    const angle = (2 * Math.PI * nodeId) / totalNodes;
    return {
      x: centerX + radius * Math.cos(angle),
      y: centerY + radius * Math.sin(angle)
    };
  };

  // Check if node is in algorithm result
  const isNodeHighlighted = (nodeId) => {
    if (!algorithmResult) return false;
    return algorithmResult.includes(nodeId);
  };

  // Check if edge is in shortest path
  const isEdgeInPath = (source, target) => {
    if (!algorithmResult || algorithm !== 'path') return false;
    for (let i = 0; i < algorithmResult.length - 1; i++) {
      if ((algorithmResult[i] === source && algorithmResult[i + 1] === target) ||
          (algorithmResult[i] === target && algorithmResult[i + 1] === source)) {
        return true;
      }
    }
    return false;
  };

  if (loading) {
    return (
      <div className="graph-view">
        <div className="graph-header">
          <h2 className="graph-title">Loading Graph...</h2>
        </div>
        <div className="graph-canvas" style={{ display: 'flex', alignItems: 'center', justifyContent: 'center' }}>
          <p style={{ color: 'var(--text-secondary)' }}>Fetching graph data from backend...</p>
        </div>
      </div>
    );
  }

  return (
    <div className="graph-view">
      <div className="graph-header">
        <div>
          <h2 className="graph-title">
            {graphId === 'main' ? 'Social Network Graph' : 'Communities Graph'}
          </h2>
          <p className="text-sm" style={{ color: 'var(--text-secondary)', marginTop: '0.25rem' }}>
            {graphData.nodes.length} users, {graphData.edges.length} friendships
          </p>
        </div>
        
        {/* Algorithm Controls */}
        <div style={{ display: 'flex', gap: '8px', flexWrap: 'wrap' }}>
          {!algorithm && (
            <>
              <button 
                className="algorithm-btn"
                onClick={() => selectedNode && runBFS(selectedNode)}
                disabled={!selectedNode}
                title="Run BFS from selected node"
              >
                BFS
              </button>
              <button 
                className="algorithm-btn"
                onClick={() => selectedNode && runDFS(selectedNode)}
                disabled={!selectedNode}
                title="Run DFS from selected node"
              >
                DFS
              </button>
              <button 
                className="algorithm-btn"
                onClick={() => setAlgorithm('path')}
                title="Find shortest path between two nodes"
              >
                Shortest Path
              </button>
            </>
          )}
          {algorithm && (
            <button 
              className="algorithm-btn"
              onClick={clearAlgorithm}
              style={{ background: 'var(--danger)' }}
            >
              Clear
            </button>
          )}
        </div>
      </div>

      {algorithm === 'path' && !pathEnd && (
        <div style={{ 
          padding: '12px', 
          background: 'var(--background-tertiary)', 
          borderRadius: '8px',
          margin: '12px',
          color: 'var(--text-secondary)'
        }}>
          {!pathStart ? 'Select start node' : `Start: ${pathStart} - Now select end node`}
        </div>
      )}

      {algorithmResult && (
        <div style={{ 
          padding: '12px', 
          background: 'var(--background-tertiary)', 
          borderRadius: '8px',
          margin: '12px'
        }}>
          <strong style={{ color: 'var(--text-primary)' }}>
            {algorithm === 'bfs' && 'BFS Traversal: '}
            {algorithm === 'dfs' && 'DFS Traversal: '}
            {algorithm === 'path' && 'Shortest Path: '}
          </strong>
          <span style={{ color: 'var(--accent)' }}>
            {algorithmResult.join(' → ')}
          </span>
        </div>
      )}

      <div className="graph-canvas">
        <svg className="graph-svg" viewBox="0 0 800 600">
          {/* Draw edges */}
          {graphData.edges.map((edge, idx) => {
            const sourceNode = graphData.nodes.find(n => n.id === edge.source);
            const targetNode = graphData.nodes.find(n => n.id === edge.target);
            if (!sourceNode || !targetNode) return null;

            const sourcePos = getNodePosition(sourceNode.id, graphData.nodes.length);
            const targetPos = getNodePosition(targetNode.id, graphData.nodes.length);
            const isInPath = isEdgeInPath(edge.source, edge.target);

            return (
              <line
                key={idx}
                x1={sourcePos.x}
                y1={sourcePos.y}
                x2={targetPos.x}
                y2={targetPos.y}
                className="graph-edge"
                stroke={isInPath ? 'var(--accent)' : 'var(--border)'}
                strokeWidth={isInPath ? 3 : 1.5}
                opacity={isInPath ? 1 : 0.4}
              />
            );
          })}

          {/* Draw nodes */}
          {graphData.nodes.map((node) => {
            const pos = getNodePosition(node.id, graphData.nodes.length);
            const isSelected = selectedNode === node.id;
            const isHighlighted = isNodeHighlighted(node.id);
            const isPathNode = pathStart === node.id || pathEnd === node.id;

            return (
              <g 
                key={node.id} 
                onClick={() => handleNodeClick(node.id)} 
                className={`graph-node ${isSelected ? 'graph-node-selected' : ''}`}
                style={{ cursor: 'pointer' }}
              >
                <circle
                  cx={pos.x}
                  cy={pos.y}
                  r={isSelected ? 28 : isHighlighted || isPathNode ? 26 : 22}
                  fill={
                    isPathNode ? '#ef4444' :
                    isHighlighted ? 'var(--accent)' :
                    node.group === 1 ? '#3b82f6' :
                    node.group === 2 ? '#8b5cf6' :
                    '#10b981'
                  }
                  stroke={isSelected ? '#fff' : 'transparent'}
                  strokeWidth={isSelected ? 3 : 0}
                />
                <text
                  x={pos.x}
                  y={pos.y + 5}
                  className="graph-node-label"
                  style={{ 
                    fontWeight: '600',
                    fill: '#fff',
                    fontSize: '14px',
                    textAnchor: 'middle'
                  }}
                >
                  {node.id}
                </text>
              </g>
            );
          })}
        </svg>

        <div className="graph-stats">
          <p className="text-xs" style={{ color: 'var(--text-secondary)', marginBottom: '0.5rem' }}>
            Graph Stats
          </p>
          <div className="stat-item">
            <span className="stat-label">Total Users</span>
            <span className="stat-value">{graphData.nodes.length}</span>
          </div>
          <div className="stat-item">
            <span className="stat-label">Friendships</span>
            <span className="stat-value">{graphData.edges.length}</span>
          </div>
          <div className="stat-item">
            <span className="stat-label">Avg Connections</span>
            <span className="stat-value">
              {graphData.nodes.length > 0 
                ? (graphData.edges.length * 2 / graphData.nodes.length).toFixed(1) 
                : 0}
            </span>
          </div>
          {selectedNode && (
            <>
              <div style={{ 
                borderTop: '1px solid var(--border)', 
                margin: '8px 0', 
                paddingTop: '8px' 
              }}>
                <p className="text-xs" style={{ color: 'var(--text-secondary)', marginBottom: '0.5rem' }}>
                  Selected User {selectedNode}
                </p>
              </div>
              <div className="stat-item">
                <span className="stat-label">Friends</span>
                <span className="stat-value">
                  {graphData.nodes.find(n => n.id === selectedNode)?.friends?.length || 0}
                </span>
              </div>
            </>
          )}
        </div>
      </div>
    </div>
  );
}
