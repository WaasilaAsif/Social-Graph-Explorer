import { useState } from 'react';
import { Heart, MessageCircle, Share2 } from 'lucide-react';
import '../styles/PostView.css';

export default function PostView({ post, onUserClick }) {
  const [liked, setLiked] = useState(false);
  const [likes, setLikes] = useState(post.likes || 0);

  const handleLike = () => {
    setLiked(!liked);
    setLikes(liked ? likes - 1 : likes + 1);
  };

  const postContent = typeof post === 'string' ? post : (post.content || post.text || 'No content');
  const authorName = post.username || post.authorName || `User ${post.userId || 'Unknown'}`;

  return (
    <div className="post-view">
      <div className="post-detail">
        <div
          onClick={() => onUserClick && post.userId && onUserClick({ id: post.userId, name: authorName })}
          className="post-detail-header"
          style={{ cursor: onUserClick && post.userId ? 'pointer' : 'default' }}
        >
          <div className="post-detail-avatar">
            {authorName.charAt(0).toUpperCase()}
          </div>
          <div className="post-detail-author-info">
            <div className="post-detail-author">{authorName}</div>
            <div className="post-detail-meta">
              <span>{post.timestamp ? new Date(post.timestamp).toLocaleString() : 'Recently'}</span>
            </div>
          </div>
        </div>

        <div className="post-detail-content">
          {postContent}
        </div>

        <div className="post-detail-actions">
          <button
            onClick={handleLike}
            className={`post-detail-action ${liked ? 'action-liked' : ''}`}
          >
            <Heart size={20} fill={liked ? 'currentColor' : 'none'} />
            <span>{likes}</span>
          </button>
          <button className="post-detail-action">
            <MessageCircle size={20} />
            <span>{post.comments || 0}</span>
          </button>
          <button className="post-detail-action">
            <Share2 size={20} />
            <span>Share</span>
          </button>
        </div>

        <div className="comments-section">
          <h3 className="comments-title">Comments</h3>
          <div className="comment-form">
            <textarea
              className="comment-textarea"
              placeholder="Write a comment..."
            />
            <button className="comment-submit">Post Comment</button>
          </div>
          <div>
            {[...Array(Math.min(post.comments, 3))].map((_, idx) => (
              <div key={idx} className="comment">
                <div className="comment-avatar">
                  U{idx + 1}
                </div>
                <div className="comment-content">
                  <div className="comment-header">
                    <span className="comment-author">User {idx + 1}</span>
                    <span className="comment-time">2h ago</span>
                  </div>
                  <p className="comment-text">
                    Great insights! This is really helpful.
                  </p>
                </div>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
}
