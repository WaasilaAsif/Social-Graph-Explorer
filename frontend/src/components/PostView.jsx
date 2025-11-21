import { Heart, MessageCircle, Share2 } from 'lucide-react';
import { getUserById } from '../data/dummyUsers';

export default function PostView({ post, onUserClick }) {
  const author = getUserById(post.userId);

  return (
    <div className="h-full overflow-auto">
      <div className="max-w-3xl mx-auto p-8">
        <button
          onClick={() => onUserClick(author)}
          className="flex items-center gap-3 mb-6 hover:bg-[#2b2b2b] p-3 rounded-lg transition-colors"
        >
          <div className="w-12 h-12 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-sm font-semibold text-white">
            {author.avatar}
          </div>
          <div>
            <p className="text-gray-200 font-medium">{author.name}</p>
            <p className="text-sm text-gray-500">
              {new Date(post.timestamp).toLocaleString()}
            </p>
          </div>
        </button>

        <div className="bg-[#2b2b2b] rounded-lg p-6">
          <p className="text-gray-200 text-lg leading-relaxed whitespace-pre-wrap">
            {post.content}
          </p>

          <div className="flex items-center gap-6 mt-6 pt-6 border-t border-[#3a3a3a]">
            <button className="flex items-center gap-2 text-gray-400 hover:text-red-400 transition-colors">
              <Heart size={20} />
              <span className="text-sm">{post.likes}</span>
            </button>
            <button className="flex items-center gap-2 text-gray-400 hover:text-blue-400 transition-colors">
              <MessageCircle size={20} />
              <span className="text-sm">{post.comments}</span>
            </button>
            <button className="flex items-center gap-2 text-gray-400 hover:text-green-400 transition-colors">
              <Share2 size={20} />
              <span className="text-sm">Share</span>
            </button>
          </div>
        </div>

        <div className="mt-8">
          <h3 className="text-lg font-semibold text-gray-200 mb-4">Comments</h3>
          <div className="space-y-4">
            {[...Array(post.comments > 3 ? 3 : post.comments)].map((_, idx) => (
              <div key={idx} className="bg-[#2b2b2b] rounded-lg p-4">
                <div className="flex items-center gap-3 mb-2">
                  <div className="w-8 h-8 rounded-full bg-gradient-to-br from-emerald-500 to-teal-600 flex items-center justify-center text-xs font-semibold text-white">
                    U{idx + 1}
                  </div>
                  <p className="text-sm text-gray-300 font-medium">User {idx + 1}</p>
                  <span className="text-xs text-gray-500">2h ago</span>
                </div>
                <p className="text-sm text-gray-400 ml-11">
                  Great insights! This is really helpful.
                </p>
              </div>
            ))}
          </div>
        </div>
      </div>
    </div>
  );
}
