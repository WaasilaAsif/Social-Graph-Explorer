import { useState, useEffect } from 'react';
import { userAPI, graphAPI, algoAPI, messagingAPI } from '../services/api';
import { 
  Users, TrendingUp, MessageSquare, Target, 
  UserPlus, Activity, Award, Network 
} from 'lucide-react';
import '../styles/Dashboard.css';

interface DashboardProps {
  userId: number;
  username: string;
  onOpenTab?: (type: string, data: any) => void;
}

interface UserProfile {
  id: number;
  username: string;
  posts: string[];
}

interface GraphStats {
  totalNodes: number;
  totalEdges: number;
  avgDegree: number;
  components: number;
}

export default function Dashboard({ userId, username, onOpenTab }: DashboardProps) {
  const [loading, setLoading] = useState(true);
  const [profile, setProfile] = useState<UserProfile | null>(null);
  const [friends, setFriends] = useState<any[]>([]);
  const [friendCount, setFriendCount] = useState(0);
  const [userRank, setUserRank] = useState<number | null>(null);
  const [graphStats, setGraphStats] = useState<GraphStats | null>(null);
  const [topPopular, setTopPopular] = useState<any[]>([]);
  const [friendSuggestions, setFriendSuggestions] = useState<any[]>([]);
  const [twoHopFriends, setTwoHopFriends] = useState<any[]>([]);
  const [posts, setPosts] = useState<string[]>([]);
  const [newPost, setNewPost] = useState('');
  const [topConversations, setTopConversations] = useState<any[]>([]);
  const [messagingSuggestions, setMessagingSuggestions] = useState<any[]>([]);

  useEffect(() => {
    loadDashboardData();
  }, [userId]);

  const loadDashboardData = async () => {
    setLoading(true);
    try {
      // Fetch all data in parallel for better performance
      const [
        profileData,
        friendsData,
        degreeData,
        rankData,
        statsData,
        popularData,
        suggestionsData,
        twoHopData,
        postsData,
        topKData,
        msgSuggestionsData
      ] = await Promise.allSettled([
        userAPI.getUser(userId),
        graphAPI.getFriends(userId),
        algoAPI.getUserDegree(userId),
        algoAPI.getUserRank(userId),
        algoAPI.getGraphStats(),
        algoAPI.getTopPopular(10),
        algoAPI.getFriendSuggestions(userId, 10),
        algoAPI.getTwoHopFriends(userId),
        userAPI.getPosts(userId),
        messagingAPI.getTopK(userId, 5),
        messagingAPI.getSuggestions(userId, 5)
      ]);

      if (profileData.status === 'fulfilled') setProfile(profileData.value);
      if (friendsData.status === 'fulfilled') setFriends(friendsData.value.friends || []);
      if (degreeData.status === 'fulfilled') setFriendCount(degreeData.value.degree || 0);
      if (rankData.status === 'fulfilled') setUserRank(rankData.value.rank);
      if (statsData.status === 'fulfilled') setGraphStats(statsData.value);
      if (popularData.status === 'fulfilled') setTopPopular(popularData.value.users || []);
      if (suggestionsData.status === 'fulfilled') setFriendSuggestions(suggestionsData.value.suggestions || []);
      if (twoHopData.status === 'fulfilled') setTwoHopFriends(twoHopData.value.twoHopFriends || []);
      if (postsData.status === 'fulfilled') setPosts(postsData.value.posts || []);
      if (topKData.status === 'fulfilled') setTopConversations(topKData.value.conversations || []);
      if (msgSuggestionsData.status === 'fulfilled') setMessagingSuggestions(msgSuggestionsData.value.suggestions || []);

    } catch (error) {
      console.error('Error loading dashboard data:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleCreatePost = async () => {
    if (!newPost.trim()) return;
    
    try {
      await userAPI.createPost(userId, newPost);
      setNewPost('');
      // Reload posts
      const postsData = await userAPI.getPosts(userId);
      setPosts(postsData.posts || []);
    } catch (error) {
      console.error('Error creating post:', error);
      alert('Failed to create post');
    }
  };

  const handleDeletePost = async (postIndex: number) => {
    try {
      await userAPI.deletePost(userId, postIndex);
      // Reload posts
      const postsData = await userAPI.getPosts(userId);
      setPosts(postsData.posts || []);
    } catch (error) {
      console.error('Error deleting post:', error);
      alert('Failed to delete post');
    }
  };

  const handleAddFriend = async (friendId: number) => {
    try {
      await graphAPI.addFriend(userId, friendId);
      // Reload dashboard data
      loadDashboardData();
    } catch (error) {
      console.error('Error adding friend:', error);
      alert('Failed to add friend');
    }
  };

  if (loading) {
    return (
      <div className="dashboard-loading">
        <div className="loading-spinner"></div>
        <p>Loading your dashboard...</p>
      </div>
    );
  }

  return (
    <div className="dashboard">
      {/* Header Section */}
      <div className="dashboard-header">
        <div className="user-welcome">
          <h1>Welcome back, {username}!</h1>
          <p>Here's what's happening in your network</p>
        </div>
      </div>

      {/* Stats Grid */}
      <div className="stats-grid">
        <div className="stat-card">
          <div className="stat-icon">
            <Users size={24} />
          </div>
          <div className="stat-content">
            <h3>Friends</h3>
            <p className="stat-value">{friendCount}</p>
            <span className="stat-label">Connections</span>
          </div>
        </div>

        <div className="stat-card">
          <div className="stat-icon">
            <Award size={24} />
          </div>
          <div className="stat-content">
            <h3>Rank</h3>
            <p className="stat-value">#{userRank || 'N/A'}</p>
            <span className="stat-label">Popularity</span>
          </div>
        </div>

        <div className="stat-card">
          <div className="stat-icon">
            <MessageSquare size={24} />
          </div>
          <div className="stat-content">
            <h3>Posts</h3>
            <p className="stat-value">{posts.length}</p>
            <span className="stat-label">Your posts</span>
          </div>
        </div>

        <div className="stat-card">
          <div className="stat-icon">
            <Network size={24} />
          </div>
          <div className="stat-content">
            <h3>Network</h3>
            <p className="stat-value">{graphStats?.totalNodes || 0}</p>
            <span className="stat-label">Total users</span>
          </div>
        </div>
      </div>

      {/* Main Content Grid */}
      <div className="dashboard-grid">
        {/* My Connections */}
        <div className="dashboard-card">
          <div className="card-header">
            <Users size={20} />
            <h2>My Connections</h2>
          </div>
          <div className="card-content">
            {friends.length === 0 ? (
              <p className="empty-state">No friends yet. Start connecting!</p>
            ) : (
              <div className="friends-list">
                {friends.slice(0, 8).map((friend) => (
                  <div key={friend.id} className="friend-item" onClick={() => onOpenTab?.('user', { userId: friend.id })}>
                    <div className="friend-avatar">{friend.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <span className="friend-name">{friend.username || `User ${friend.id}`}</span>
                  </div>
                ))}
                {friends.length > 8 && (
                  <div className="friend-item view-all">
                    <span>+{friends.length - 8} more</span>
                  </div>
                )}
              </div>
            )}
          </div>
        </div>

        {/* Friend Suggestions */}
        <div className="dashboard-card">
          <div className="card-header">
            <UserPlus size={20} />
            <h2>Friend Suggestions</h2>
          </div>
          <div className="card-content">
            {friendSuggestions.length === 0 ? (
              <p className="empty-state">No suggestions available</p>
            ) : (
              <div className="suggestions-list">
                {friendSuggestions.slice(0, 5).map((suggestion) => (
                  <div key={suggestion.userId} className="suggestion-item">
                    <div className="suggestion-info">
                      <div className="friend-avatar">{suggestion.username?.charAt(0).toUpperCase() || 'U'}</div>
                      <div className="suggestion-details">
                        <span className="suggestion-name">{suggestion.username || `User ${suggestion.userId}`}</span>
                        <span className="suggestion-reason">{suggestion.mutualFriends || 0} mutual friends</span>
                      </div>
                    </div>
                    <button 
                      className="btn-add-friend"
                      onClick={() => handleAddFriend(suggestion.userId)}
                    >
                      Add
                    </button>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>

        {/* My Posts */}
        <div className="dashboard-card posts-card">
          <div className="card-header">
            <MessageSquare size={20} />
            <h2>My Posts</h2>
          </div>
          <div className="card-content">
            <div className="create-post">
              <textarea
                value={newPost}
                onChange={(e) => setNewPost(e.target.value)}
                placeholder="What's on your mind?"
                rows={3}
              />
              <button 
                className="btn-post"
                onClick={handleCreatePost}
                disabled={!newPost.trim()}
              >
                Post
              </button>
            </div>
            <div className="posts-list">
              {posts.length === 0 ? (
                <p className="empty-state">No posts yet. Share your thoughts!</p>
              ) : (
                posts.map((post, index) => (
                  <div key={index} className="post-item">
                    <p className="post-content">{typeof post === 'string' ? post : post.content || post}</p>
                    <div className="post-actions">
                      <span className="post-time">Just now</span>
                      <button 
                        className="btn-delete-post"
                        onClick={() => handleDeletePost(index)}
                      >
                        Delete
                      </button>
                    </div>
                  </div>
                ))
              )}
            </div>
          </div>
        </div>

        {/* Top Popular Users */}
        <div className="dashboard-card">
          <div className="card-header">
            <TrendingUp size={20} />
            <h2>Top Popular Users</h2>
          </div>
          <div className="card-content">
            {topPopular.length === 0 ? (
              <p className="empty-state">No data available</p>
            ) : (
              <div className="leaderboard">
                {topPopular.slice(0, 10).map((user, index) => (
                  <div key={user.userId} className="leaderboard-item" onClick={() => onOpenTab?.('user', { userId: user.userId })}>
                    <span className="rank">#{index + 1}</span>
                    <div className="friend-avatar">{user.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <span className="leaderboard-name">{user.username || `User ${user.userId}`}</span>
                    <span className="leaderboard-score">{user.degree || 0} friends</span>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>

        {/* Network Insights */}
        <div className="dashboard-card">
          <div className="card-header">
            <Activity size={20} />
            <h2>Network Insights</h2>
          </div>
          <div className="card-content">
            <div className="insights-grid">
              <div className="insight-item">
                <span className="insight-label">Total Users</span>
                <span className="insight-value">{graphStats?.totalNodes || 0}</span>
              </div>
              <div className="insight-item">
                <span className="insight-label">Total Connections</span>
                <span className="insight-value">{graphStats?.totalEdges || 0}</span>
              </div>
              <div className="insight-item">
                <span className="insight-label">Avg. Connections</span>
                <span className="insight-value">{graphStats?.avgDegree?.toFixed(1) || 0}</span>
              </div>
              <div className="insight-item">
                <span className="insight-label">Network Components</span>
                <span className="insight-value">{graphStats?.components || 0}</span>
              </div>
            </div>
            {twoHopFriends.length > 0 && (
              <div className="insight-extra">
                <p><strong>Extended Network:</strong> {twoHopFriends.length} friends of friends</p>
              </div>
            )}
          </div>
        </div>

        {/* Messaging Activity */}
        <div className="dashboard-card">
          <div className="card-header">
            <Target size={20} />
            <h2>Messaging Activity</h2>
          </div>
          <div className="card-content">
            {topConversations.length === 0 ? (
              <p className="empty-state">No messaging activity yet</p>
            ) : (
              <div className="messaging-list">
                <h4>Top Conversations</h4>
                {topConversations.map((conv, index) => (
                  <div key={index} className="messaging-item">
                    <div className="friend-avatar">{conv.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <div className="messaging-info">
                      <span className="messaging-name">{conv.username || `User ${conv.userId}`}</span>
                      <span className="messaging-count">{conv.count || 0} messages</span>
                    </div>
                  </div>
                ))}
              </div>
            )}
            {messagingSuggestions.length > 0 && (
              <div className="messaging-suggestions">
                <h4>Suggested Contacts</h4>
                {messagingSuggestions.slice(0, 3).map((suggestion, index) => (
                  <div key={index} className="messaging-item">
                    <div className="friend-avatar">{suggestion.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <span className="messaging-name">{suggestion.username || `User ${suggestion.userId}`}</span>
                  </div>
                ))}
              </div>
            )}
          </div>
        </div>
      </div>
    </div>
  );
}
