import { useState, useEffect, useRef } from 'react';
import { userAPI, graphAPI, algoAPI, messagingAPI } from '../services/api';
import { 
  Users, TrendingUp, MessageSquare, Target, 
  UserPlus, Activity, Award, Network, MoreVertical, UserMinus 
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
  nodeCount: number;
  edgeCount: number;
  averageDegree: number;
  components: number;
  density: number;
  connected: boolean;
  diameter: number;
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
  const [openMenuId, setOpenMenuId] = useState<number | null>(null);
  const [toast, setToast] = useState<{ message: string; type: 'success' | 'error' } | null>(null);
  const menuRef = useRef<HTMLDivElement>(null);

  // Close dropdown when clicking outside
  useEffect(() => {
    const handleClickOutside = (event: MouseEvent) => {
      if (menuRef.current && !menuRef.current.contains(event.target as Node)) {
        setOpenMenuId(null);
      }
    };
    document.addEventListener('mousedown', handleClickOutside);
    return () => document.removeEventListener('mousedown', handleClickOutside);
  }, []);

  // Auto-hide toast after 3 seconds
  useEffect(() => {
    if (toast) {
      const timer = setTimeout(() => setToast(null), 3000);
      return () => clearTimeout(timer);
    }
  }, [toast]);

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
      
      // Handle friends - fetch usernames for each friend
      if (friendsData.status === 'fulfilled' && friendsData.value.friends) {
        const friendsWithDetails = await Promise.all(
          friendsData.value.friends.map(async (friend: any) => {
            try {
              const userDetails = await userAPI.getUser(friend.id);
              return {
                id: friend.id,
                username: userDetails.user?.username || userDetails.username || `User ${friend.id}`
              };
            } catch (error) {
              return {
                id: friend.id,
                username: `User ${friend.id}`
              };
            }
          })
        );
        setFriends(friendsWithDetails);
      }
      
      if (degreeData.status === 'fulfilled') setFriendCount(degreeData.value.degree || 0);
      if (rankData.status === 'fulfilled') setUserRank(rankData.value.rank);
      if (statsData.status === 'fulfilled') setGraphStats(statsData.value);
      
      // Handle top popular users - fetch usernames for each user
      if (popularData.status === 'fulfilled' && popularData.value.topUsers) {
        const topUsersWithDetails = await Promise.all(
          popularData.value.topUsers.map(async (user: any) => {
            try {
              const userDetails = await userAPI.getUser(user.userId);
              return {
                userId: user.userId,
                username: userDetails.user?.username || userDetails.username || `User ${user.userId}`,
                score: user.score
              };
            } catch (error) {
              return {
                userId: user.userId,
                username: `User ${user.userId}`,
                score: user.score
              };
            }
          })
        );
        setTopPopular(topUsersWithDetails);
      }
      
      // Handle friend suggestions - fetch usernames for each suggestion
      if (suggestionsData.status === 'fulfilled' && suggestionsData.value.suggestions) {
        const suggestionsWithDetails = await Promise.all(
          suggestionsData.value.suggestions.map(async (suggestion: any) => {
            try {
              const userDetails = await userAPI.getUser(suggestion.userId);
              return {
                userId: suggestion.userId,
                username: userDetails.user?.username || userDetails.username || `User ${suggestion.userId}`,
                mutualFriends: suggestion.mutualFriends || 0
              };
            } catch (error) {
              return {
                userId: suggestion.userId,
                username: `User ${suggestion.userId}`,
                mutualFriends: suggestion.mutualFriends || 0
              };
            }
          })
        );
        setFriendSuggestions(suggestionsWithDetails);
      }
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

  const handleRemoveFriend = async (friendId: number, e: React.MouseEvent) => {
    e.stopPropagation(); // Prevent opening user profile
    setOpenMenuId(null);
    
    try {
      await graphAPI.removeFriend(userId, friendId);
      // Visually remove the friend from the list immediately
      setFriends(prev => prev.filter(f => f.id !== friendId));
      setFriendCount(prev => Math.max(0, prev - 1));
      setToast({ message: 'Friend removed successfully.', type: 'success' });
    } catch (error) {
      console.error('Error removing friend:', error);
      setToast({ message: 'Unable to remove friend. Please try again.', type: 'error' });
    }
  };

  const toggleMenu = (friendId: number, e: React.MouseEvent) => {
    e.stopPropagation(); // Prevent opening user profile
    setOpenMenuId(openMenuId === friendId ? null : friendId);
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

        {/* <div className="stat-card">
          <div className="stat-icon">
            <Network size={24} />
          </div>
          <div className="stat-content">
            <h3>Network</h3>
            <p className="stat-value">{graphStats?.totalNodes || 0}</p>
            <span className="stat-label">Total users</span>
          </div>
        </div> */}
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
              <div className="friends-list" ref={menuRef}>
                {friends.slice(0, 8).map((friend) => (
                  <div key={friend.id} className="friend-item" onClick={() => onOpenTab?.('user', { user: { id: friend.id, name: friend.username || `User ${friend.id}` } })}>
                    <div className="friend-avatar">{friend.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <span className="friend-name">{friend.username || `User ${friend.id}`}</span>
                    <button 
                      className="friend-menu-btn"
                      onClick={(e) => toggleMenu(friend.id, e)}
                      aria-label="Friend options"
                    >
                      <MoreVertical size={16} />
                    </button>
                    {openMenuId === friend.id && (
                      <div className="friend-dropdown">
                        <button 
                          className="dropdown-item remove"
                          onClick={(e) => handleRemoveFriend(friend.id, e)}
                        >
                          <UserMinus size={14} />
                          Remove Friend
                        </button>
                      </div>
                    )}
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
                      {/* <span className="post-time">posted</span> */}
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
                  <div key={user.userId} className="leaderboard-item" onClick={() => onOpenTab?.('user', { user: { id: user.userId, name: user.username || `User ${user.userId}` } })}>
                    <span className="rank">#{index + 1}</span>
                    <div className="friend-avatar">{user.username?.charAt(0).toUpperCase() || 'U'}</div>
                    <span className="leaderboard-name">{user.username || `User ${user.userId}`}</span>
                    <span className="leaderboard-score">{user.score || 0} friends</span>
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
                <span className="insight-value">{graphStats?.nodeCount || 0}</span>
              </div>
              <div className="insight-item">
                <span className="insight-label">Total Connections</span>
                <span className="insight-value">{graphStats?.edgeCount || 0}</span>
              </div>
              <div className="insight-item">
                <span className="insight-label">Avg. Connections</span>
                <span className="insight-value">{graphStats?.averageDegree?.toFixed(1) || 0}</span>
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

      </div>

      {/* Toast Notification */}
      {toast && (
        <div className={`dashboard-toast ${toast.type}`}>
          {toast.message}
        </div>
      )}
    </div>
  );
}
