// API service for backend communication
const API_BASE_URL = 'http://localhost:8081';

// User API endpoints
export const userAPI = {
  // Register a new user
  register: async (username: string, password: string) => {
    const response = await fetch(`${API_BASE_URL}/api/users/register`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password })
    });
    if (!response.ok) throw new Error('Failed to register user');
    return response.json();
  },

  // Login user
  login: async (username: string, password: string) => {
    const response = await fetch(`${API_BASE_URL}/api/users/login`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ username, password })
    });
    if (!response.ok) throw new Error('Failed to login');
    return response.json();
  },

  // Search users by prefix
  searchUsers: async (prefix: string) => {
    const response = await fetch(`${API_BASE_URL}/api/users/search?prefix=${encodeURIComponent(prefix)}`);
    if (!response.ok) throw new Error('Failed to search users');
    return response.json();
  },

  // Get user profile
  getUser: async (userId: number) => {
    const response = await fetch(`${API_BASE_URL}/api/users/${userId}`);
    if (!response.ok) throw new Error('Failed to get user');
    return response.json();
  },

  // Create post
  createPost: async (userId: number, content: string) => {
    const response = await fetch(`${API_BASE_URL}/api/users/${userId}/posts`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ content })
    });
    if (!response.ok) throw new Error('Failed to create post');
    return response.json();
  },

  // Get user posts
  getPosts: async (userId: number) => {
    const response = await fetch(`${API_BASE_URL}/api/users/${userId}/posts`);
    if (!response.ok) throw new Error('Failed to get posts');
    return response.json();
  }
};

// Graph API endpoints
export const graphAPI = {
  // Get all friends of a user
  getFriends: async (userId: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/friends/${userId}`);
    if (!response.ok) throw new Error('Failed to fetch friends');
    return response.json();
  },

  // Add friendship between two users
  addFriend: async (user1: number, user2: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/add-friend`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ user1, user2 })
    });
    if (!response.ok) throw new Error('Failed to add friend');
    return response.json();
  },

  // Remove friendship
  removeFriend: async (user1: number, user2: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/remove-friend/${user1}/${user2}`, {
      method: 'DELETE'
    });
    if (!response.ok) throw new Error('Failed to remove friend');
    return response.json();
  },

  // BFS traversal from a user
  bfs: async (startUserId: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/bfs/${startUserId}`);
    if (!response.ok) throw new Error('Failed to perform BFS');
    return response.json();
  },

  // DFS traversal from a user
  dfs: async (startUserId: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/dfs/${startUserId}`);
    if (!response.ok) throw new Error('Failed to perform DFS');
    return response.json();
  },

  // Find shortest path between two users
  shortestPath: async (srcUserId: number, destUserId: number) => {
    const response = await fetch(`${API_BASE_URL}/graph/shortest-path/${srcUserId}/${destUserId}`);
    if (!response.ok) throw new Error('Failed to find shortest path');
    return response.json();
  }
};

// Messaging API endpoints
export const messagingAPI = {
  // Send a new message
  sendMessage: async (senderId: number, receiverId: number, text: string) => {
    const response = await fetch(`${API_BASE_URL}/msg/send`, {
      method: 'POST',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify({ senderId, receiverId, text })
    });
    if (!response.ok) throw new Error('Failed to send message');
    return response.json();
  },

  // Search messages by exact word
  searchWord: async (word: string) => {
    const response = await fetch(`${API_BASE_URL}/msg/search/${encodeURIComponent(word)}`);
    if (!response.ok) throw new Error('Failed to search word');
    return response.json();
  },

  // Search messages by prefix
  searchPrefix: async (prefix: string) => {
    const response = await fetch(`${API_BASE_URL}/msg/prefix/${encodeURIComponent(prefix)}`);
    if (!response.ok) throw new Error('Failed to search prefix');
    return response.json();
  },

  // Get top K conversation partners
  getTopK: async (userId: number, k: number) => {
    const response = await fetch(`${API_BASE_URL}/msg/topk/${userId}/${k}`);
    if (!response.ok) throw new Error('Failed to get top K');
    return response.json();
  },

  // Get friend suggestions based on messages
  getSuggestions: async (userId: number, k: number) => {
    const response = await fetch(`${API_BASE_URL}/msg/suggestions/${userId}/${k}`);
    if (!response.ok) throw new Error('Failed to get suggestions');
    return response.json();
  },

  // Get mutual interactions
  getMutualInteractions: async (userId: number) => {
    const response = await fetch(`${API_BASE_URL}/msg/mutual/${userId}`);
    if (!response.ok) throw new Error('Failed to get mutual interactions');
    return response.json();
  },

  // Get popularity ranking
  getPopularityRank: async (top: number) => {
    const response = await fetch(`${API_BASE_URL}/msg/rank/${top}`);
    if (!response.ok) throw new Error('Failed to get popularity rank');
    return response.json();
  },

  // Find shortest messaging path
  getShortestPath: async (srcUserId: number, destUserId: number) => {
    const response = await fetch(`${API_BASE_URL}/msg/path/${srcUserId}/${destUserId}`);
    if (!response.ok) throw new Error('Failed to find shortest path');
    return response.json();
  }
};
