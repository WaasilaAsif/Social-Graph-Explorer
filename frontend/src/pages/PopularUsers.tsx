import { useState, useEffect } from 'react';
import { algoAPI, userAPI } from '../services/api';
import { Trophy, Users, TrendingUp, Crown } from 'lucide-react';
import '../styles/PopularUsers.css';

interface PopularUser {
  userId: number;
  username: string;
  score: number;
}

const PopularUsers = () => {
  const [topUsers, setTopUsers] = useState<PopularUser[]>([]);
  const [limit, setLimit] = useState(20);
  const [loading, setLoading] = useState(true);
  const [error, setError] = useState<string | null>(null);

  useEffect(() => {
    loadTopUsers();
  }, [limit]);

  const loadTopUsers = async () => {
    setLoading(true);
    setError(null);
    try {
      const data = await algoAPI.getTopPopular(limit);
      const topUsersList = data.topUsers || [];
      
      // Fetch usernames for each user
      const topUsersWithDetails = await Promise.all(
        topUsersList.map(async (user: any) => {
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
      
      setTopUsers(topUsersWithDetails);
    } catch (err: any) {
      setError(err.message || 'Failed to load popular users');
    } finally {
      setLoading(false);
    }
  };

  const getMedalIcon = (rank: number) => {
    if (rank === 1) return <Crown size={24} color="#FFD700" />;
    if (rank === 2) return <Crown size={22} color="#C0C0C0" />;
    if (rank === 3) return <Crown size={20} color="#CD7F32" />;
    return null;
  };

  if (loading) {
    return (
      <div className="popular-users-loading">
        <div className="spinner"></div>
        <p>Loading leaderboard...</p>
      </div>
    );
  }

  if (error) {
    return (
      <div className="popular-users-error">
        <p>Error: {error}</p>
        <button onClick={loadTopUsers}>Retry</button>
      </div>
    );
  }

  return (
    <div className="popular-users-container">
      <div className="leaderboard-header">
        <h1><Trophy size={36} /> Popularity Leaderboard</h1>
        <p>Top users ranked by number of connections</p>
      </div>

      <div className="leaderboard-controls">
        <label htmlFor="limit-select">Show:</label>
        <select 
          id="limit-select"
          value={limit} 
          onChange={(e) => setLimit(Number(e.target.value))}
          className="limit-select"
        >
          <option value={10}>Top 10</option>
          <option value={20}>Top 20</option>
          <option value={50}>Top 50</option>
          <option value={100}>Top 100</option>
        </select>
      </div>

      {topUsers.length === 0 ? (
        <div className="no-data">
          <Users size={48} />
          <p>No users found</p>
        </div>
      ) : (
        <div className="leaderboard-list">
          {topUsers.map((user, index) => {
            const rank = index + 1;
            const isTopThree = rank <= 3;

            return (
              <div 
                key={user.userId} 
                className={`leaderboard-item ${isTopThree ? 'top-three' : ''} ${rank === 1 ? 'champion' : ''}`}
              >
                <div className="rank-badge">
                  {getMedalIcon(rank) || <span className="rank-number">#{rank}</span>}
                </div>

                <div className="user-info">
                  <div className="user-avatar">
                    {user.username?.charAt(0).toUpperCase() || 'U'}
                  </div>
                  <div className="user-details">
                    <h3 className="username">{user.username || `User ${user.userId}`}</h3>
                    <p className="user-id">ID: {user.userId}</p>
                  </div>
                </div>

                <div className="user-stats">
                  <div className="stat">
                    <Users size={18} />
                    <span className="stat-value">{user.score}</span>
                    <span className="stat-label">friends</span>
                  </div>
                </div>

                {isTopThree && (
                  <div className="trophy-decoration">
                    <Trophy size={20} />
                  </div>
                )}
              </div>
            );
          })}
        </div>
      )}

      <div className="leaderboard-footer">
        <button onClick={loadTopUsers} className="refresh-btn">
          <TrendingUp size={16} /> Refresh Leaderboard
        </button>
      </div>
    </div>
  );
};

export default PopularUsers;
