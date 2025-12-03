# Frontend API Integration - Quick Start Guide

## What's New

The frontend now has **full integration** with the backend C++ APIs! Two new interactive pages have been added:

### 1. Graph Explorer 🕸️
Test and visualize all graph operations directly from the UI.

### 2. Messaging Hub 💬
Send messages and explore messaging analytics with a user-friendly interface.

## How to Access

1. **Start the Backend Server:**
   ```bash
   cd backend
   ./server.exe
   ```
   Server should show: "Listening on: http://localhost:8081"

2. **Start the Frontend:**
   ```bash
   cd frontend
   npm run dev
   ```
   Frontend will open at: http://localhost:5173

3. **Navigate to API Tools:**
   - Look at the left sidebar
   - Find the "API Tools" section (with Activity icon)
   - Click to expand
   - Choose either "Graph Explorer" or "Messaging Hub"

## Graph Explorer Features

### Friends Management
- **Get Friends**: Enter a user ID (e.g., `1`) and get their friends list
- **Add Friend**: Enter two user IDs to create a friendship
- **Remove Friend**: Enter two user IDs to remove a friendship

### Graph Traversal
- **BFS**: Breadth-First Search starting from a user
- **DFS**: Depth-First Search starting from a user
- Shows the order nodes are visited

### Shortest Path
- Find the shortest connection between any two users
- Enter source and destination user IDs

## Messaging Hub Features

### Send Message
- Sender ID: Your user ID (default: 1)
- Receiver ID: Recipient's user ID
- Message: Type your message text
- Click "Send Message"
- Message is saved to the database automatically

### Search Messages
- **Exact Word**: Search for messages containing a specific word (e.g., "project")
- **Prefix Search**: Find messages with words starting with a prefix (e.g., "pro" finds "project", "progress", "problem")
- Returns message IDs matching your query

### Analytics
- **Top K Conversations**: Get user's most active chat partners
  - User ID: 1
  - K Value: 5
  - Shows top 5 people user 1 messages most
  
- **Friend Suggestions**: AI-powered friend recommendations based on messaging patterns
  - User ID: 1
  - K Value: 5
  - Shows 5 suggested friends
  
- **Mutual Interactions**: Find users who message each other through you
  - Shows triangular relationships in your network
  
- **Popularity Ranking**: See most active users by message count
  - Top N: 10
  - Shows top 10 most active users

### Message Path
- Find the shortest messaging chain between two users
- Similar to "Six Degrees of Separation"
- Source User: 1
- Destination User: 10
- Shows: [1, 5, 10] (user 1 → user 5 → user 10)

## Example Workflows

### Workflow 1: Explore User's Network
1. Open **Graph Explorer**
2. Click "Friends Management"
3. Enter User ID: `1`
4. Click "Get Friends List"
5. Result shows all of user 1's friends

### Workflow 2: Find Connection Path
1. Open **Graph Explorer**
2. Click "Shortest Path"
3. Source User: `1`
4. Destination User: `10`
5. Click "Find Shortest Path"
6. See the connection chain

### Workflow 3: Send and Search Messages
1. Open **Messaging Hub**
2. Click "Send Message"
3. Sender: `1`, Receiver: `3`
4. Message: `"Let's discuss the new feature implementation"`
5. Click "Send Message"
6. Switch to "Search Messages"
7. Search Query: `feature`
8. Click "Search Exact Word"
9. Your new message ID appears in results

### Workflow 4: Discover Popular Users
1. Open **Messaging Hub**
2. Click "Analytics"
3. Scroll to "Top N" input
4. Enter: `10`
5. Click "Get Popularity Ranking"
6. See top 10 most active users with message counts

## Tips for Testing

### Use Existing Data
The backend has pre-loaded data:
- 20 users (IDs: 1-20)
- 62 friendships
- 50+ messages

### Try These User IDs
- User 1: Most connected user
- User 5: Active messenger
- User 10: Good for path testing
- User 20: Less connected

### Try These Search Terms
- "project" - Multiple messages about projects
- "code" - Messages about coding
- "meeting" - Meeting coordination messages
- Prefix "pro" - Finds project, progress, problem, etc.

## Understanding Results

### Graph Results
```json
{
  "success": true,
  "userId": 1,
  "friends": [2, 3, 5, 7, 15, 19, 20]
}
```
- User 1 has 7 friends
- Friend IDs listed in array

### Message Search Results
```json
{
  "results": [1, 5, 12, 23, 34, 42]
}
```
- Message IDs where the search term was found
- Empty array [] means no matches

### Top K Results
```json
{
  "messages": [
    { "userId": 2, "weight": 8 },
    { "userId": 3, "weight": 6 }
  ]
}
```
- User 2: 8 message exchanges
- User 3: 6 message exchanges

### Path Results
```json
{
  "path": [1, 5, 10]
}
```
- Connection: User 1 → User 5 → User 10
- Empty [] means no path exists

## Troubleshooting

### "Failed to fetch" Error
**Problem**: Cannot connect to backend
**Solution**: 
1. Check backend is running: `./server.exe`
2. Verify it shows "Listening on: http://localhost:8081"
3. Refresh the frontend page

### Empty Results
**Problem**: Search returns no results
**Solution**:
1. Check spelling (searches are case-sensitive)
2. Try prefix search instead of exact word
3. Try a common word like "the" or "and"

### Invalid User ID
**Problem**: "User not found" or empty response
**Solution**:
1. Use user IDs between 1-20
2. Check the user exists in database

### CORS Error
**Problem**: CORS policy blocking requests
**Solution**:
1. Backend automatically includes CORS headers
2. If issue persists, restart both backend and frontend
3. Clear browser cache

## What's Next?

Now that the APIs are integrated, you can:
1. **Extend the UI**: Add visualizations for graph traversals
2. **Add Message Display**: Show actual message text, not just IDs
3. **User Profiles**: Display user details in results
4. **Real-time Updates**: Add WebSocket support for live messages
5. **Analytics Dashboard**: Create charts for messaging statistics

## Need Help?

Check these files:
- Backend API Documentation: `backend/MESSAGING_API_GUIDE.md`
- Frontend Code: `frontend/src/pages/GraphExplorer.jsx` and `MessagingHub.jsx`
- API Service: `frontend/src/services/api.ts`

Enjoy exploring your social graph! 🚀
