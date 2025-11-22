import { useState } from 'react';
import { dummyGraph } from '../data/dummyGraph';
import { getUserById } from '../data/dummyUsers';
import '../styles/GraphView.css';

export default function GraphView({ graphId, onNodeClick }) {
  const [selectedNode, setSelectedNode] = useState(null);

  const handleNodeClick = (nodeId) => {
    setSelectedNode(nodeId);
    const user = getUserById(nodeId);
    if (user && onNodeClick) {
      onNodeClick(user);
    }
  };

  return (
    <div className="graph-view">
      <div className="graph-header">
        <div>
          <h2 className="graph-title">
            {graphId === 'main' ? 'Main Network Graph' : 'Communities Graph'}
          </h2>
          <p className="text-sm" style={{ color: 'var(--text-secondary)', marginTop: '0.25rem' }}>
            {dummyGraph.nodes.length} nodes, {dummyGraph.edges.length} edges
          </p>
        </div>
      </div>

      <div className="graph-canvas">
        <svg className="graph-svg">
          {dummyGraph.edges.map((edge, idx) => {
            const sourceNode = dummyGraph.nodes.find(n => n.id === edge.source);
            const targetNode = dummyGraph.nodes.find(n => n.id === edge.target);
            const x1 = (sourceNode.id * 80) % 800 + 50;
            const y1 = Math.floor(sourceNode.id / 4) * 120 + 80;
            const x2 = (targetNode.id * 80) % 800 + 50;
            const y2 = Math.floor(targetNode.id / 4) * 120 + 80;

            return (
              <line
                key={idx}
                x1={x1}
                y1={y1}
                x2={x2}
                y2={y2}
                className="graph-edge"
                opacity={edge.weight}
              />
            );
          })}

          {dummyGraph.nodes.map((node) => {
            const x = (node.id * 80) % 800 + 50;
            const y = Math.floor(node.id / 4) * 120 + 80;
            const isSelected = selectedNode === node.id;

            return (
              <g 
                key={node.id} 
                onClick={() => handleNodeClick(node.id)} 
                className={`graph-node ${isSelected ? 'graph-node-selected' : ''}`}
              >
                <circle
                  cx={x}
                  cy={y}
                  r={isSelected ? 28 : 24}
                  fill={
                    node.group === 1
                      ? '#3b82f6'
                      : node.group === 2
                      ? '#8b5cf6'
                      : '#10b981'
                  }
                />
                <text
                  x={x}
                  y={y + 4}
                  className="graph-node-label"
                  style={{ fontWeight: '600' }}
                >
                  {node.id}
                </text>
                <text
                  x={x}
                  y={y + 45}
                  className="graph-node-label"
                  style={{ fill: '#9ca3af' }}
                >
                  {node.label.split(' ')[0]}
                </text>
              </g>
            );
          })}
        </svg>

        <div className="graph-stats">
          <p className="text-xs" style={{ color: 'var(--text-secondary)', marginBottom: '0.5rem' }}>Graph Stats</p>
          <div className="stat-item">
            <span className="stat-label">Group 1</span>
            <span className="stat-value" style={{ color: '#3b82f6' }}>●</span>
          </div>
          <div className="stat-item">
            <span className="stat-label">Group 2</span>
            <span className="stat-value" style={{ color: '#8b5cf6' }}>●</span>
          </div>
          <div className="stat-item">
            <span className="stat-label">Group 3</span>
            <span className="stat-value" style={{ color: '#10b981' }}>●</span>
          </div>
        </div>
      </div>
    </div>
  );
}
