import { Users, GitBranch, FileText } from 'lucide-react';
import { getPostsByUserId } from '../data/dummyPosts';
import { getUserConnections } from '../data/dummyUsers';
import '../styles/UserProfileView.css';

export default function UserProfileView({ user, onPostClick, onUserClick }) {
  const userPosts = getPostsByUserId(user.id);
  const connections = getUserConnections(user.id);

  return (
    <div className="user-profile">
      <div className="profile-header">
        <div className="profile-info">
          <div className="profile-avatar">
            {user.avatar}
          </div>
          <div className="profile-details">
            <h2 className="profile-name">{user.name}</h2>
            <p className="profile-bio">{user.bio}</p>
          </div>
        </div>
        <div className="profile-stats">
          <div className="stat-box">
            <div className="stat-number">{user.followers}</div>
            <div className="stat-label">Followers</div>
          </div>
          <div className="stat-box">
            <div className="stat-number">{user.following}</div>
            <div className="stat-label">Following</div>
          </div>
          <div className="stat-box">
            <div className="stat-number">{user.posts}</div>
            <div className="stat-label">Posts</div>
          </div>
        </div>
      </div>

      <div className="profile-content">
        <h3 style={{ fontSize: '1.125rem', fontWeight: '600', marginBottom: '1rem' }}>Connections</h3>
        <div className="friends-grid">
          {connections.map((conn) => (
            <div
              key={conn.id}
              onClick={() => onUserClick(conn)}
              className="friend-card"
            >
              <div className="friend-avatar">
                {conn.avatar}
              </div>
              <div className="friend-name">{conn.name}</div>
              <div className="friend-username">{conn.followers} followers</div>
            </div>
          ))}
        </div>

        <h3 style={{ fontSize: '1.125rem', fontWeight: '600', margin: '2rem 0 1rem' }}>Recent Posts</h3>
        <div style={{ display: 'flex', flexDirection: 'column', gap: '1rem' }}>
          {userPosts.map((post) => (
            <div
              key={post.id}
              onClick={() => onPostClick(post)}
              className="post-card"
              style={{ cursor: 'pointer' }}
            >
              <p className="post-content" style={{ marginBottom: '0.75rem' }}>{post.content}</p>
              <div style={{ display: 'flex', gap: '1rem', fontSize: '0.75rem', color: 'var(--text-muted)' }}>
                <span>{new Date(post.timestamp).toLocaleDateString()}</span>
                <span>{post.likes} likes</span>
                <span>{post.comments} comments</span>
              </div>
            </div>
          ))}
        </div>
      </div>
    </div>
  );
}
