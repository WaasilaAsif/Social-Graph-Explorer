import { useState, useEffect } from 'react';
import { useParams } from 'react-router-dom';
import { userAPI, graphAPI, algoAPI } from '../services/api';
import { User, Users, MessageSquare, TrendingUp, UserPlus, MapPin, Award } from 'lucide-react';
import '../styles/UserProfile.css';

interface UserData {
  id: number;
  username: string;
  posts?: any[];
}

const UserProfile = () => {
  const { id } = useParams<{ id: string }>();
  const userId = id ? parseInt(id) : null;
  
  const [user, setUser] = useState<UserData | null>(null);
  const [friends, setFriends] = useState<any[]>([]);
  const [posts, setPosts] = useState<any[]>([]);
  const [degree, setDegree] = useState<number>(0);
  const [rank, setRank] = useState<number | null>(null);
  const [suggestions, setSuggestions] = useState<any[]>([]);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  const currentUserId = parseInt(localStorage.getItem('userId') || '0');

  useEffect(() => {
    if (userId) {
      loadUserProfile();
    }
  }, [userId]);

  const loadUserProfile = async () => {
    if (!userId) return;
    
    setLoading(true);
    setError(null);
    try {
      const [userData, friendsData, postsData, degreeData, rankData, suggestionsData] = await Promise.all([
        userAPI.getUser(userId),
        graphAPI.getFriends(userId),
        userAPI.getPosts(userId),
        algoAPI.getUserDegree(userId),
        algoAPI.getUserRank(userId),
        algoAPI.getFriendSuggestions(userId, 5)
      ]);

      setUser(userData.user || userData);
      setFriends(friendsData.friends || []);
      setPosts(postsData.posts || []);
      setDegree(degreeData.degree || 0);
      setRank(rankData.rank || null);
      setSuggestions(suggestionsData.suggestions || []);
    } catch (err: any) {
      setError(err.message || 'Failed to load user profile');
    } finally {
      setLoading(false);
    }
  };

  const handleAddFriend = async (friendId: number) => {
    try {
      await graphAPI.addFriend(currentUserId, friendId);
      loadUserProfile();
    } catch (err: any) {
      alert('Failed to add friend: ' + err.message);
    }
  };

  if (loading) {
    return (
      <div className="user-profile-loading">
        <div className="spinner"></div>
        <p>Loading profile...</p>
      </div>
    );
  }

  if (error || !user) {
    return (
      <div className="user-profile-error">
        <p>Error: {error || 'User not found'}</p>
        <button onClick={loadUserProfile}>Retry</button>
      </div>
    );
  }

  return (
    <div className="user-profile-container">
      {/* Profile Header */}
      <div className="profile-header">
        <div className="profile-avatar-large">
          {user.username?.charAt(0).toUpperCase() || 'U'}
        </div>
        <div className="profile-info">
          <h1>{user.username || `User ${user.id}`}</h1>
          <p className="user-id-label">ID: {user.id}</p>
          <div className="profile-stats-inline">
            <div className="stat-inline">
              <Users size={18} />
              <span>{degree} connections</span>
            </div>
            {rank && (
              <div className="stat-inline">
                <Award size={18} />
                <span>Rank #{rank}</span>
              </div>
            )}
            <div className="stat-inline">
              <MessageSquare size={18} />
              <span>{posts.length} posts</span>
            </div>
          </div>
        </div>
      </div>

      <div className="profile-grid">
        {/* Friends Section */}
        <div className="profile-card">
          <div className="card-header">
            <Users size={20} />
            <h2>Friends ({friends.length})</h2>
          </div>
          <div className="card-content">
            {friends.length === 0 ? (
              <p className="empty-state">No friends yet</p>
            ) : (
              <div className="friends-grid">
                {friends.slice(0, 12).map((friend: any) => (
                  <div key={friend.id} className="friend-mini-card">
                    <div className="friend-avatar-small">
                      {friend.username?.charAt(0).toUpperCase() || 'U'}
                    </div>
                    <span className="friend-name-small">{friend.username || `User ${friend.id}`}</span>
                  </div>
                ))}
                {friends.length > 12 && (
                  <div className="friend-mini-card more">
                    <span>+{friends.length - 12}</span>
                  </div>
                )}
              </div>
            )}
          </div>
        </div>

        {/* Posts Section */}
        <div className="profile-card">
          <div className="card-header">
            <MessageSquare size={20} />
            <h2>Posts ({posts.length})</h2>
          </div>
          <div className="card-content">
            {posts.length === 0 ? (
              <p className="empty-state">No posts yet</p>
            ) : (
              <div className="posts-list">
                {posts.slice(0, 10).map((post: any, index: number) => (
                  <div key={index} className="post-item">
                    <p>{typeof post === 'string' ? post : post.content || post}</p>
                  </div>
                ))}
                {posts.length > 10 && (
                  <p className="more-posts">+ {posts.length - 10} more posts</p>
                )}
              </div>
            )}
          </div>
        </div>

        {/* Friend Suggestions Section */}
        {suggestions.length > 0 && (
          <div className="profile-card">
            <div className="card-header">
              <UserPlus size={20} />
              <h2>Suggested Connections</h2>
            </div>
            <div className="card-content">
              <div className="suggestions-list">
                {suggestions.map((suggestion: any) => (
                  <div key={suggestion.userId} className="suggestion-item">
                    <div className="suggestion-info">
                      <div className="friend-avatar-small">
                        {suggestion.username?.charAt(0).toUpperCase() || 'U'}
                      </div>
                      <div className="suggestion-details">
                        <span className="suggestion-name">{suggestion.username || `User ${suggestion.userId}`}</span>
                        <span className="suggestion-reason">{suggestion.mutualFriends || 0} mutual</span>
                      </div>
                    </div>
                    {userId !== currentUserId && (
                      <button
                        className="btn-add-mini"
                        onClick={() => handleAddFriend(suggestion.userId)}
                      >
                        Add
                      </button>
                    )}
                  </div>
                ))}
              </div>
            </div>
          </div>
        )}
      </div>
    </div>
  );
};

export default UserProfile;
