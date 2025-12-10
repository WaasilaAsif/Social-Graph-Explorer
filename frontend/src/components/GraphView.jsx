import { useState, useEffect, useRef } from 'react';
///import { getUserById } from '../data/dummyUsers';
import { graphAPI, userAPI } from '../services/api';
import '../styles/GraphView.css';

export default function GraphView({ graphId, onNodeClick }) {
  const [selectedNode, setSelectedNode] = useState(null);
  const [graphData, setGraphData] = useState({ nodes: [], edges: [] });
  const [loading, setLoading] = useState(true);
  const [algorithm, setAlgorithm] = useState(null); // 'bfs', 'dfs', 'path'
  const [algorithmResult, setAlgorithmResult] = useState(null);
  const [pathStart, setPathStart] = useState(null);
  const [pathEnd, setPathEnd] = useState(null);
  const [hoveredNode, setHoveredNode] = useState(null);
  const animationRef = useRef(null);
  const [nodePositions, setNodePositions] = useState({});

  // Fetch graph data from backend
  useEffect(() => {
    const fetchGraphData = async () => {
      try {
        setLoading(true);
        // Fetch friendships for users 1-20
        const nodes = [];
        const edges = [];
        const edgeSet = new Set();
        const userCache = new Map(); // Cache user details

        // Helper function to get user details
        const getUserDetails = async (userId) => {
          if (userCache.has(userId)) {
            return userCache.get(userId);
          }
          try {
            const userData = await userAPI.getUser(userId);
            userCache.set(userId, userData);
            return userData;
          } catch (error) {
            console.error(`Failed to fetch user ${userId}:`, error);
            return null;
          }
        };

        for (let userId = 1; userId <= 20; userId++) {
          try {
            const response = await graphAPI.getFriends(userId);
            if (response.success) {
              // Get user details for the label
              const userData = await getUserDetails(userId);
              const username = userData?.user?.username || `User ${userId}`;

              // Add node if not exists
              if (!nodes.find(n => n.id === userId)) {
                nodes.push({ 
                  id: userId, 
                  label: username,
                  group: (userId % 3) + 1
                });
              }

              // Add edges
              if (response.friends && response.friends.length > 0) {
                for (const friend of response.friends) {
                  // Handle both array of IDs and array of objects
                  const friendId = typeof friend === 'object' ? friend.id : friend;
                  
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
                    const friendData = await getUserDetails(friendId);
                    const friendUsername = friendData?.user?.username || `User ${friendId}`;
                    
                    nodes.push({ 
                      id: friendId, 
                      label: friendUsername,
                      group: (friendId % 3) + 1
                    });
                  }
                }
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

  // Force-directed layout simulation
  useEffect(() => {
    if (graphData.nodes.length === 0) return;

    const width = 1200;
    const height = 800;
    const centerX = width / 2;
    const centerY = height / 2;

    // Initialize positions in a circle with better spacing
    const initialPositions = {};
    graphData.nodes.forEach((node, idx) => {
      const angle = (2 * Math.PI * idx) / graphData.nodes.length;
      const radius = Math.min(width, height) * 0.35;
      initialPositions[node.id] = {
        x: centerX + radius * Math.cos(angle),
        y: centerY + radius * Math.sin(angle),
        vx: 0,
        vy: 0
      };
    });

    setNodePositions(initialPositions);

    // Force-directed layout parameters
    const repulsionStrength = 8000;
    const attractionStrength = 0.001;
    const damping = 0.85;
    const iterations = 300;

    let currentPositions = { ...initialPositions };
    let iteration = 0;

    const simulate = () => {
      if (iteration >= iterations) {
        cancelAnimationFrame(animationRef.current);
        return;
      }

      // Apply repulsion between all nodes
      graphData.nodes.forEach((node1) => {
        let fx = 0, fy = 0;

        graphData.nodes.forEach((node2) => {
          if (node1.id === node2.id) return;

          const dx = currentPositions[node1.id].x - currentPositions[node2.id].x;
          const dy = currentPositions[node1.id].y - currentPositions[node2.id].y;
          const distance = Math.sqrt(dx * dx + dy * dy) || 1;
          
          if (distance < 200) {
            const force = repulsionStrength / (distance * distance);
            fx += (dx / distance) * force;
            fy += (dy / distance) * force;
          }
        });

        // Apply attraction along edges
        graphData.edges.forEach((edge) => {
          if (edge.source === node1.id) {
            const dx = currentPositions[edge.target].x - currentPositions[node1.id].x;
            const dy = currentPositions[edge.target].y - currentPositions[node1.id].y;
            fx += dx * attractionStrength;
            fy += dy * attractionStrength;
          } else if (edge.target === node1.id) {
            const dx = currentPositions[edge.source].x - currentPositions[node1.id].x;
            const dy = currentPositions[edge.source].y - currentPositions[node1.id].y;
            fx += dx * attractionStrength;
            fy += dy * attractionStrength;
          }
        });

        // Apply center gravity
        const dcx = centerX - currentPositions[node1.id].x;
        const dcy = centerY - currentPositions[node1.id].y;
        fx += dcx * 0.0001;
        fy += dcy * 0.0001;

        currentPositions[node1.id].vx = (currentPositions[node1.id].vx + fx) * damping;
        currentPositions[node1.id].vy = (currentPositions[node1.id].vy + fy) * damping;
      });

      // Update positions
      graphData.nodes.forEach((node) => {
        currentPositions[node.id].x += currentPositions[node.id].vx;
        currentPositions[node.id].y += currentPositions[node.id].vy;

        // Keep within bounds
        currentPositions[node.id].x = Math.max(100, Math.min(width - 100, currentPositions[node.id].x));
        currentPositions[node.id].y = Math.max(100, Math.min(height - 100, currentPositions[node.id].y));
      });

      setNodePositions({ ...currentPositions });
      iteration++;
      animationRef.current = requestAnimationFrame(simulate);
    };

    animationRef.current = requestAnimationFrame(simulate);

    return () => {
      if (animationRef.current) {
        cancelAnimationFrame(animationRef.current);
      }
    };
  }, [graphData]);

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

  // Get node position from force-directed layout
  const getNodePosition = (nodeId) => {
    return nodePositions[nodeId] || { x: 600, y: 400 };
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
    <div className="graph-view-modern">
      <div className="graph-header-modern">
        <div className="graph-title-section">
          <h2 className="graph-title-modern">
            {graphId === 'main' ? 'Social Network Graph' : 'Communities Graph'}
          </h2>
          <div className="graph-meta">
            <span className="meta-badge">
              <span className="meta-icon">👥</span>
              {graphData.nodes.length} Users
            </span>
            <span className="meta-badge">
              <span className="meta-icon">🔗</span>
              {graphData.edges.length} Connections
            </span>
          </div>
        </div>
        
        {/* Algorithm Controls */}
        <div className="algorithm-controls">
          {!algorithm && (
            <>
              <button 
                className="modern-btn btn-primary"
                onClick={() => selectedNode && runBFS(selectedNode)}
                disabled={!selectedNode}
                title="Run BFS from selected node"
              >
                🔍 BFS
              </button>
              <button 
                className="modern-btn btn-primary"
                onClick={() => selectedNode && runDFS(selectedNode)}
                disabled={!selectedNode}
                title="Run DFS from selected node"
              >
                🌲 DFS
              </button>
              <button 
                className="modern-btn btn-primary"
                onClick={() => setAlgorithm('path')}
                title="Find shortest path between two nodes"
              >
                🎯 Path
              </button>
            </>
          )}
          {algorithm && (
            <button 
              className="modern-btn btn-danger"
              onClick={clearAlgorithm}
            >
              ✕ Clear
            </button>
          )}
        </div>
      </div>

      {algorithm === 'path' && !pathEnd && (
        <div className="algorithm-banner">
          <div className="banner-icon">🎯</div>
          <div className="banner-text">
            {!pathStart ? 'Click a node to select start point' : `Start: ${graphData.nodes.find(n => n.id === pathStart)?.label} → Click another node for destination`}
          </div>
        </div>
      )}

      {algorithmResult && (
        <div className="algorithm-result-modern">
          <div className="result-header">
            {algorithm === 'bfs' && '🔍 Breadth-First Traversal'}
            {algorithm === 'dfs' && '🌲 Depth-First Traversal'}
            {algorithm === 'path' && '🎯 Shortest Path'}
          </div>
          <div className="result-path">
            {algorithmResult.map((nodeId, idx) => {
              const node = graphData.nodes.find(n => n.id === nodeId);
              return (
                <span key={nodeId} className="path-node">
                  {node?.label || `User ${nodeId}`}
                  {idx < algorithmResult.length - 1 && <span className="path-arrow">→</span>}
                </span>
              );
            })}
          </div>
        </div>
      )}

      <div className="graph-canvas-modern">
        <svg className="graph-svg-modern" viewBox="0 0 1200 800" preserveAspectRatio="xMidYMid meet">
          <defs>
            <filter id="glow">
              <feGaussianBlur stdDeviation="2.5" result="coloredBlur"/>
              <feMerge>
                <feMergeNode in="coloredBlur"/>
                <feMergeNode in="SourceGraphic"/>
              </feMerge>
            </filter>
            <linearGradient id="edgeGradient" x1="0%" y1="0%" x2="100%" y2="0%">
              <stop offset="0%" style={{ stopColor: 'rgba(147, 51, 234, 0.3)', stopOpacity: 1 }} />
              <stop offset="100%" style={{ stopColor: 'rgba(59, 130, 246, 0.3)', stopOpacity: 1 }} />
            </linearGradient>
          </defs>

          {/* Draw edges with improved styling */}
          <g className="edges-layer">
            {graphData.edges.map((edge, idx) => {
              const sourceNode = graphData.nodes.find(n => n.id === edge.source);
              const targetNode = graphData.nodes.find(n => n.id === edge.target);
              if (!sourceNode || !targetNode) return null;

              const sourcePos = getNodePosition(sourceNode.id);
              const targetPos = getNodePosition(targetNode.id);
              const isInPath = isEdgeInPath(edge.source, edge.target);
              const isConnected = hoveredNode === edge.source || hoveredNode === edge.target;

              return (
                <line
                  key={idx}
                  x1={sourcePos.x}
                  y1={sourcePos.y}
                  x2={targetPos.x}
                  y2={targetPos.y}
                  className="graph-edge-modern"
                  stroke={isInPath ? '#9d4edd' : isConnected ? 'rgba(147, 51, 234, 0.5)' : 'url(#edgeGradient)'}
                  strokeWidth={isInPath ? 4 : isConnected ? 2.5 : 1.5}
                  opacity={isInPath ? 1 : isConnected ? 0.7 : 0.3}
                  strokeLinecap="round"
                />
              );
            })}
          </g>

          {/* Draw nodes with modern styling */}
          <g className="nodes-layer">
            {graphData.nodes.map((node) => {
              const pos = getNodePosition(node.id);
              const isSelected = selectedNode === node.id;
              const isHighlighted = isNodeHighlighted(node.id);
              const isPathNode = pathStart === node.id || pathEnd === node.id;
              const isHovered = hoveredNode === node.id;

              const nodeRadius = isSelected ? 40 : isHovered ? 38 : isHighlighted || isPathNode ? 36 : 32;
              
              const getNodeColor = () => {
                if (isPathNode) return '#ef4444';
                if (isHighlighted) return '#9d4edd';
                if (node.group === 1) return '#3b82f6';
                if (node.group === 2) return '#8b5cf6';
                return '#10b981';
              };

              return (
                <g 
                  key={node.id} 
                  onClick={() => handleNodeClick(node.id)}
                  onMouseEnter={() => setHoveredNode(node.id)}
                  onMouseLeave={() => setHoveredNode(null)}
                  className="graph-node-modern"
                  style={{ cursor: 'pointer' }}
                >
                  {/* Outer glow ring */}
                  {(isSelected || isHovered) && (
                    <circle
                      cx={pos.x}
                      cy={pos.y}
                      r={nodeRadius + 8}
                      fill="none"
                      stroke={getNodeColor()}
                      strokeWidth={2}
                      opacity={0.3}
                      className="node-glow-ring"
                    />
                  )}
                  
                  {/* Main node circle */}
                  <circle
                    cx={pos.x}
                    cy={pos.y}
                    r={nodeRadius}
                    fill={getNodeColor()}
                    filter={isSelected || isHovered ? "url(#glow)" : "none"}
                    className="node-circle"
                  />
                  
                  {/* White border for selected */}
                  {isSelected && (
                    <circle
                      cx={pos.x}
                      cy={pos.y}
                      r={nodeRadius}
                      fill="none"
                      stroke="white"
                      strokeWidth={3}
                    />
                  )}

                  {/* Node label with background */}
                  <text
                    x={pos.x}
                    y={pos.y - nodeRadius - 12}
                    className="node-label-modern"
                    textAnchor="middle"
                    fill="white"
                    fontSize="13"
                    fontWeight="600"
                  >
                    <tspan x={pos.x} className="label-bg">
                      {node.label}
                    </tspan>
                  </text>
                  
                  {/* ID badge inside node */}
                  <text
                    x={pos.x}
                    y={pos.y + 5}
                    className="node-id-badge"
                    textAnchor="middle"
                    fill="white"
                    fontSize="14"
                    fontWeight="700"
                  >
                    {node.id}
                  </text>
                </g>
              );
            })}
          </g>
        </svg>

        {/* Side Stats Panel */}
        <div className="graph-stats-modern">
          <div className="stats-header">
            <span className="stats-icon">📊</span>
            <h3>Network Stats</h3>
          </div>
          
          <div className="stat-card">
            <div className="stat-label">Total Users</div>
            <div className="stat-value">{graphData.nodes.length}</div>
          </div>
          
          <div className="stat-card">
            <div className="stat-label">Friendships</div>
            <div className="stat-value">{graphData.edges.length}</div>
          </div>
          
          <div className="stat-card">
            <div className="stat-label">Network Density</div>
            <div className="stat-value">
              {graphData.nodes.length > 1
                ? ((graphData.edges.length * 2 / (graphData.nodes.length * (graphData.nodes.length - 1))) * 100).toFixed(1) + '%'
                : '0%'}
            </div>
          </div>
          
          <div className="stat-card">
            <div className="stat-label">Avg Connections</div>
            <div className="stat-value">
              {graphData.nodes.length > 0 
                ? (graphData.edges.length * 2 / graphData.nodes.length).toFixed(1) 
                : 0}
            </div>
          </div>

          {selectedNode && (
            <>
              <div className="stats-divider"></div>
              <div className="selected-node-info">
                <div className="selected-badge">Selected User</div>
                <div className="selected-name">
                  {graphData.nodes.find(n => n.id === selectedNode)?.label || `User ${selectedNode}`}
                </div>
                <div className="selected-id">ID: {selectedNode}</div>
              </div>
            </>
          )}

          {hoveredNode && hoveredNode !== selectedNode && (
            <>
              <div className="stats-divider"></div>
              <div className="hovered-node-info">
                <div className="hovered-badge">Hovering</div>
                <div className="hovered-name">
                  {graphData.nodes.find(n => n.id === hoveredNode)?.label || `User ${hoveredNode}`}
                </div>
              </div>
            </>
          )}
        </div>
      </div>
    </div>
  );
}
