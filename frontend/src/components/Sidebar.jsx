import { useState } from 'react';
import { ChevronDown, ChevronRight, Users, Network, Home } from 'lucide-react';
import { dummyUsers } from '../data/dummyUsers';

export default function Sidebar({ onUserClick, onNavigate }) {
  const [usersExpanded, setUsersExpanded] = useState(true);
  const [graphsExpanded, setGraphsExpanded] = useState(true);

  return (
    <div className="h-full bg-[#1e1e1e] border-r border-[#2b2b2b] flex flex-col">
      <div className="p-4 border-b border-[#2b2b2b]">
        <h1 className="text-lg font-semibold text-gray-200">SocialGraphExplorer</h1>
      </div>

      <div className="flex-1 overflow-y-auto">
        <div className="p-2">
          <button
            onClick={() => onNavigate('home')}
            className="w-full flex items-center gap-2 px-3 py-2 text-sm text-gray-300 hover:bg-[#2b2b2b] rounded transition-colors"
          >
            <Home size={16} />
            <span>Home</span>
          </button>
        </div>

        <div className="mt-4">
          <button
            onClick={() => setUsersExpanded(!usersExpanded)}
            className="w-full flex items-center gap-2 px-4 py-2 text-sm text-gray-400 hover:bg-[#2b2b2b] transition-colors"
          >
            {usersExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
            <Users size={16} />
            <span>Users</span>
          </button>

          {usersExpanded && (
            <div className="mt-1">
              {dummyUsers.map(user => (
                <button
                  key={user.id}
                  onClick={() => onUserClick(user)}
                  className="w-full flex items-center gap-3 px-8 py-2 text-sm text-gray-300 hover:bg-[#2b2b2b] transition-colors"
                >
                  <div className="w-6 h-6 rounded-full bg-gradient-to-br from-blue-500 to-purple-600 flex items-center justify-center text-xs font-semibold text-white">
                    {user.avatar}
                  </div>
                  <span className="truncate">{user.name}</span>
                </button>
              ))}
            </div>
          )}
        </div>

        <div className="mt-4">
          <button
            onClick={() => setGraphsExpanded(!graphsExpanded)}
            className="w-full flex items-center gap-2 px-4 py-2 text-sm text-gray-400 hover:bg-[#2b2b2b] transition-colors"
          >
            {graphsExpanded ? <ChevronDown size={16} /> : <ChevronRight size={16} />}
            <Network size={16} />
            <span>Graphs</span>
          </button>

          {graphsExpanded && (
            <div className="mt-1">
              <button
                onClick={() => onNavigate('graph', { graphId: 'main' })}
                className="w-full flex items-center gap-3 px-8 py-2 text-sm text-gray-300 hover:bg-[#2b2b2b] transition-colors"
              >
                <Network size={14} />
                <span>Main Network</span>
              </button>
              <button
                onClick={() => onNavigate('graph', { graphId: 'communities' })}
                className="w-full flex items-center gap-3 px-8 py-2 text-sm text-gray-300 hover:bg-[#2b2b2b] transition-colors"
              >
                <Network size={14} />
                <span>Communities</span>
              </button>
            </div>
          )}
        </div>
      </div>

      <div className="p-4 border-t border-[#2b2b2b]">
        <button className="w-full px-3 py-2 text-sm text-gray-400 hover:text-gray-200 hover:bg-[#2b2b2b] rounded transition-colors">
          Settings
        </button>
      </div>
    </div>
  );
}
