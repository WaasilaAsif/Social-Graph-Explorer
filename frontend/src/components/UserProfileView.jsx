import { useState, useEffect } from 'react';
import { Users, FileText, UserPlus, UserCheck, Loader2 } from 'lucide-react';
import { userAPI, graphAPI } from '../services/api';
import '../styles/UserProfileView.css';

export default function UserProfileView({ user, onPostClick, onUserClick }) {
  const [posts, setPosts] = useState([]);
  const [friends, setFriends] = useState([]);
  const [loading, setLoading] = useState(true);
  const [isAlreadyFriend, setIsAlreadyFriend] = useState(false);
  const [connectLoading, setConnectLoading] = useState(false);
  const [connectStatus, setConnectStatus] = useState('idle'); // 'idle' | 'success' | 'error'

  // Get current user from localStorage
  const getCurrentUserId = () => {
    try {
      const storedUser = localStorage.getItem('user');
      if (storedUser) {
        const parsed = JSON.parse(storedUser);
        return parsed.userId || 0;
      }
    } catch (err) {
      console.error('Error reading user from localStorage:', err);
    }
    return 0;
  };

  const currentUserId = getCurrentUserId();

  useEffect(() => {
    loadUserData();
  }, [user?.id]);

  // Check if the profile user is already a friend of the current user
  useEffect(() => {
    const checkFriendship = async () => {
      if (!currentUserId || !user?.id || currentUserId === user.id) return;
      
      try {
        const myFriendsData = await graphAPI.getFriends(currentUserId);
        const myFriends = myFriendsData.friends || [];
        const isFriend = myFriends.some((f) => f.id === user.id || f === user.id);
        setIsAlreadyFriend(isFriend);
      } catch (err) {
        console.error('Error checking friendship:', err);
      }
    };
    
    checkFriendship();
  }, [currentUserId, user?.id]);

  const loadUserData = async () => {
    if (!user?.id) return;
    
    setLoading(true);
    try {
      const [postsData, friendsData] = await Promise.all([
        userAPI.getPosts(user.id),
        graphAPI.getFriends(user.id)
      ]);
      setPosts(postsData.posts || []);
      
      // Fetch usernames for each friend
      const friendsList = friendsData.friends || [];
      const friendsWithNames = await Promise.all(
        friendsList.map(async (friend) => {
          try {
            const friendId = typeof friend === 'object' ? friend.id : friend;
            const userData = await userAPI.getUser(friendId);
            return {
              id: friendId,
              username: userData.user?.username || userData.username || `User ${friendId}`
            };
          } catch (error) {
            const friendId = typeof friend === 'object' ? friend.id : friend;
            return { id: friendId, username: `User ${friendId}` };
          }
        })
      );
      setFriends(friendsWithNames);
    } catch (error) {
      console.error('Error loading user data:', error);
    } finally {
      setLoading(false);
    }
  };

  const handleConnect = async () => {
    if (!user?.id || !currentUserId || isAlreadyFriend) return;
    
    setConnectLoading(true);
    setConnectStatus('idle');
    
    try {
      await graphAPI.addFriend(currentUserId, user.id);
      setIsAlreadyFriend(true);
      setConnectStatus('success');
      // Reload to update friend count
      loadUserData();
    } catch (err) {
      console.error('Failed to connect:', err);
      setConnectStatus('error');
      // Reset error status after 3 seconds
      setTimeout(() => setConnectStatus('idle'), 3000);
    } finally {
      setConnectLoading(false);
    }
  };

  if (loading) {
    return (
      <div className="user-profile">
        <div style={{ textAlign: 'center', padding: '2rem' }}>Loading...</div>
      </div>
    );
  }

  return (
    <div className="user-profile">
      <div className="profile-header">
        <div className="profile-info">
          <div className="profile-avatar">
            {user.name?.charAt(0).toUpperCase() || user.username?.charAt(0).toUpperCase() || 'U'}
          </div>
          <div className="profile-details">
            <h2 className="profile-name">{user.name || user.username || `User ${user.id}`}</h2>
            <p className="profile-bio">User ID: {user.id}</p>
          </div>
        </div>
        <div className="profile-stats">
          <div className="stat-box">
            <div className="stat-number">{friends.length}</div>
            <div className="stat-label">Connections</div>
          </div>
          <div className="stat-box">
            <div className="stat-number">{posts.length}</div>
            <div className="stat-label">Posts</div>
          </div>
        </div>
        
        {/* Connect Button - only show if viewing another user's profile */}
        {currentUserId && user?.id && currentUserId !== user.id && (
          <div className="profile-actions">
            {isAlreadyFriend ? (
              <button className="btn-connected" disabled>
                <UserCheck size={18} />
                Connected
              </button>
            ) : (
              <button 
                className={`btn-connect ${connectStatus === 'error' ? 'error' : ''}`}
                onClick={handleConnect}
                disabled={connectLoading}
              >
                {connectLoading ? (
                  <>
                    <Loader2 size={18} className="spinner-icon" />
                    Connecting...
                  </>
                ) : connectStatus === 'success' ? (
                  <>
                    <UserCheck size={18} />
                    Connected!
                  </>
                ) : connectStatus === 'error' ? (
                  <>
                    <UserPlus size={18} />
                    Failed - Retry
                  </>
                ) : (
                  <>
                    <UserPlus size={18} />
                    Connect
                  </>
                )}
              </button>
            )}
          </div>
        )}
      </div>

      <div className="profile-content">
        <h3 style={{ fontSize: '1.125rem', fontWeight: '600', marginBottom: '1rem', display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
          <Users size={20} /> Connections ({friends.length})
        </h3>
        {friends.length === 0 ? (
          <p style={{ color: 'var(--text-secondary)', fontStyle: 'italic' }}>No connections yet</p>
        ) : (
          <div className="friends-grid">
            {friends.slice(0, 12).map((friend) => (
              <div
                key={friend.id}
                onClick={() => onUserClick({ id: friend.id, name: friend.username || `User ${friend.id}` })}
                className="friend-card"
              >
                <div className="friend-avatar">
                  {friend.username?.charAt(0).toUpperCase() || 'U'}
                </div>
                <div className="friend-name">{friend.username || `User ${friend.id}`}</div>
              </div>
            ))}
            {friends.length > 12 && (
              <div className="friend-card" style={{ opacity: 0.6, cursor: 'default' }}>
                <div className="friend-avatar">+</div>
                <div className="friend-name">{friends.length - 12} more</div>
              </div>
            )}
          </div>
        )}

        <h3 style={{ fontSize: '1.125rem', fontWeight: '600', margin: '2rem 0 1rem', display: 'flex', alignItems: 'center', gap: '0.5rem' }}>
          <FileText size={20} /> Recent Posts ({posts.length})
        </h3>
        {posts.length === 0 ? (
          <p style={{ color: 'var(--text-secondary)', fontStyle: 'italic' }}>No posts yet</p>
        ) : (
          <div style={{ display: 'flex', flexDirection: 'column', gap: '1rem' }}>
            {posts.slice(0, 10).map((post, index) => (
              <div
                key={index}
                onClick={() => onPostClick && onPostClick({ id: index, content: typeof post === 'string' ? post : post.content || post })}
                className="post-card"
                style={{ cursor: onPostClick ? 'pointer' : 'default' }}
              >
                <p className="post-content" style={{ marginBottom: '0.5rem' }}>
                  {typeof post === 'string' ? post : post.content || post}
                </p>
              </div>
            ))}
            {posts.length > 10 && (
              <p style={{ textAlign: 'center', color: 'var(--text-secondary)', fontStyle: 'italic' }}>
                + {posts.length - 10} more posts
              </p>
            )}
          </div>
        )}
      </div>
    </div>
  );
}
