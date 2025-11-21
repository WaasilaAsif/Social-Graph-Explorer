export const dummyPosts = [
  {
    id: 1,
    userId: 1,
    content: "Just implemented a fascinating breadth-first search algorithm for analyzing friend recommendation systems. The time complexity improvements are remarkable!",
    timestamp: "2024-01-20T10:30:00Z",
    likes: 42,
    comments: 8
  },
  {
    id: 2,
    userId: 2,
    content: "Working on centrality measures in social networks. Betweenness centrality reveals some interesting patterns about information flow.",
    timestamp: "2024-01-19T15:45:00Z",
    likes: 67,
    comments: 12
  },
  {
    id: 3,
    userId: 3,
    content: "Anyone else fascinated by the small-world phenomenon? Six degrees of separation is more than just a fun fact!",
    timestamp: "2024-01-19T09:20:00Z",
    likes: 89,
    comments: 23
  },
  {
    id: 4,
    userId: 1,
    content: "Exploring different graph traversal techniques today. DFS vs BFS - each has its perfect use case.",
    timestamp: "2024-01-18T14:15:00Z",
    likes: 34,
    comments: 5
  },
  {
    id: 5,
    userId: 4,
    content: "Published a new paper on community detection algorithms in large-scale social networks. Link in bio!",
    timestamp: "2024-01-18T11:00:00Z",
    likes: 156,
    comments: 34
  },
  {
    id: 6,
    userId: 5,
    content: "Graph coloring problems are everywhere once you start looking. Just solved an interesting scheduling problem using chromatic number optimization.",
    timestamp: "2024-01-17T16:30:00Z",
    likes: 78,
    comments: 15
  },
  {
    id: 7,
    userId: 2,
    content: "The PageRank algorithm is pure genius. Still amazed at how elegant the solution is for ranking network nodes.",
    timestamp: "2024-01-17T13:45:00Z",
    likes: 92,
    comments: 19
  },
  {
    id: 8,
    userId: 6,
    content: "Building a graph visualization tool with D3.js. Force-directed layouts are mesmerizing to watch!",
    timestamp: "2024-01-16T10:20:00Z",
    likes: 61,
    comments: 11
  },
  {
    id: 9,
    userId: 7,
    content: "Studying influence propagation models. It's fascinating how ideas spread through social networks like epidemics.",
    timestamp: "2024-01-16T08:15:00Z",
    likes: 103,
    comments: 27
  },
  {
    id: 10,
    userId: 3,
    content: "Minimum spanning trees aren't just for computer science classes - they're used in network design everywhere!",
    timestamp: "2024-01-15T17:40:00Z",
    likes: 45,
    comments: 7
  },
  {
    id: 11,
    userId: 8,
    content: "Optimizing graph database queries today. Neo4j's Cypher query language is incredibly expressive.",
    timestamp: "2024-01-15T14:25:00Z",
    likes: 54,
    comments: 9
  },
  {
    id: 12,
    userId: 4,
    content: "Triangle counting in large graphs is harder than it seems. Working on approximation algorithms for better performance.",
    timestamp: "2024-01-14T11:50:00Z",
    likes: 71,
    comments: 14
  },
  {
    id: 13,
    userId: 9,
    content: "Network effects are the key to understanding modern platform businesses. It's all about the graph structure!",
    timestamp: "2024-01-14T09:30:00Z",
    likes: 88,
    comments: 21
  },
  {
    id: 14,
    userId: 10,
    content: "Dijkstra's algorithm never gets old. Finding shortest paths in weighted graphs is fundamental to so many applications.",
    timestamp: "2024-01-13T15:15:00Z",
    likes: 39,
    comments: 6
  },
  {
    id: 15,
    userId: 5,
    content: "Graph isomorphism is one of those problems that seems simple but is incredibly complex. Still no polynomial-time algorithm!",
    timestamp: "2024-01-13T12:00:00Z",
    likes: 97,
    comments: 25
  }
];

export const getPostById = (id) => {
  return dummyPosts.find(post => post.id === id);
};

export const getPostsByUserId = (userId) => {
  return dummyPosts.filter(post => post.userId === userId);
};

export const getRecentPosts = (limit = 10) => {
  return [...dummyPosts]
    .sort((a, b) => new Date(b.timestamp) - new Date(a.timestamp))
    .slice(0, limit);
};
