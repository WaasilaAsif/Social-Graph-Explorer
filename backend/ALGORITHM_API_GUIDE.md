# Algorithm API Guide - SocialGraphExplorer

This guide documents the **10 advanced algorithm endpoints** that provide social network analysis, recommendations, and statistics.

---

## Table of Contents
1. [Mutual Friends](#1-mutual-friends)
2. [Shortest Path](#2-shortest-path)
3. [Users Within Distance](#3-users-within-distance)
4. [User Degree](#4-user-degree)
5. [Graph Statistics](#5-graph-statistics)
6. [Top Popular Users](#6-top-popular-users)
7. [User Rank](#7-user-rank)
8. [Friend Suggestions](#8-friend-suggestions)
9. [Two-Hop Friends](#9-two-hop-friends)
10. [Unit Tests](#10-unit-tests)

---

## Overview

All algorithm endpoints are accessible at: **`http://localhost:8081/api/algo/*`**

These endpoints implement advanced **graph algorithms** and **data structures** for social network analysis:

- **BFS/DFS Traversal**: Shortest paths, connected components
- **Max-Heap (PriorityQueue)**: Popularity ranking, top-K extraction
- **Hash-Set Operations**: Mutual friends, intersection algorithms
- **Network Metrics**: Density, clustering coefficient, diameter
- **Recommendation Algorithms**: 2-hop friends, mutual friends scoring

---

## 1. Mutual Friends

**Find common friends between two users**

### Endpoint
```
GET /api/algo/mutual-friends?user1={id}&user2={id}
```

### Algorithm
- **Data Structure**: Hash-set intersection
- **Time Complexity**: O(n + m) where n, m are friend counts
- **Space Complexity**: O(min(n, m))

### Use Cases
- Display "You and Alice have 12 friends in common"
- Social proof in friend suggestions
- Network overlap analysis
- Friend comparison features

### Example Request
```bash
curl "http://localhost:8081/api/algo/mutual-friends?user1=1&user2=5"
```

### Example Response
```json
{
  "user1": 1,
  "user2": 5,
  "mutualFriends": [2, 3, 7, 15, 23],
  "count": 5
}
```

### Integration Example
```javascript
// React component
const getMutualFriends = async (userId1, userId2) => {
  const response = await fetch(
    `http://localhost:8081/api/algo/mutual-friends?user1=${userId1}&user2=${userId2}`
  );
  const data = await response.json();
  return data.mutualFriends;
};
```

---

## 2. Shortest Path

**Find the shortest connection path between two users (degrees of separation)**

### Endpoint
```
GET /api/algo/shortest-path?start={id}&end={id}
```

### Algorithm
- **Data Structure**: BFS with parent tracking
- **Time Complexity**: O(V + E)
- **Space Complexity**: O(V)

### Use Cases
- "How do you know X?" feature
- Display connection path visualization
- Network distance calculation
- "You are connected through Alice → Bob → Charlie"

### Example Request
```bash
curl "http://localhost:8081/api/algo/shortest-path?start=1&end=50"
```

### Example Response
```json
{
  "start": 1,
  "end": 50,
  "path": [1, 3, 15, 42, 50],
  "distance": 4,
  "exists": true
}
```

### Visualization
```
User 1 → User 3 → User 15 → User 42 → User 50
   (friend)  (friend)   (friend)   (friend)
```

---

## 3. Users Within Distance

**Find all users within N hops from a given user**

### Endpoint
```
GET /api/algo/users-within-distance?userId={id}&distance={n}
```

### Algorithm
- **Data Structure**: BFS with distance tracking
- **Time Complexity**: O(V + E) bounded by distance
- **Space Complexity**: O(V)

### Use Cases
- "Discover 45 people 2 connections away"
- Expand social circle recommendations
- Network reach analysis
- Proximity-based features

### Example Request
```bash
curl "http://localhost:8081/api/algo/users-within-distance?userId=1&distance=2"
```

### Example Response
```json
{
  "userId": 1,
  "maxDistance": 2,
  "users": [2, 3, 5, 7, 10, 15, 18, 22, 25, 30],
  "count": 10
}
```

---

## 4. User Degree

**Get the friend count for a specific user**

### Endpoint
```
GET /api/algo/user-degree?userId={id}
```

### Algorithm
- **Data Structure**: Adjacency list size
- **Time Complexity**: O(1)
- **Space Complexity**: O(1)

### Use Cases
- Profile statistics display
- User metrics dashboard
- Engagement tracking
- "You have 42 connections"

### Example Request
```bash
curl "http://localhost:8081/api/algo/user-degree?userId=5"
```

### Example Response
```json
{
  "userId": 5,
  "degree": 42
}
```

---

## 5. Graph Statistics

**Complete network analysis and metrics**

### Endpoint
```
GET /api/algo/graph-stats
```

### Algorithm
- **Multiple Algorithms**:
  - Node/Edge counting: O(V + E)
  - Density calculation: O(1)
  - Clustering coefficient: O(V × d²) where d = avg degree
  - Diameter: O(V × (V + E)) using BFS from all nodes
  - Connected components: O(V + E) using DFS

### Metrics Returned
- **nodeCount**: Total users in network
- **edgeCount**: Total friendships
- **averageDegree**: Average friends per user
- **density**: Network connectivity (0 to 1)
- **connected**: Is network fully connected?
- **components**: Number of disconnected groups
- **diameter**: Maximum shortest path length
- **averageClusteringCoefficient**: Network clustering (0 to 1)
- **mostConnectedNode**: User ID with highest degree

### Use Cases
- Admin dashboard analytics
- Network health monitoring
- Engagement metrics tracking
- Research and insights
- Growth analysis

### Example Request
```bash
curl "http://localhost:8081/api/algo/graph-stats"
```

### Example Response
```json
{
  "nodeCount": 320,
  "edgeCount": 61,
  "averageDegree": 2.1,
  "density": 0.0012,
  "connected": false,
  "components": 15,
  "diameter": 8,
  "averageClusteringCoefficient": 0.23,
  "mostConnectedNode": 5
}
```

---

## 6. Top Popular Users

**Get the most connected users (influencers) using max-heap**

### Endpoint
```
GET /api/algo/top-popular?n={count}
```

### Algorithm
- **Data Structure**: Max-Heap (PriorityQueue)
- **Ranking Metric**: Degree centrality
- **Time Complexity**: O(V log V)
- **Space Complexity**: O(V)

### Use Cases
- Influencer leaderboards
- "Top users" feature
- Trending users dashboard
- Social proof and credibility
- Gamification elements

### Example Request
```bash
curl "http://localhost:8081/api/algo/top-popular?n=5"
```

### Example Response
```json
{
  "topUsers": [
    {"userId": 5, "score": 45},
    {"userId": 12, "score": 38},
    {"userId": 23, "score": 35},
    {"userId": 7, "score": 32},
    {"userId": 18, "score": 30}
  ],
  "count": 5
}
```

---

## 7. User Rank

**Get popularity ranking and percentile for a specific user**

### Endpoint
```
GET /api/algo/user-rank?userId={id}
```

### Algorithm
- **Data Structure**: Sorted ranking with binary search
- **Time Complexity**: O(V log V) for sorting
- **Space Complexity**: O(V)

### Use Cases
- "You're in the top 10% most connected users"
- Gamification and achievements
- User engagement metrics
- Profile badges and status

### Example Request
```bash
curl "http://localhost:8081/api/algo/user-rank?userId=5"
```

### Example Response
```json
{
  "userId": 5,
  "rank": 1,
  "score": 45,
  "percentile": 99.7
}
```

**Interpretation**: User 5 is rank #1 with 45 friends, more connected than 99.7% of users.

---

## 8. Friend Suggestions

**AI-powered "People you may know" recommendations**

### Endpoint
```
GET /api/algo/friend-suggestions?userId={id}&limit={n}
```

### Algorithm
- **Data Structure**: 2-hop BFS + mutual friends counting
- **Scoring Formula**: 
  - Primary: Mutual friends count
  - Secondary: Interaction frequency (if available)
- **Time Complexity**: O(d² × V) where d = avg degree
- **Space Complexity**: O(V)

### Recommendation Logic
1. Find all friends of friends (2-hop)
2. Exclude current friends and self
3. Count mutual friends for each candidate
4. Score by frequency of appearance
5. Sort by score and return top N

### Use Cases
- "People you may know" feature
- Smart friend recommendations
- Network expansion
- User engagement and growth

### Example Request
```bash
curl "http://localhost:8081/api/algo/friend-suggestions?userId=1&limit=10"
```

### Example Response
```json
{
  "userId": 1,
  "suggestions": [
    {
      "userId": 42,
      "mutualFriends": 8,
      "frequencyScore": 12
    },
    {
      "userId": 15,
      "mutualFriends": 6,
      "frequencyScore": 9
    },
    {
      "userId": 27,
      "mutualFriends": 5,
      "frequencyScore": 7
    }
  ],
  "count": 3
}
```

**Interpretation**: User 42 has 8 mutual friends and appeared 12 times across friend lists.

---

## 9. Two-Hop Friends

**Find friends of friends (second-degree connections)**

### Endpoint
```
GET /api/algo/two-hop-friends?userId={id}
```

### Algorithm
- **Data Structure**: BFS 2-level traversal
- **Time Complexity**: O(d²) where d = avg degree
- **Space Complexity**: O(V)

### Use Cases
- Expand social circle
- Network visualization
- Connection suggestions
- "Discover new people"

### Example Request
```bash
curl "http://localhost:8081/api/algo/two-hop-friends?userId=1"
```

### Example Response
```json
{
  "userId": 1,
  "twoHopFriends": [15, 18, 22, 25, 30, 42, 55, 67, 89],
  "count": 9
}
```

---

## 10. Unit Tests

**Automated test suite for all algorithm modules**

### Endpoint
```
GET /api/algo/unit-tests
```

### Tests Included
1. **PriorityQueue (Max-Heap)**: Insert/extract operations
2. **MutualFriends**: Count consistency and logic validation
3. **ShortestPath**: Path/distance consistency, BFS correctness
4. **GraphStats**: Metric validation (density, clustering, etc.)
5. **PopularityRanker**: Heap ordering and ranking accuracy
6. **FriendSuggestion**: 2-hop algorithm, no self/direct friends

### Use Cases
- Development validation
- CI/CD integration
- Regression testing
- Performance benchmarking

### Example Request
```bash
curl "http://localhost:8081/api/algo/unit-tests"
```

### Example Response
```json
{
  "component": "Member 3 - Algorithms & Analytics",
  "timestamp": 1733789456,
  "tester": "Member 3",
  "test1_priorityQueue": {
    "status": "[PASS]",
    "details": "Max-heap correctly returns elements in descending order"
  },
  "test2_mutualFriends": {
    "status": "[PASS]",
    "details": {
      "user1": 1,
      "user2": 5,
      "mutualCount": 3,
      "hasMutuals": true,
      "consistency": "Count matches list size"
    }
  },
  "summary": {
    "totalTests": 6,
    "passed": 6,
    "failed": 0,
    "skipped": 0,
    "passRate": 100.0,
    "overallStatus": "[PASS] ALL TESTS PASSED"
  }
}
```

---

## Performance Notes

### Optimization Strategies
- **Caching**: Popular queries (graph stats) can be cached
- **Indexing**: Pre-compute user degrees for O(1) lookups
- **Lazy Loading**: Load suggestions on-demand
- **Batch Processing**: Process multiple requests together

### Scalability Considerations
- Current implementation: Up to 1000 users with good performance
- For 10,000+ users: Consider distributed graph databases
- For real-time updates: Implement incremental algorithms

### Bottlenecks
- **Graph Stats**: Most expensive (O(V²) for diameter)
- **Friend Suggestions**: O(d² × V) can be slow for high-degree nodes
- **Shortest Path**: Generally fast with BFS

---

## Integration Examples

### Frontend React Component
```javascript
import { useState, useEffect } from 'react';

const AlgorithmDashboard = ({ userId }) => {
  const [stats, setStats] = useState(null);
  const [suggestions, setSuggestions] = useState([]);
  const [rank, setRank] = useState(null);

  useEffect(() => {
    // Get graph statistics
    fetch('http://localhost:8081/api/algo/graph-stats')
      .then(res => res.json())
      .then(setStats);

    // Get friend suggestions
    fetch(`http://localhost:8081/api/algo/friend-suggestions?userId=${userId}&limit=10`)
      .then(res => res.json())
      .then(data => setSuggestions(data.suggestions));

    // Get user rank
    fetch(`http://localhost:8081/api/algo/user-rank?userId=${userId}`)
      .then(res => res.json())
      .then(setRank);
  }, [userId]);

  return (
    <div>
      <h2>Network Statistics</h2>
      {stats && (
        <div>
          <p>Total Users: {stats.nodeCount}</p>
          <p>Network Density: {(stats.density * 100).toFixed(2)}%</p>
          <p>Your Rank: #{rank?.rank} (Top {(100 - rank?.percentile).toFixed(1)}%)</p>
        </div>
      )}

      <h2>Friend Suggestions</h2>
      <ul>
        {suggestions.map(s => (
          <li key={s.userId}>
            User {s.userId} - {s.mutualFriends} mutual friends
          </li>
        ))}
      </ul>
    </div>
  );
};
```

---

## Error Handling

All endpoints return consistent error responses:

```json
{
  "error": "Error message description"
}
```

Common error codes:
- **400**: Missing required parameters
- **404**: User not found
- **500**: Internal server error

---

## Testing Workflows

### 1. Basic Functionality Test
```bash
# Test all endpoints
curl http://localhost:8081/api/algo/graph-stats
curl "http://localhost:8081/api/algo/mutual-friends?user1=1&user2=5"
curl "http://localhost:8081/api/algo/friend-suggestions?userId=1&limit=5"
```

### 2. Performance Test
```bash
# Measure response times
time curl "http://localhost:8081/api/algo/shortest-path?start=1&end=100"
time curl "http://localhost:8081/api/algo/graph-stats"
```

### 3. Validation Test
```bash
# Run automated test suite
curl http://localhost:8081/api/algo/unit-tests | jq .
```

---

## Advanced Use Cases

### 1. Network Visualization
Combine multiple endpoints to create interactive graph visualization:
- Use `/graph-stats` for overview
- Use `/shortest-path` to highlight connections
- Use `/top-popular` to emphasize influencers
- Use `/two-hop-friends` for expansion animations

### 2. Social Proof System
Build trust indicators:
- Display mutual friends count
- Show connection path to trusted users
- Highlight popular/verified users
- Display network overlap metrics

### 3. Recommendation Engine
Multi-factor friend suggestions:
- Primary: Mutual friends (weight: 0.5)
- Secondary: Network proximity (weight: 0.3)
- Tertiary: User activity (weight: 0.2)

### 4. Analytics Dashboard
Admin monitoring panel:
- Real-time network health
- Growth trends over time
- User engagement metrics
- Influencer identification

---

## Future Enhancements

Planned algorithm additions:
- **Community Detection**: Louvain algorithm for group discovery
- **Centrality Measures**: Betweenness, closeness, eigenvector centrality
- **Link Prediction**: Machine learning-based friend suggestions
- **Influence Propagation**: Viral spread simulation
- **Graph Clustering**: k-means on graph embeddings

---

## Troubleshooting

### Issue: Slow graph-stats response
**Solution**: Stats are computationally expensive. Consider caching or computing asynchronously.

### Issue: Empty friend suggestions
**Cause**: User has no 2-hop friends or all are already friends.
**Solution**: Fall back to popular users or mutual interest-based suggestions.

### Issue: Incorrect shortest path
**Cause**: Graph may have disconnected components.
**Solution**: Check `pathExists` field in response.

---

## Conclusion

The algorithm API provides **10 powerful endpoints** for social network analysis, recommendations, and statistics. These endpoints leverage advanced **graph algorithms** and **data structures** to deliver:

[x]
 Fast recommendations (2-hop + mutual friends)  
[x]
 Network insights (density, clustering, diameter)  
[x]
 Popularity ranking (max-heap based)  
[x]
 Connection analysis (shortest paths, degrees)  
[x]
 Automated testing (comprehensive test suite)  

For questions or issues, refer to the main [README.md](../README.md) or [Overview.md](../Overview.md).
