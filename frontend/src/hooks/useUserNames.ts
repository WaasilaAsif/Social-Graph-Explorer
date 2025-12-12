import { useState, useEffect } from 'react';
import { userAPI } from '../services/api';

// Cache for usernames to avoid repeated API calls
const usernameCache = new Map<number, string>();

export const useUserNames = (userIds: number[]) => {
  const [usernames, setUsernames] = useState<Map<number, string>>(new Map());
  const [loading, setLoading] = useState(true);

  useEffect(() => {
    const fetchUsernames = async () => {
      const newUsernames = new Map<number, string>();
      const uncachedIds: number[] = [];

      // Check cache first
      userIds.forEach(id => {
        if (usernameCache.has(id)) {
          newUsernames.set(id, usernameCache.get(id)!);
        } else {
          uncachedIds.push(id);
        }
      });

      // Fetch uncached usernames
      if (uncachedIds.length > 0) {
        const promises = uncachedIds.map(async (id) => {
          try {
            const response = await userAPI.getUser(id);
            const username = response.user?.username || response.username || `User ${id}`;
            usernameCache.set(id, username);
            return { id, username };
          } catch (error) {
            const fallback = `User ${id}`;
            usernameCache.set(id, fallback);
            return { id, username: fallback };
          }
        });

        const results = await Promise.all(promises);
        results.forEach(({ id, username }) => {
          newUsernames.set(id, username);
        });
      }

      setUsernames(newUsernames);
      setLoading(false);
    };

    if (userIds.length > 0) {
      fetchUsernames();
    } else {
      setLoading(false);
    }
  }, [userIds.join(',')]);

  return { usernames, loading };
};

// Utility function to get a single username (with caching)
export const getUserName = async (userId: number): Promise<string> => {
  if (usernameCache.has(userId)) {
    return usernameCache.get(userId)!;
  }

  try {
    const response = await userAPI.getUser(userId);
    const username = response.user?.username || response.username || `User ${userId}`;
    usernameCache.set(userId, username);
    return username;
  } catch (error) {
    const fallback = `User ${userId}`;
    usernameCache.set(userId, fallback);
    return fallback;
  }
};

