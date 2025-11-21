export const dummyGraph = {
  nodes: [
    { id: 1, label: "Alice Chen", group: 1 },
    { id: 2, label: "Bob Martinez", group: 1 },
    { id: 3, label: "Carol Zhang", group: 2 },
    { id: 4, label: "David Kumar", group: 2 },
    { id: 5, label: "Emma Wilson", group: 1 },
    { id: 6, label: "Frank Thompson", group: 3 },
    { id: 7, label: "Grace Lee", group: 2 },
    { id: 8, label: "Henry Park", group: 3 },
    { id: 9, label: "Iris Rodriguez", group: 2 },
    { id: 10, label: "Jack Foster", group: 3 }
  ],
  edges: [
    { source: 1, target: 2, weight: 0.8 },
    { source: 1, target: 3, weight: 0.6 },
    { source: 1, target: 5, weight: 0.9 },
    { source: 2, target: 4, weight: 0.7 },
    { source: 2, target: 6, weight: 0.5 },
    { source: 2, target: 7, weight: 0.6 },
    { source: 3, target: 4, weight: 0.8 },
    { source: 3, target: 5, weight: 0.7 },
    { source: 3, target: 8, weight: 0.5 },
    { source: 4, target: 6, weight: 0.6 },
    { source: 4, target: 9, weight: 0.7 },
    { source: 5, target: 7, weight: 0.8 },
    { source: 5, target: 10, weight: 0.6 },
    { source: 6, target: 8, weight: 0.7 },
    { source: 7, target: 9, weight: 0.5 },
    { source: 8, target: 10, weight: 0.6 }
  ]
};

export const adjacencyList = {
  1: [2, 3, 5],
  2: [1, 4, 6, 7],
  3: [1, 4, 5, 8],
  4: [2, 3, 6, 9],
  5: [1, 3, 7, 10],
  6: [2, 4, 8],
  7: [2, 5, 9],
  8: [3, 6, 10],
  9: [4, 7],
  10: [5, 8]
};

export const getNodeConnections = (nodeId) => {
  return adjacencyList[nodeId] || [];
};

export const getShortestPath = (startId, endId) => {
  return [startId, endId];
};
