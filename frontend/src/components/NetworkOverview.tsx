import { useState, useEffect, useRef } from 'react';
import { graphAPI, userAPI, algoAPI } from '../services/api';
import '../styles/NetworkOverview.css';

export default function NetworkOverview() {
  const [graphData, setGraphData] = useState({ nodes: [], edges: [] });
  const [stats, setStats] = useState(null);
  const [loading, setLoading] = useState(true);
  const [nodePositions, setNodePositions] = useState({});
  const [selectedComponent, setSelectedComponent] = useState(null);
  const [hoveredNode, setHoveredNode] = useState(null);
  const animationRef = useRef(null);

  // Fetch comprehensive network data
  useEffect(() => {
    const fetchNetworkData = async () => {
      try {
        setLoading(true);
        const nodes = [];
        const edges = [];
        const edgeSet = new Set();
        const userCache = new Map();

        // Helper to get user details
        const getUserDetails = async (userId) => {
          if (userCache.has(userId)) {
            return userCache.get(userId);
          }
          try {
            const userData = await userAPI.getUser(userId);
            userCache.set(userId, userData);
            return userData;
          } catch (error) {
            return null;
          }
        };

        // Fetch ALL users (up to 100 for overview)
        for (let userId = 1; userId <= 100; userId++) {
          try {
            const response = await graphAPI.getFriends(userId);
            if (response.success) {
              const userData = await getUserDetails(userId);
              const username = userData?.user?.username || `User ${userId}`;

              if (!nodes.find(n => n.id === userId)) {
                nodes.push({ 
                  id: userId, 
                  label: username,
                  degree: response.friends?.length || 0
                });
              }

              if (response.friends && response.friends.length > 0) {
                for (const friendId of response.friends) {
                  const edgeId = userId < friendId 
                    ? `${userId}-${friendId}` 
                    : `${friendId}-${userId}`;
                  
                  if (!edgeSet.has(edgeId)) {
                    edgeSet.add(edgeId);
                    edges.push({
                      source: userId,
                      target: friendId
                    });
                  }

                  if (!nodes.find(n => n.id === friendId)) {
                    const friendData = await getUserDetails(friendId);
                    const friendUsername = friendData?.user?.username || `User ${friendId}`;
                    nodes.push({ 
                      id: friendId, 
                      label: friendUsername,
                      degree: 0
                    });
                  }
                }
              }
            }
          } catch (error) {
            // User doesn't exist, continue
            continue;
          }
        }

        // Update degrees
        nodes.forEach(node => {
          node.degree = edges.filter(e => e.source === node.id || e.target === node.id).length;
        });

        setGraphData({ nodes, edges });

        // Fetch graph statistics
        try {
          const statsResponse = await algoAPI.getGraphStats();
          if (statsResponse.success) {
            setStats(statsResponse.stats);
          }
        } catch (error) {
          console.error('Failed to fetch stats:', error);
        }
      } catch (error) {
        console.error('Failed to fetch network data:', error);
      } finally {
        setLoading(false);
      }
    };

    fetchNetworkData();
  }, []);

  // Force-directed layout for entire network
  useEffect(() => {
    if (graphData.nodes.length === 0) return;

    const width = 1600;
    const height = 1000;
    const centerX = width / 2;
    const centerY = height / 2;

    // Initialize positions
    const initialPositions = {};
    graphData.nodes.forEach((node, idx) => {
      const angle = (2 * Math.PI * idx) / graphData.nodes.length;
      const radius = Math.min(width, height) * 0.4;
      initialPositions[node.id] = {
        x: centerX + radius * Math.cos(angle),
        y: centerY + radius * Math.sin(angle),
        vx: 0,
        vy: 0
      };
    });

    setNodePositions(initialPositions);

    // Force simulation
    const repulsionStrength = 5000;
    const attractionStrength = 0.0008;
    const damping = 0.88;
    const iterations = 400;

    let currentPositions = { ...initialPositions };
    let iteration = 0;

    const simulate = () => {
      if (iteration >= iterations) {
        cancelAnimationFrame(animationRef.current);
        return;
      }

      graphData.nodes.forEach((node1) => {
        let fx = 0, fy = 0;

        // Repulsion
        graphData.nodes.forEach((node2) => {
          if (node1.id === node2.id) return;

          const dx = currentPositions[node1.id].x - currentPositions[node2.id].x;
          const dy = currentPositions[node1.id].y - currentPositions[node2.id].y;
          const distance = Math.sqrt(dx * dx + dy * dy) || 1;
          
          if (distance < 250) {
            const force = repulsionStrength / (distance * distance);
            fx += (dx / distance) * force;
            fy += (dy / distance) * force;
          }
        });

        // Attraction
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

        // Center gravity
        const dcx = centerX - currentPositions[node1.id].x;
        const dcy = centerY - currentPositions[node1.id].y;
        fx += dcx * 0.00008;
        fy += dcy * 0.00008;

        currentPositions[node1.id].vx = (currentPositions[node1.id].vx + fx) * damping;
        currentPositions[node1.id].vy = (currentPositions[node1.id].vy + fy) * damping;
      });

      graphData.nodes.forEach((node) => {
        currentPositions[node.id].x += currentPositions[node.id].vx;
        currentPositions[node.id].y += currentPositions[node.id].vy;

        currentPositions[node.id].x = Math.max(80, Math.min(width - 80, currentPositions[node.id].x));
        currentPositions[node.id].y = Math.max(80, Math.min(height - 80, currentPositions[node.id].y));
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

  const getNodePosition = (nodeId) => {
    return nodePositions[nodeId] || { x: 800, y: 500 };
  };

  const getNodeSize = (degree) => {
    return Math.max(8, Math.min(30, 8 + degree * 2));
  };

  const getNodeColor = (degree) => {
    if (degree === 0) return '#6b7280';
    if (degree <= 2) return '#10b981';
    if (degree <= 5) return '#3b82f6';
    if (degree <= 10) return '#8b5cf6';
    return '#ef4444';
  };

  if (loading) {
    return (
      <div className="network-overview">
        <div className="overview-loading">
          <div className="loading-spinner-large"></div>
          <p>Loading entire network...</p>
          <p className="loading-subtext">This may take a moment</p>
        </div>
      </div>
    );
  }

  return (
    <div className="network-overview">
      <div className="overview-header">
        <div className="overview-title-section">
          <h1 className="overview-title">🌐 Complete Network Overview</h1>
          <p className="overview-subtitle">
            Visualizing all {graphData.nodes.length} users and {graphData.edges.length} connections
          </p>
        </div>
      </div>

      {/* Network Stats Dashboard */}
      {stats && (
        <div className="overview-stats-grid">
          <div className="overview-stat-card">
            <div className="stat-icon">👥</div>
            <div className="stat-content">
              <div className="stat-number">{stats.nodes || graphData.nodes.length}</div>
              <div className="stat-label">Total Users</div>
            </div>
          </div>

          <div className="overview-stat-card">
            <div className="stat-icon">🔗</div>
            <div className="stat-content">
              <div className="stat-number">{stats.edges || graphData.edges.length}</div>
              <div className="stat-label">Connections</div>
            </div>
          </div>

          <div className="overview-stat-card">
            <div className="stat-icon">🎯</div>
            <div className="stat-content">
              <div className="stat-number">{stats.components || 'N/A'}</div>
              <div className="stat-label">Communities</div>
            </div>
          </div>

          <div className="overview-stat-card">
            <div className="stat-icon">📊</div>
            <div className="stat-content">
              <div className="stat-number">{stats.averageDegree?.toFixed(1) || 'N/A'}</div>
              <div className="stat-label">Avg Connections</div>
            </div>
          </div>

          <div className="overview-stat-card">
            <div className="stat-icon">💫</div>
            <div className="stat-content">
              <div className="stat-number">{((stats.density || 0) * 100).toFixed(2)}%</div>
              <div className="stat-label">Network Density</div>
            </div>
          </div>

          <div className="overview-stat-card">
            <div className="stat-content">
              <div className="stat-number">{stats.isConnected ? 'Yes' : 'No'}</div>
              <div className="stat-label">Fully Connected</div>
            </div>
          </div>
        </div>
      )}

      {/* Main Network Visualization */}
      <div className="overview-canvas-container">
        <svg className="overview-svg" viewBox="0 0 1600 1000" preserveAspectRatio="xMidYMid meet">
          <defs>
            <radialGradient id="nodeGradient" cx="50%" cy="50%" r="50%">
              <stop offset="0%" style={{ stopColor: 'rgba(255, 255, 255, 0.3)', stopOpacity: 1 }} />
              <stop offset="100%" style={{ stopColor: 'rgba(255, 255, 255, 0)', stopOpacity: 1 }} />
            </radialGradient>
          </defs>

          {/* Edges */}
          <g className="overview-edges-layer" opacity="0.15">
            {graphData.edges.map((edge, idx) => {
              const sourcePos = getNodePosition(edge.source);
              const targetPos = getNodePosition(edge.target);
              const isHighlighted = hoveredNode === edge.source || hoveredNode === edge.target;

              return (
                <line
                  key={idx}
                  x1={sourcePos.x}
                  y1={sourcePos.y}
                  x2={targetPos.x}
                  y2={targetPos.y}
                  stroke={isHighlighted ? '#9d4edd' : '#4b5563'}
                  strokeWidth={isHighlighted ? 2 : 0.8}
                  opacity={isHighlighted ? 0.6 : 0.3}
                  strokeLinecap="round"
                />
              );
            })}
          </g>

          {/* Nodes */}
          <g className="overview-nodes-layer">
            {graphData.nodes.map((node) => {
              const pos = getNodePosition(node.id);
              const nodeSize = getNodeSize(node.degree);
              const nodeColor = getNodeColor(node.degree);
              const isHovered = hoveredNode === node.id;

              return (
                <g 
                  key={node.id}
                  onMouseEnter={() => setHoveredNode(node.id)}
                  onMouseLeave={() => setHoveredNode(null)}
                  style={{ cursor: 'pointer' }}
                >
                  {isHovered && (
                    <>
                      <circle
                        cx={pos.x}
                        cy={pos.y}
                        r={nodeSize + 10}
                        fill="none"
                        stroke={nodeColor}
                        strokeWidth={2}
                        opacity={0.4}
                      />
                      <text
                        x={pos.x}
                        y={pos.y - nodeSize - 15}
                        textAnchor="middle"
                        fill="white"
                        fontSize="12"
                        fontWeight="600"
                        style={{ 
                          textShadow: '0 0 4px rgba(0,0,0,0.8)',
                          pointerEvents: 'none'
                        }}
                      >
                        {node.label}
                      </text>
                      <text
                        x={pos.x}
                        y={pos.y - nodeSize - 3}
                        textAnchor="middle"
                        fill="rgba(255,255,255,0.7)"
                        fontSize="10"
                        style={{ 
                          textShadow: '0 0 4px rgba(0,0,0,0.8)',
                          pointerEvents: 'none'
                        }}
                      >
                        {node.degree} {node.degree === 1 ? 'connection' : 'connections'}
                      </text>
                    </>
                  )}
                  
                  <circle
                    cx={pos.x}
                    cy={pos.y}
                    r={isHovered ? nodeSize + 3 : nodeSize}
                    fill={nodeColor}
                    opacity={isHovered ? 1 : 0.85}
                  />
                  
                  {isHovered && (
                    <circle
                      cx={pos.x}
                      cy={pos.y}
                      r={isHovered ? nodeSize + 3 : nodeSize}
                      fill="url(#nodeGradient)"
                    />
                  )}
                </g>
              );
            })}
          </g>
        </svg>

        {/* Legend */}
        <div className="overview-legend">
          <h4 className="legend-title">Connection Levels</h4>
          <div className="legend-item">
            <div className="legend-dot" style={{ background: '#6b7280' }}></div>
            <span>Isolated (0)</span>
          </div>
          <div className="legend-item">
            <div className="legend-dot" style={{ background: '#10b981' }}></div>
            <span>1-2 connections</span>
          </div>
          <div className="legend-item">
            <div className="legend-dot" style={{ background: '#3b82f6' }}></div>
            <span>3-5 connections</span>
          </div>
          <div className="legend-item">
            <div className="legend-dot" style={{ background: '#8b5cf6' }}></div>
            <span>6-10 connections</span>
          </div>
          <div className="legend-item">
            <div className="legend-dot" style={{ background: '#ef4444' }}></div>
            <span>10+ connections (Hubs)</span>
          </div>
        </div>
      </div>
    </div>
  );
}
