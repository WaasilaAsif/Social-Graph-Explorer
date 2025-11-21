import { useState } from 'react';
import { dummyGraph } from '../data/dummyGraph';
import { getUserById } from '../data/dummyUsers';

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
    <div className="h-full flex flex-col">
      <div className="p-4 border-b border-[#2b2b2b]">
        <h2 className="text-xl font-semibold text-gray-200">
          {graphId === 'main' ? 'Main Network Graph' : 'Communities Graph'}
        </h2>
        <p className="text-sm text-gray-400 mt-1">
          {dummyGraph.nodes.length} nodes, {dummyGraph.edges.length} edges
        </p>
      </div>

      <div className="flex-1 p-6 overflow-auto">
        <div className="relative w-full h-full min-h-[600px] bg-[#252525] rounded-lg border border-[#2b2b2b]">
          <svg className="w-full h-full">
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
                  stroke="#3a3a3a"
                  strokeWidth="2"
                  opacity={edge.weight}
                />
              );
            })}

            {dummyGraph.nodes.map((node) => {
              const x = (node.id * 80) % 800 + 50;
              const y = Math.floor(node.id / 4) * 120 + 80;
              const isSelected = selectedNode === node.id;

              return (
                <g key={node.id} onClick={() => handleNodeClick(node.id)} className="cursor-pointer">
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
                    stroke={isSelected ? '#60a5fa' : 'transparent'}
                    strokeWidth={isSelected ? 3 : 0}
                    className="transition-all"
                  />
                  <text
                    x={x}
                    y={y + 4}
                    textAnchor="middle"
                    fill="white"
                    fontSize="12"
                    fontWeight="600"
                  >
                    {node.id}
                  </text>
                  <text
                    x={x}
                    y={y + 45}
                    textAnchor="middle"
                    fill="#9ca3af"
                    fontSize="11"
                  >
                    {node.label.split(' ')[0]}
                  </text>
                </g>
              );
            })}
          </svg>

          <div className="absolute top-4 right-4 bg-[#1e1e1e] border border-[#2b2b2b] rounded-lg p-3">
            <p className="text-xs text-gray-400 mb-2">Graph Stats</p>
            <div className="space-y-1">
              <div className="flex items-center gap-2 text-xs">
                <div className="w-3 h-3 rounded-full bg-blue-500"></div>
                <span className="text-gray-300">Group 1</span>
              </div>
              <div className="flex items-center gap-2 text-xs">
                <div className="w-3 h-3 rounded-full bg-purple-500"></div>
                <span className="text-gray-300">Group 2</span>
              </div>
              <div className="flex items-center gap-2 text-xs">
                <div className="w-3 h-3 rounded-full bg-emerald-500"></div>
                <span className="text-gray-300">Group 3</span>
              </div>
            </div>
          </div>
        </div>
      </div>
    </div>
  );
}
