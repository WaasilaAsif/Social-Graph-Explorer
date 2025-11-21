import { Users, GitBranch, FileText } from 'lucide-react';
import { getPostsByUserId } from '../data/dummyPosts';
import { getUserConnections } from '../data/dummyUsers';

export default function UserProfileView({ user, onPostClick, onUserClick }) {
  const userPosts = getPostsByUserId(user.id);
  const connections = getUserConnections(user.id);

  return (
    <div className="h-full overflow-auto">
      <div className="p-6 border-b border-[#2b2b2b]">
        <div className="flex items-start gap-6">
          <div className="w-24 h-24 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-3xl font-bold text-white">
            {user.avatar}
          </div>
          <div className="flex-1">
            <h2 className="text-2xl font-bold text-gray-200">{user.name}</h2>
            <p className="text-gray-400 mt-2">{user.bio}</p>
            <div className="flex items-center gap-6 mt-4">
              <div className="flex items-center gap-2">
                <Users size={16} className="text-gray-500" />
                <span className="text-sm text-gray-300">
                  <strong>{user.followers}</strong> followers
                </span>
              </div>
              <div className="flex items-center gap-2">
                <GitBranch size={16} className="text-gray-500" />
                <span className="text-sm text-gray-300">
                  <strong>{user.following}</strong> following
                </span>
              </div>
              <div className="flex items-center gap-2">
                <FileText size={16} className="text-gray-500" />
                <span className="text-sm text-gray-300">
                  <strong>{user.posts}</strong> posts
                </span>
              </div>
            </div>
          </div>
        </div>
      </div>

      <div className="p-6">
        <h3 className="text-lg font-semibold text-gray-200 mb-4">Connections</h3>
        <div className="grid grid-cols-2 gap-3 mb-8">
          {connections.map((conn) => (
            <button
              key={conn.id}
              onClick={() => onUserClick(conn)}
              className="flex items-center gap-3 p-3 bg-[#2b2b2b] hover:bg-[#3a3a3a] rounded-lg transition-colors"
            >
              <div className="w-10 h-10 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-sm font-semibold text-white">
                {conn.avatar}
              </div>
              <div className="text-left">
                <p className="text-sm font-medium text-gray-200">{conn.name}</p>
                <p className="text-xs text-gray-400">{conn.followers} followers</p>
              </div>
            </button>
          ))}
        </div>

        <h3 className="text-lg font-semibold text-gray-200 mb-4">Recent Posts</h3>
        <div className="space-y-4">
          {userPosts.map((post) => (
            <button
              key={post.id}
              onClick={() => onPostClick(post)}
              className="w-full text-left p-4 bg-[#2b2b2b] hover:bg-[#3a3a3a] rounded-lg transition-colors"
            >
              <p className="text-sm text-gray-300 line-clamp-3">{post.content}</p>
              <div className="flex items-center gap-4 mt-3 text-xs text-gray-500">
                <span>{new Date(post.timestamp).toLocaleDateString()}</span>
                <span>{post.likes} likes</span>
                <span>{post.comments} comments</span>
              </div>
            </button>
          ))}
        </div>
      </div>
    </div>
  );
}
